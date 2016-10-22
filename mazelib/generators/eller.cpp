//
// Created by Nicholas Amor on 21/10/16.
//

#include <algorithm>
#include <map>
#include "generator.h"

using namespace mazer;

struct RowState
{
  public:
    RowState(int starting_set = 0) : next_set(starting_set) {}

    std::map<int, std::vector<Cell *>> cells_in_set;
    std::map<int, int> set_for_cell;
    int next_set;

    /**
     * Records a given set for the given cell.
     * @param set
     * @param cell
     * @return
     */
    void record(int set, Cell *cell)
    {
        set_for_cell[cell->x] = set;

        cells_in_set[set].emplace_back(cell);
    }

    /**
     * Checks to see if the given cell belongs to a set yet (if not, it assigns
     * it to one) and then returns that set.
     * @param cell
     * @return
     */
    int set_for(Cell *cell)
    {
        if (set_for_cell.find(cell->x) == set_for_cell.end())
        {
            record(next_set, cell);
            next_set += 1;
        }

        return set_for_cell[cell->x];
    }

    /**
     * Moves all cells from the loser set to the winner set.
     * @param winner
     * @param loser
     * @return
     */
    void merge(int winner, int loser)
    {
        for (auto cell : cells_in_set[loser])
        {
            set_for_cell[cell->x] = winner;
            cells_in_set[winner].emplace_back(cell);
        }

        cells_in_set[loser].clear();
    }

    /**
     * Returns a new RowState instance, counting sets from where the current
     * instance left off.
     * @return
     */
    RowState next()
    {
        return RowState(next_set);
    }

    /**
     * Iterates over the sets in the current row, yielding each set and its
     * collection of cells to the attached block.
     * @return
     */
    std::vector<std::vector<Cell *>> each_set()
    {
        std::vector<std::vector<Cell *>> sets;

        for (auto pair : cells_in_set)
        {
            sets.emplace_back(pair.second);
        }

        return sets;
    }
};

EllerGen::EllerGen(IMaze &maze)
    : Generator(maze)
{
}

EllerGen::~EllerGen()
{
}

void EllerGen::generate()
{
    RowState row_state;
    auto &cells = maze.getCells();
    int w = maze.getWidth(), h = maze.getHeight();

    // For each row
    for (int y = 0; y < h; ++y)
    {
        // For each cell, skipping the left-most column
        for (int x = 1; x < w; ++x)
        {
            auto cell = &cells[(y * w) + x];

            auto set = row_state.set_for(cell);
            auto prior_set = row_state.set_for(cell->left);

            // Link this cell and the previous if they have distinct sets,
            // and either this is the last row or 50/50 chance
            auto should_link = set != prior_set &&
                               (cell->down == nullptr || nextRand(0, 1) == 0);

            if (should_link)
            {
                auto next = cell->left;
                link(cell, next);

                row_state.merge(prior_set, set);
            }
        }

        // If this is not the last row
        if (y < h - 1)
        {
            // Prepare the next row state
            auto next_row = row_state.next();

            // For each set of cells in the row
            for (auto list : row_state.each_set())
            {
                std::shuffle(list.begin(), list.end(), engine);

                // For each cell in the set
                for (auto cell : list)
                {
                    // If this is the first(random) cell or 50/50 chance, link
                    // this cell and the cell lower than it
                    if (cell == list.front() || nextRand(0, 1) == 0)
                    {
                        auto next = cell->down;
                        link(cell, next);

                        next_row.record(row_state.set_for(cell), cell->down);
                    }
                }
            }

            row_state = next_row;
        }
    }
}
