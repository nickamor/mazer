//
// Created by Nicholas Amor on 25/8/16.
//

#include "strong_random.h"

using namespace mazer;

StrongRandom::StrongRandom(int seed)
{
    engine = std::mt19937(seed);
}

#ifdef __TEST__

#include <iostream>
#include <chrono>

int main() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rand = StrongRandom(seed);

    std::cout << "Rand(0,1): \t"    << rand.Next(0  , 1)    << std::endl;
    std::cout << "Rand(1,100): \t"  << rand.Next(1  , 100)  << std::endl;
    std::cout << "Rand(-32,32): \t" << rand.Next(-32, 32)   << std::endl;
    std::cout << "Rand(0,4096): \t" << rand.Next(0  , 4096) << std::endl;

    // Guarantee inclusive range
    while (!rand.Next(0, 1));
    while (rand.Next(0, 1));

    int dist1[2], dist2[2];
    for (int i = 0; i < 2; ++i)
    {
        dist1[0] = 0;
        dist2[0] = 0;
    }

    std::cout << std::endl;

    // Compare distribution
    std::mt19937 engine(seed);
    std::uniform_int_distribution<> distro(0, 1);
    for (int i = 0; i < 1000000; ++i)
    {
        int r1 = rand.Next(0, 1), r2 = distro(engine);
        dist1[r1]++;
        dist2[r2]++;
    }

    for (int i = 0; i < 2; ++i)
    {
        std::cout << i << ": " << dist1[i] << " - " << dist2[i] << std::endl;
    }
}

#endif
