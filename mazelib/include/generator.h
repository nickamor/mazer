//
// Created by Nicholas Amor on 14/10/16.
//

#ifndef MAZELIB_GENERATOR_H
#define MAZELIB_GENERATOR_H

#include <random>
#include "maze.h"

namespace mazer
{

class Generator
{
  public:
    Generator(IMaze &maze);
    virtual ~Generator() = 0;

    virtual void generate() = 0;

    void seed(const int s);

  protected:
    int nextRand(int min, int max);

    IMaze &maze;

    std::mt19937 engine;
};

class AldousBroderGen
    : public Generator
{
  public:
    AldousBroderGen(IMaze &maze);
    ~AldousBroderGen();

    void generate();
};

class EllerGen
    : public Generator
{
  public:
    EllerGen(IMaze &maze);
    ~EllerGen();

    void generate();
};
}

#endif //MAZELIB_GENERATOR_H
