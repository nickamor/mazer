//
// Created by Nicholas Amor on 14/10/16.
//

#include "generator.h"

using namespace mazer;

Generator::Generator(IMaze &maze) : maze(maze)
{
    engine.seed(unsigned(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
}

Generator::~Generator() {}

void Generator::generate() {}

/**
 * Get a random number within a range.
 * @param min
 * @param max
 * @return
 */
int Generator::nextRand(int min, int max)
{
    return std::uniform_int_distribution<int>(min, max)(engine);
}

void Generator::seed(const int s)
{
    engine.seed(unsigned(s));
}

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
            cell->links.push_back(next);
            next->links.push_back(cell);
            unvisited--;
        }

        cell = next;
    }
}

EllerGen::EllerGen(IMaze &maze)
    : Generator(maze)
{
}

EllerGen::~EllerGen()
{
}
