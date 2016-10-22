//
// Created by Nicholas Amor on 14/10/16.
//

#include <algorithm>
#include <iostream>
#include <random>
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
    int num_cells = w * h;

    // Construct a grid of Cells that are interlinked.
    cells.resize(unsigned(num_cells));

    // For every cell in the grid...
    for (int i = 0; i < num_cells; ++i)
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

    for (auto &cell : cells)
    {
        if (!cell.linkedTo(cell.up))
        {
            edges.emplace(cell.x, cell.y, cell.x + 1, cell.y);
        }
        if (!cell.linkedTo(cell.down))
        {
            edges.emplace(cell.x, cell.y + 1, cell.x + 1, cell.y + 1);
        }
        if (!cell.linkedTo(cell.left))
        {
            edges.emplace(cell.x, cell.y, cell.x, cell.y + 1);
        }
        if (!cell.linkedTo(cell.right))
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
