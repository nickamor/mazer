//
// Created by Nicholas Amor on 14/10/16.
//

#ifndef LIBMAZER_GENERATOR_H
#define LIBMAZER_GENERATOR_H

#include <random>
#include "maze.h"

namespace mazer
{

class Generator
{
  public:
    Generator(IMaze& maze);
    virtual ~Generator() = 0;

    virtual void generate() = 0;

    void seed(const int s);

    void link(Cell* cell, Cell* next);

  protected:
    int nextRand(int min, int max);

    IMaze& maze;

    std::mt19937 engine;
};

class AldousBroderGen
    : public Generator
{
  public:
    AldousBroderGen(IMaze& maze);
    ~AldousBroderGen();

    void generate();
};

class EllerGen
    : public Generator
{
public:
    EllerGen(IMaze& maze);
    ~EllerGen();

    void generate();
};
}

#endif //LIBMAZER_GENERATOR_H