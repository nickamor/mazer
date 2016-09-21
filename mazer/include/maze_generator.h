//
// Created by Nicholas Amor on 13/8/16.
//

#ifndef MAZER_GENERATOR_H
#define MAZER_GENERATOR_H

#include <memory>
#include "maze.h"

namespace mazer
{

enum class MazeGeneratorType
{
    AldousBroder,
    Eller
};

/**
 * Generates a random maze.
 */
class MazeGenerator
{
public:
    virtual std::shared_ptr<Maze>
    Generate(int seed, int width, int height) = 0;

    static std::shared_ptr<MazeGenerator>
    Factory(MazeGeneratorType type = MazeGeneratorType::AldousBroder);
};

}

#endif //MAZER_GENERATOR_H
