//
// Created by Nicholas Amor on 12/8/16.
//

#include "reader.h"
#include "maze.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace mazer;

edge::point::point(int x, int y) : x(x), y(y) {}

edge::edge(int x1, int y1, int x2, int y2) : src(x1, y1), dst(x2, y2) {}

cell::cell() : north(nullptr), east(nullptr), south(nullptr), west(nullptr) {}

maze::maze(int width, int height, std::set<edge> edges) : width(width), height(height), edges(edges) {}

std::string maze::to_json_string() {
    std::stringstream out;
    out << "{" << std::endl;

    out << "\t\"width\": " << width << "," << std::endl;
    out << "\t\"height\": " << height << "," << std::endl;
    out << "\t\"num_edges\": " << edges.size() << "," << std::endl;

    out << "\t\"edges\": [" << std::endl;
    for (auto iter = edges.begin(); iter != edges.end(); ++iter) {
        auto& edge = *iter;
        out << "\t\t{ ";

        out << "\"x1\": " << edge.src.x << ", ";
        out << "\"y1\": " << edge.src.y << ", ";
        out << "\"x2\": " << edge.dst.x << ", ";
        out << "\"y2\": " << edge.dst.y;

        if (iter != std::end(edges)) {
            out << " }," << std::endl;
        } else {
            out << " }" << std::endl;
        }
    }
    out << "\t]" << std::endl;
    out << "}" << std::endl;

    return out.str();
}

maze_builder::maze_builder(int width, int height) : width(width), height(height) {
    cells = new cell[width * height];

    // initialise grid cell links
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            cell& cell = *cell_at(i, j);

            // north
            if (j > 0) {
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

maze_builder::~maze_builder() {
    delete[] cells;
    cells = nullptr;
}

std::shared_ptr<maze> maze_builder::to_maze() {
    std::set<edge> edges;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            auto& cell = *cell_at(i, j);
            auto& links = cell.links;

            auto north_ln = std::find(links.begin(), links.end(), cell.north);
            auto east_ln = std::find(links.begin(), links.end(), cell.east);
            auto south_ln = std::find(links.begin(), links.end(), cell.south);
            auto west_ln = std::find(links.begin(), links.end(), cell.west);

            if (north_ln == std::end(links)) {
                std::cout << "north edge" << std::endl;
                edges.emplace(i, j, i + 1, j);
            }

            if (east_ln == std::end(links)) {
                std::cout << "east edge" << std::endl;
                edges.emplace(i + 1, j, i + 1, j + 1);
            }

            if (south_ln == std::end(links)) {
                std::cout << "south edge" << std::endl;
                edges.emplace(i, j + 1, i + 1, j + 1);
            }

            if (west_ln == std::end(links)) {
                std::cout << "west edge" << std::endl;
                edges.emplace(i, j, i, j + 1);
            }

            std::cout << links.size() << " links" << std::endl;
        }
    }

    return std::make_shared<maze>(width, height, edges);
}

cell* maze_builder::cell_at(int x, int y) {
    if (!valid_cell(x, y)) {
        throw std::runtime_error("Cell index out of bounds.");
    }

    return &cells[(y * width) + x];
}

void maze_builder::add_link(cell* lhs, cell* rhs) {
    lhs->links.push_back(rhs);
    rhs->links.push_back(lhs);
}

void maze_builder::add_exits() {
    cells[0].links.push_back(&entry);
    cells[0].west = &entry;

    cells[(width * height) - 1].links.push_back(&exit);
    cells[(width * height) - 1].east = &exit;
}

std::vector<cell *> cell::neighbours() {
    std::vector<cell *> vec;

    if (this->north) {
        vec.push_back(this->north);
    }

    if (this->east) {
        vec.push_back(this->east);
    }

    if (this->south) {
        vec.push_back(this->south);
    }

    if (this->west) {
        vec.push_back(this->west);
    }

    return vec;
}

#ifdef __TEST__

#include <iostream>

void test_add_edges() {
    int width = 2;
    int height = 2;
    std::set<edge> edges;

    /**
     *   |  |  |
     *   |_____|
     **/

    edges.emplace(0, 2, 1, 2);
    edges.emplace(1, 2, 2, 2);

    edges.emplace(2, 0, 2, 1);
    edges.emplace(2, 1, 2, 2);

    edges.emplace(0, 0, 1, 0);
    edges.emplace(1, 0, 1, 2);

    edges.emplace(0, 1, 1, 1);

    maze maze(width, height, edges);

    std::cout << maze.to_json_string() << std::endl;
}

void test_add_links() {
    maze_builder builder(2, 2);

    auto cell = builder.cell_at(0, 0);

    cell->add_link(cell->south);
    cell = cell->south;

    // cell->add_link(cell->east);
    // cell = cell->east;

    // cell->add_link(cell->north);

    // builder.add_exits();

    auto maze = builder.to_maze();

    std::cout << maze->to_json_string() << std::endl;
}

int main() {
    test_add_edges();
    test_add_links();
}

#endif

