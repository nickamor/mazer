//
// Created by Nicholas Amor on 14/10/16.
//

#include <chrono>
#include <stdexcept>
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
    if (min < 0)
    {
        throw std::invalid_argument("min must be greater than or equal to zero.");
    }

    if (min >= max)
    {
        throw std::invalid_argument("max must exceed min");
    }

    return std::uniform_int_distribution<int>(min, max)(engine);
}

void Generator::seed(const int s)
{
    engine.seed(unsigned(s));
}
