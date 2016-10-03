//
// Created by Nicholas Amor on 28/8/16.
//

#ifndef MAZER_MAZE_BUILDER_H
#define MAZER_MAZE_BUILDER_H

#include <algorithm>
#include <vector>
#include "maze.h"

namespace mazer
{

/**
 * A single section of the maze, with possible adjoining cells.
 */
    // TODO: evaluate non-intrusive datastructure for grid?
struct Cell
{
    Cell *north, *east, *south, *west;
    std::vector<Cell *> links;

    Cell();

    // TODO: hand out shared_ptrs instead of raw pointers
    std::vector<Cell *>
    Neighbours();

    inline bool
    IsLinkedTo(Cell *cell)
    {
        return std::find(links.begin(), links.end(), cell) != std::end(links);
    }
};

/**
 *
 */
struct CellPos
{
    int x, y;
};

/**
 * Used to construct a maze, composed of a grid of cells which are interconnected.
 */
class MazeBuilder
{
    int width, height;
    // TODO: use const vector or vector<unique_ptr> for cell storage
    Cell *cells;
    Cell entry, exit;

public:
    MazeBuilder(int width, int height);

    ~MazeBuilder();

    std::unique_ptr<Maze>
    ToMaze();

    Cell *
    CellAt(int x, int y);

    Cell *
    CellAt(CellPos pos);

    void
    AddLink(Cell *lhs, Cell *rhs);

    void
    AddLink(CellPos lhs, CellPos rhs);

    void
    AddExits();

    inline bool
    ValidCell(int x, int y)
    {
        return ((x >= 0 && y >= 0) && (x < width && y < height));
    }
};

}

#endif //MAZER_MAZE_BUILDER_H