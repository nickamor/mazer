//
// Created by Nicholas Amor on 13/8/16.
//

#include <map>
#include "maze_generator.h"
#include "strong_random.h"
#include "maze_builder.h"

using namespace mazer;

/**
 * Concrete implementation of MazeGenerator that uses the Aldous-Broder algorithm.
 */
class AldousBroderGenerator : public MazeGenerator
{
public:

    /**
     * Generate the maze using Aldous-Broder
     * @return
     */
    std::shared_ptr<Maze>
    Generate(int seed, int width, int height) override
    {
        auto rand = StrongRandom(seed);
        int unvisited = (width * height) - 1;
        auto builder = MazeBuilder(width, height);

        auto cell = builder.CellAt(rand.Next(0, width - 1), rand.Next(0, height - 1));

        while (unvisited > 0)
        {
            auto &&n = cell->Neighbours();
            int i = rand.Next<int>(0, (int) (n.size() - 1));
            auto random_n = n[i];

            if (random_n->links.size() == 0)
            {
                builder.AddLink(cell, random_n);
                unvisited -= 1;
            }

            cell = random_n;
        }

        builder.AddExits();

        return builder.ToMaze();
    }
};

class EllerGenerator : public MazeGenerator
{
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
public:
    std::shared_ptr<Maze>
    Generate(int seed, int width, int height) override
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
};

std::shared_ptr<Maze>
MazeGenerator::Generate(int, int, int)
{
    return nullptr;
}

std::shared_ptr<MazeGenerator>
MazeGenerator::Factory(MazeGeneratorType type)
{
    switch (type)
    {
        case MazeGeneratorType::AldousBroder:return std::make_shared<AldousBroderGenerator>();
        case MazeGeneratorType::Eller:return std::make_shared<EllerGenerator>();
    }
}
