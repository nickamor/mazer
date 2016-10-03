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
	virtual ~MazeGenerator() = 0;

    virtual std::unique_ptr<Maze>
    Generate(int seed, int width, int height) = 0;

    static std::unique_ptr<MazeGenerator>
    Factory(MazeGeneratorType type = MazeGeneratorType::AldousBroder);
};

class AldousBroderGenerator : public MazeGenerator
{
public:
	~AldousBroderGenerator() override;

	std::unique_ptr<Maze>
    Generate(int seed, int width, int height) override;
};

class EllerGenerator : public MazeGenerator
{
public:
	~EllerGenerator() override;

	std::unique_ptr<Maze>
    Generate(int seed, int width, int height) override;
};

}

#endif //MAZER_GENERATOR_H
