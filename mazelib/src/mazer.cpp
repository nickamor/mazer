//
// Created by Nicholas Amor on 14/10/16.
//

#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>
#include "mazer.h"

using namespace mazer;

Maze::Maze(const unsigned w, const unsigned h) : w(w), h(h)
{
    resize(w, h);
}

Maze::~Maze() {}

void Maze::clear()
{
    for (auto& cell : cells)
    {
        cell.links.clear();
        cell.nbrs.clear();
    }
    cells.clear();
    solution.clear();
}

void Maze::resize(int w, int h)
{
    int cellCount = w * h;

    // Construct a grid of Cells that are interlinked.
    cells.resize(unsigned(cellCount));

    // For every cell in the grid...
    for (int i = 0; i < cellCount; ++i)
    {
        const int x = i % w;
        const int y = i / w;

        auto& cell = cells[i];
        cell.i = i;
        cell.x = x;
        cell.y = y;

        // Set the left neighbour
        if (x > 0)
        {
            auto next = &cells[i - 1];
            cell.left = next;
            cell.nbrs.emplace_back(next);
        }

        // Set the right neighbour
        if (x < w - 1)
        {
            auto next = &cells[i + 1];
            cell.right = next;
            cell.nbrs.emplace_back(next);
        }

        // Set the north neighbour
        if (y > 0)
        {
            auto next = &cells[i - w];
            cell.up = next;
            cell.nbrs.emplace_back(next);
        }

        // Set the south neighbour
        if (y < h - 1)
        {
            auto next = &cells[i + w];
            cell.down = next;
            cell.nbrs.emplace_back(next);
        }
    }
}

int Maze::getWidth() const
{
    return w;
}

int Maze::getHeight() const
{
    return h;
}

std::vector<Cell> &Maze::getCells()
{
    return cells;
}

Cell &Maze::getCell(int x, int y) {
    return cells[(y * w) + x];
}

Cell &Maze::getCell(int i) {
    return cells[i];
}

void Maze::link(Cell *lhs, Cell *rhs)
{
    if (lhs == nullptr || rhs == nullptr)
    {
        throw std::invalid_argument("cell arguments must not be null");
    }

    lhs->links.emplace_back(rhs);
    rhs->links.emplace_back(lhs);
}

const std::deque<Cell *> &Maze::getSolution()
{
    return solution;
}

std::set<Edge> Maze::getEdges() const
{
    std::set<Edge> edges;

    auto emplaceCell = [](std::set<Edge>& edges, const Cell& cell, bool special)
    {
        if (!cell.linkedTo(cell.up))
        {
            edges.emplace(Edge{cell.x, cell.y, cell.x + 1, cell.y, special});
        }
        if (!cell.linkedTo(cell.down))
        {
            edges.emplace(Edge{cell.x, cell.y + 1, cell.x + 1, cell.y + 1, special});
        }
        if (!cell.linkedTo(cell.left))
        {
            edges.emplace(Edge{cell.x, cell.y, cell.x, cell.y + 1, special});
        }
        if (!cell.linkedTo(cell.right))
        {
            edges.emplace(Edge{cell.x + 1, cell.y, cell.x + 1, cell.y + 1, special});
        }
    };

    for (auto& cell : solution)
    {
        emplaceCell(edges, *cell, true);
    }

    for (auto& cell : cells)
    {
        emplaceCell(edges, cell, false);
    }

    return edges;
}

void Maze::setSolution(const std::deque<Cell *> &path)
{
    solution = path;
}
