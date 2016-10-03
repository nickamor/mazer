//
// Created by Nicholas Amor on 13/8/16.
//

#include <map>
#include "maze_generator.h"
#include "strong_random.h"
#include "maze_builder.h"

using namespace mazer;

MazeGenerator::~MazeGenerator()
{

}

std::unique_ptr<Maze>
MazeGenerator::Generate(int, int, int)
{
    return nullptr;
}

std::unique_ptr<MazeGenerator>
MazeGenerator::Factory(MazeGeneratorType type)
{
    switch (type)
    {
        case MazeGeneratorType::AldousBroder:return std::make_unique<AldousBroderGenerator>();
        case MazeGeneratorType::Eller:return std::make_unique<EllerGenerator>();
    }
}
