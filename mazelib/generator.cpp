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

void Generator::link(Cell *cell, Cell *next)
{
    cell->links.emplace_back(next);
    next->links.emplace_back(cell);
}
