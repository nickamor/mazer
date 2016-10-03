//
// Created by Nicholas Amor on 28/9/16.
//

#include <map>
#include <maze_builder.h>
#include <maze_generator.h>
#include <strong_random.h>

using namespace mazer;

struct SetState {
    SetState(int width, int height) :
        width(width),
        height(height),
        builder(width, height),
        cells(width * height) {}

    int width, height;
    MazeBuilder builder;
    std::vector<int> cells;

    bool SameSet(const CellPos& lhs, const CellPos& rhs) {
        return cells.at(unsigned((lhs.y * width) + lhs.x)) == cells.at(unsigned((rhs.y * width) + rhs.x));
    }

    void Link(const CellPos& lhs, const CellPos& rhs) {
        cells[(width * lhs.y) + lhs.x] = cells.at(unsigned((width * rhs.y) + rhs.x));
        builder.AddLink(lhs, rhs);
    }

    std::map<int, int> DistinctSets(const int& row) {
        std::map<int, int> distinct;
        for (int j = 0; j < width; ++j) {
            distinct[cells[(width * row) + j]]++;
        }
        return distinct;
    }

    std::vector<CellPos> SetCells(const int& row, const int& set) {
        std::vector<CellPos> set_cells;
        for (int j = 0; j < width; ++j) {
            if (cells[(width * row) + j] == set) {
                set_cells.push_back(CellPos{row, j});
            }
        }

        return set_cells;
    };

    int& SetAt(const CellPos& pos) {
        return cells[(width * pos.y) + pos.x];
    }
};

EllerGenerator::~EllerGenerator() {

}

std::unique_ptr<Maze>
EllerGenerator::Generate(int seed, int width, int height)
{
    SetState state(width, height);
    StrongRandom rand(seed);
    int sets = 0;

    // for each row
    for (int i = 0; i < height; ++i)
    {
        // initialise sets as needed
        for (int j = 0; j < width; ++j)
        {
            int& set = state.SetAt(CellPos{i, j});
            if (set == 0)
                set = ++sets;
        }

        // randomly join adjacent sets
        for (int j = 0; j < width - 1; ++j) {
            if (rand.NextBool() && !state.SameSet(CellPos{i, j}, CellPos{i + 1, j})) {
                state.Link(CellPos{i, j + 1}, CellPos{i, j});
            }
        }

        // carve south at least once from remaining sets
        auto distinct = state.DistinctSets(i);
        for (auto& set : distinct) {
            auto set_cells = state.SetCells(i, set.first);
            rand.Shuffle(set_cells.begin(), set_cells.end());

            auto first_cell = set_cells.front();
            state.Link(first_cell, CellPos{first_cell.x, first_cell.y + 1});
            set_cells.erase(set_cells.begin());

            for (auto& cell : set_cells) {
                if (rand.NextBool()) {
                    state.Link(cell, CellPos{cell.x, cell.y + 1});
                }
            }
        }
    }

    state.builder.AddExits();
    return state.builder.ToMaze();
}
