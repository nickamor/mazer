//
// Created by Nicholas Amor on 13/8/16.
//

#include <memory>
#include "Maze.h"

#ifndef MAZER_GENERATOR_H
#define MAZER_GENERATOR_H

class Generator {
protected:
	int seed, width, height;
public:
    Generator(int seed = -1, int width = 50, int height = 50);
    virtual std::shared_ptr<Maze> generate() = 0;
};

class AldousBroderGenerator : public Generator {
public:
    AldousBroderGenerator(int, int, int);

    std::shared_ptr<Maze> generate();
};


#endif //MAZER_GENERATOR_H
