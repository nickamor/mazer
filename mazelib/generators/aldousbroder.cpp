//
// Created by Nicholas Amor on 21/10/16.
//

#include "generator.h"

using namespace mazer;

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
