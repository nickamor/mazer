//
// Created by Nicholas Amor on 14/10/16.
//

#include <iostream>
#include <random>
#include "mazer.h"

using namespace mazer;

Maze::Maze(const unsigned w, const unsigned h) : w(w), h(h) {
    resize(w, h);
}

Maze::~Maze() {}

void Maze::clear()
{
    cells.clear();
    solution.clear();
}

void Maze::resize(int w, int h)
{
    int num_cells = w * h;

    // Construct a grid of Cells that are interlinked.
    cells.resize(unsigned(num_cells));

    // For every cell in the grid...
    for (int i = 0; i < num_cells; ++i)
    {
        const int x = i % w;
        const int y = i / w;

        cells[i] = Cell(x, y, i);

        // Set the left neighbour
        if (x > 0)
        {
            Cell *cell = &cells[i - 1];
            cells[i].left = cell;
            cells[i].nbrs.push_back(cell);
        }

        // Set the right neighbour
        if (x < w - 1)
        {
            Cell *cell = &cells[i + 1];
            cells[i].right = cell;
            cells[i].nbrs.push_back(cell);
        }

        // Set the north neighbour
        if (y > 0)
        {
            Cell *cell = &cells[i - w];
            cells[i].up = cell;
            cells[i].nbrs.push_back(cell);
        }

        // Set the south neighbour
        if (y < h - 1)
        {
            Cell *cell = &cells[i + w];
            cells[i].down = cell;
            cells[i].nbrs.push_back(cell);
        }
    }
}

std::vector<Cell> &Maze::getCells()
{
    return cells;
}

int Maze::getWidth()
{
    return w;
}

int Maze::getHeight()
{
    return h;
}

const std::deque<Cell *> &Maze::getSolution()
{
    return solution;
}

std::set<Edge> Maze::getEdges()
{
    std::set<Edge> edges;

    auto isLinked = [](const Cell* lhs, const Cell* rhs) {
        auto f = std::find(std::begin(lhs->links), std::end(lhs->links), rhs);
        return f != std::end(lhs->links);
    };

    for (auto& cell : cells)
    {
        if (!isLinked(&cell, cell.up))
        {
            edges.emplace(cell.x, cell.y, cell.x + 1, cell.y);
        }
        if (!isLinked(&cell, cell.down))
        {
            edges.emplace(cell.x, cell.y + 1, cell.x + 1, cell.y + 1);
        }
        if (!isLinked(&cell, cell.left))
        {
            edges.emplace(cell.x, cell.y, cell.x, cell.y + 1);
        }
        if (!isLinked(&cell, cell.right))
        {
            edges.emplace(cell.x + 1, cell.y, cell.x + 1, cell.y + 1);
        }
    }

    return edges;
}

void Maze::setSolution(const std::deque<Cell *> &path)
{
    solution = path;
}
