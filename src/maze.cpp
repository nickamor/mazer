//
// Created by Nicholas Amor on 12/8/16.
//

#include "reader.h"
#include "maze.h"

using namespace mazer;

maze::builder::builder(int width, int height, bool empty) : width(width), height(height) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            cells[i].push_back(cell(i, j, empty));
        }
    }
}

maze::builder::cell &maze::builder::cell_at(int x, int y) {
    return cells[x][y];
}

void maze::builder::add_edge(int x1, int y1, int x2, int y2) {
    // north
    if (y2 > y1) {
        cells[x1][y1].north = true;
        cells[x1][y1 - 1].south = true;
    }
    // east
    if (x2 > x1) {
        cells[x1 - 1][y1].east = true;
        cells[x1][y1].west = true;
    }
    // south
    // west
}

void maze::builder::add_exits() {
    
}

void maze::builder::add_link(int, int, int, int) {

}

std::shared_ptr<maze> maze::builder::to_maze() {
    return nullptr;
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
}

#endif

