//
// Created by Nicholas Amor on 25/8/16.
//

#ifndef MAZER_RANDOM_H
#define MAZER_RANDOM_H

#include <random>

class Random {
    std::mt19937 engine;
public:
    Random(int seed);

    int next(int floor, int ciel);
};

#endif //MAZER_RANDOM_H
