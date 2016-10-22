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
    using Set = int;

    RowState(Set startingSet = 0) : nextSet(startingSet) {}

    std::map<Set, std::vector<Cell *>> cellsInSet;
    std::map<int, Set> setForCell;
    Set nextSet;

    /**
     * Records a given set for the given cell.
     * @param set
     * @param cell
     * @return
     */
    void record(Set set, Cell *cell)
    {
        setForCell[cell->x] = set;

        cellsInSet[set].emplace_back(cell);
    }

    /**
     * Checks to see if the given cell belongs to a set yet (if not, it assigns
     * it to one) and then returns that set.
     * @param cell
     * @return
     */
    Set setFor(Cell *cell)
    {
        if (setForCell.find(cell->x) == setForCell.end())
        {
            record(nextSet, cell);
            nextSet += 1;
        }

        return setForCell[cell->x];
    }

    /**
     * Moves all cells from the loser set to the winner set.
     * @param winner
     * @param loser
     * @return
     */
    void merge(Set winner, Set loser)
    {
        for (auto cell : cellsInSet[loser])
        {
            setForCell[cell->x] = winner;
            cellsInSet[winner].emplace_back(cell);
        }

        cellsInSet[loser].clear();
    }

    /**
     * Returns a new RowState instance, counting sets from where the current
     * instance left off.
     * @return
     */
    RowState next()
    {
        return RowState(nextSet);
    }

    /**
     * Iterates over the sets in the current row, yielding each set and its
     * collection of cells to the attached block.
     * @return
     */
    std::vector<std::vector<Cell *>> allSets()
    {
        std::vector<std::vector<Cell *>> sets;

        for (auto pair : cellsInSet)
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
    RowState rowState;
    int w = maze.getWidth(), h = maze.getHeight();

    // For each row
    for (int row = 0; row < h; ++row)
    {
        // For each cell, skipping the left-most column
        for (int col = 1; col < w; ++col)
        {
            auto& cell = maze.getCell(col, row);

            auto set = rowState.setFor(&cell);
            auto prior_set = rowState.setFor(cell.left);

            // Link this cell and the previous if they have distinct sets,
            // and either this is the last row or 50/50 chance
            if (set != prior_set)
            {
                if (cell.down == nullptr || nextRand(0, 1) == 0)
                {
                    auto next = cell.left;
                    maze.link(&cell, next);

                    rowState.merge(prior_set, set);
                }
            }
        }

        // If this is not the last row
        if (row < h - 1)
        {
            // Prepare the next row state
            auto nextRow = rowState.next();

            // For each set of cells in the row
            for (auto& list : rowState.allSets())
            {
                std::shuffle(list.begin(), list.end(), engine);

                // For each cell in the set
                for (auto& cell : list)
                {
                    // If this is the first(random) cell or 50/50 chance, link
                    // this cell and the cell lower than it
                    if (cell == list.front() || nextRand(0, 1) == 0)
                    {
                        auto next = cell->down;
                        maze.link(cell, next);

                        nextRow.record(rowState.setFor(cell), cell->down);
                    }
                }
            }

            rowState = nextRow;
        }
    }
}
