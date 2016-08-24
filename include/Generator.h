//
// Created by Nicholas Amor on 13/8/16.
//

#include <memory>
#include "Maze.h"

#ifndef MAZER_GENERATOR_H
#define MAZER_GENERATOR_H

class Generator {
public:
    Generator(int, int, int);
    virtual std::shared_ptr<Maze> generate() = 0;
};

class AldousBroderGenerator : public Generator {
public:
    AldousBroderGenerator(int, int, int);

    std::shared_ptr<Maze> generate();
};


#endif //MAZER_GENERATOR_H
