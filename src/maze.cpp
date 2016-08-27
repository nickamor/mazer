//
// Created by Nicholas Amor on 12/8/16.
//

#include "reader.h"
#include "maze.h"
#include <stdexcept>
#include <iostream>

using namespace mazer;

maze::maze(int width, int height, std::vector<edge> edges) : width(width), height(height), edges(edges) {

}

maze_builder::maze_builder(int width, int height, bool no_links) : width(width), height(height) {
    cells = new cell[width * height];

    if (!no_links) {
        // initialise grid cell links
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                cell& cell = *cell_at(i, j);

                std::cout << i << " " << j << std::endl;

                // north
                if (j > 0) {
                    std::cout << i << " " << j << std::endl;
                    cell.north = cell_at(i, j - 1);
                }

                // east
                if (i < width - 1) {
                    cell.east = cell_at(i + 1, j);
                }

                // south
                if (j < height - 1) {
                    cell.south = cell_at(i, j + 1);
                }

                // west
                if (i > 0)
                {
                    cell.west = cell_at(i - 1, j);
                }
            }
        }
    }
}

maze_builder::~maze_builder() {
    delete[] cells;
    cells = nullptr;
}

std::shared_ptr<maze> maze_builder::to_maze() {
    std::vector<edge> edges;

    for (int i = 0; i < width; ++i)
    {
        /* code */
    }

    return nullptr;
}

cell* maze_builder::cell_at(int x, int y) {
    if (!valid_cell(x, y)) {
        throw std::runtime_error("Cell index out of bounds.");
    }
    return &cells[(y * width) + x];
}

void maze_builder::add_edge(int, int, int, int) {
    // find and disconnect the cells bisected by this edge
}

void maze_builder::add_link(int x1, int y1, int x2, int y2) {
    cell_at(x1, y1)->links.push_back(cell_at(x2, y2));
    cell_at(x2, y2)->links.push_back(cell_at(x1, y1));
}

void maze_builder::add_exits() {

}

std::vector<cell *> cell::neighbours() {
    std::vector<cell *> n;

    if (this->north) n.push_back(this->north);
    if (this->east) n.push_back(this->east);
    if (this->south) n.push_back(this->south);
    if (this->west) n.push_back(this->west);

    return n;
}

#ifdef __TEST__

#include <iostream>

void test_add_edges() {
    auto builder = maze::builder(2, 2, true);

    /**
     *   |  |  |
     *   |_____|
     **/

    // clockwise outer edges
    // builder.add_edge(0, 0, 0, 1);
    // builder.add_edge(0, 1, 1, 2);

    builder.add_edge(0, 2, 1, 2);
    builder.add_edge(1, 2, 2, 2);

    builder.add_edge(2, 0, 2, 1);
    builder.add_edge(2, 1, 2, 2);

    builder.add_edge(0, 0, 1, 0);
    builder.add_edge(1, 0, 1, 2);

    // clockwise inner edges
    builder.add_edge(0, 1, 1, 1);
    // builder.add_edge(1, 1, 1, 2);
    // builder.add_edge(1, 1, 2, 1);
    // builder.add_edge(1, 1, 1, 0);

    auto maze = builder.to_maze();

    std::cout << maze << std::endl;
}

void test_add_links() {
    maze::builder builder(2, 2);

    builder.add_link(0, 0, 0, 1);
    builder.add_link(0, 1, 1, 1);
    builder.add_link(1, 1, 1, 0);

    builder.add_exits();

    auto maze = builder.to_maze();

    std::cout << maze << std::endl;
}

int main() {
    test_add_edges();
    test_add_links();
}

#endif

