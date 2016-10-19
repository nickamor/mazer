//
// Created by Nicholas Amor on 14/10/16.
//

#include <map>
#include "generator.h"

using namespace mazer;

Generator::Generator(IMaze &maze) : maze(maze)
{
    engine.seed(unsigned(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
}

Generator::~Generator() {}

void Generator::generate() {}

/**
 * Get a random number within a range.
 * @param min
 * @param max
 * @return
 */
int Generator::nextRand(int min, int max)
{
    return std::uniform_int_distribution<int>(min, max)(engine);
}

void Generator::seed(const int s)
{
    engine.seed(unsigned(s));
}

void Generator::link(Cell* cell, Cell* next)
{
    cell->links.emplace_back(next);
    next->links.emplace_back(cell);
}

AldousBroderGen::AldousBroderGen(IMaze &maze)
    : Generator(maze)
{
}

AldousBroderGen::~AldousBroderGen()
{
}

/**
 * Traverse each maze cell at random until all are linked.
 */
void AldousBroderGen::generate()
{
    int w = maze.getWidth(), h = maze.getHeight();

    maze.clear();
    maze.resize(w, h);

    int unvisited = w * h - 1;
    auto cells = maze.getCells();
    auto cell = &cells[nextRand(0, int(cells.size() - 1))];

    while (unvisited > 0)
    {
        auto next = cell->nbrs[nextRand(0, int(cell->nbrs.size()) - 1)];

        if (next->links.empty())
        {
            link(cell, next);

            unvisited--;
        }

        cell = next;
    }
}

EllerGen::EllerGen(IMaze &maze)
    : Generator(maze)
{
}

EllerGen::~EllerGen()
{
}

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
    void record(int set, Cell* cell);

    /**
     * Checks to see if the given cell belongs to a set yet (if not, it assigns
     * it to one) and then returns that set.
     * @param cell
     * @return
     */
    int set_for(Cell* cell);

    /**
     * Moves all cells from the loser set to the winner set.
     * @param winner
     * @param loser
     * @return
     */
    void merge(int winner, int loser);

    /**
     * Returns a new RowState instance, counting sets from where the current
     * instance left off.
     * @return
     */
    RowState next();

    /**
     * Iterates over the sets in the current row, yielding each set and its
     * collection of cells to the attached block.
     * @return
     */
    std::vector<std::vector<Cell *>> each_set();
};

void RowState::record(int set, Cell* cell) {
    set_for_cell[cell->x] = set;

    cells_in_set[set].emplace_back(cell);
}

int RowState::set_for(Cell *cell) {
    if (set_for_cell.find(cell->x) == set_for_cell.end())
    {
        record(next_set, cell);
        next_set += 1;
    }

    return set_for_cell[cell->x];
}

void RowState::merge(int winner, int loser) {
    for (auto cell : cells_in_set[loser])
    {
        set_for_cell[cell->x] = winner;
        cells_in_set[winner].emplace_back(cell);
    }

    cells_in_set[loser].clear();
}

RowState RowState::next() {
    return RowState(next_set);
}

std::vector<std::vector<Cell *>> RowState::each_set() {
    std::vector<std::vector<Cell *>> sets;

    for (auto pair : cells_in_set)
    {
        sets.emplace_back(pair.second);
    }

    return sets;
}

void EllerGen::generate()
{
    RowState row_state;
    auto& cells = maze.getCells();
    int w = maze.getWidth(), h = maze.getHeight();

    // For each row
    for (int y = 0; y < h; ++y)
    {
        // For each cell
        for (int x = 0; x < w; ++x)
        {
            auto cell = &cells[(y * w) + x];

            // Skip the left-most column
            if (cell->left == nullptr)
            {
                continue;
            }

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
