//
// Created by Nicholas Amor on 25/8/16.
//

#ifndef MAZER_RANDOM_H
#define MAZER_RANDOM_H

#include <random>

namespace mazer
{

/**
 * Facade to random number engine.
 */
class StrongRandom
{
    std::mt19937 engine;
public:
    StrongRandom(int seed);

    /**
     * Return the next value from the random number generator.
     * @param floor range minimum, inclusive
     * @param ciel range maximum, inclusive
     * @return T n, where n >= floor and n <= ciel.
     */
    template<class IntType = int>
    inline IntType
    Next(IntType floor, IntType ciel)
    {
        return std::uniform_int_distribution<IntType>(floor, ciel)(engine);
    }

    inline bool
    NextBool()
    {
        return Next(0, 1);
    }
};

}

#endif //MAZER_RANDOM_H
