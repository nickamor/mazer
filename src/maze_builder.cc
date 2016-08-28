//
// Created by Nicholas Amor on 28/8/16.
//

#include "maze_builder.h"
#include <iostream>

using namespace mazer;

Cell::Cell() : north(nullptr), east(nullptr), south(nullptr), west(nullptr) {}

std::vector<Cell *> Cell::Neighbours() {
    std::vector<Cell *> vec;

    if (this->north != nullptr) {
        vec.push_back(this->north);
    }

    if (this->east != nullptr) {
        vec.push_back(this->east);
    }

    if (this->south != nullptr) {
        vec.push_back(this->south);
    }

    if (this->west != nullptr) {
        vec.push_back(this->west);
    }

    return vec;
}

bool Cell::IsLinkedTo(Cell *cell) {
    return std::find(links.begin(), links.end(), cell) != std::end(links);
}

MazeBuilder::MazeBuilder(int width, int height) : width(width), height(height) {
    cells = new Cell[width * height];

    // initialise grid cell links
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            auto cell = CellAt(i, j);

            // north
            if (j > 0) {
                cell->north = CellAt(i, j - 1);
            }

            // east
            if (i < width - 1) {
                cell->east = CellAt(i + 1, j);
            }

            // south
            if (j < height - 1) {
                cell->south = CellAt(i, j + 1);
            }

            // west
            if (i > 0) {
                cell->west = CellAt(i - 1, j);
            }
        }
    }
}

MazeBuilder::~MazeBuilder() {
    delete[] cells;
    cells = nullptr;
}

std::shared_ptr<Maze> MazeBuilder::ToMaze() {
    std::set<Edge> edges;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            auto cell = CellAt(i, j);

            if (!cell->IsLinkedTo(cell->north)) {
                edges.emplace(i, j, i + 1, j);
            }

            if (!cell->IsLinkedTo(cell->east)) {
                edges.emplace(i + 1, j, i + 1, j + 1);
            }

            if (!cell->IsLinkedTo(cell->south)) {
                edges.emplace(i, j + 1, i + 1, j + 1);
            }

            if (!cell->IsLinkedTo(cell->west)) {
                edges.emplace(i, j, i, j + 1);
            }
        }
    }

    return std::make_shared<Maze>(width, height, edges);
}

Cell *MazeBuilder::CellAt(int x, int y) {
    if (!ValidCell(x, y)) {
        throw std::runtime_error("Cell index out of bounds.");
    }

    return &cells[(y * width) + x];
}

void MazeBuilder::AddLink(Cell *lhs, Cell *rhs) {
    lhs->links.push_back(rhs);
    rhs->links.push_back(lhs);
}

void MazeBuilder::AddExits() {
    cells[0].links.push_back(&entry);
    cells[0].west = &entry;

    cells[(width * height) - 1].links.push_back(&exit);
    cells[(width * height) - 1].east = &exit;
}

#ifdef __TEST__

#undef __TEST__
#include "maze.cc"
#define __TEST__

void test_add_links() {
    MazeBuilder builder(2, 2);

    auto cell = builder.CellAt(0, 0);

    builder.AddLink(cell, cell->south);
    cell = cell->south;

    builder.AddLink(cell, cell->east);
    cell = cell->east;

    builder.AddLink(cell, cell->north);

    builder.AddExits();

    auto maze = builder.ToMaze();

    std::cout << maze->ToJsonString() << std::endl;
}

int main() {
    test_add_links();
}

#endif // __TEST__
