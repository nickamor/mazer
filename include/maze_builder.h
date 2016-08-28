//
// Created by Nicholas Amor on 28/8/16.
//

#ifndef MAZER_MAZE_BUILDER_H
#define MAZER_MAZE_BUILDER_H

#include <vector>
#include "maze.h"

namespace mazer {

    /**
     * A single section of the maze, with possible adjoining cells.
     */
    struct Cell {
        Cell *north, *east, *south, *west;
        std::vector<Cell *> links;

        Cell();

        std::vector<Cell *> neighbours();

        bool is_linked_to(Cell *cell);
    };

    /**
     * Used to construct a maze, composed of a grid of cells which are interconnected.
     */
    class MazeBuilder {
        int width, height;
        Cell *cells;
        Cell entry, exit;

    public:
        MazeBuilder(int width, int height);

        ~MazeBuilder();

        std::shared_ptr <Maze> to_maze();

        Cell *cell_at(int x, int y);

        void add_link(Cell *lhs, Cell *rhs);

        void add_exits();

        inline bool valid_cell(int x, int y) {
            return ((x >= 0 && y >= 0) && (x < width && y < height));
        }
    };

}

#endif //MAZER_MAZE_BUILDER_H
