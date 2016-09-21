//
// Created by Nicholas Amor on 13/8/16.
//

#include "maze_generator.h"
#include "strong_random.h"
#include "maze_builder.h"

using namespace mazer;

/**
 * Concrete implementation of MazeGenerator that uses the Aldous-Broder algorithm.
 */
class AldousBroderGenerator : public MazeGenerator
{
public:

    /**
     * Generate the maze using Aldous-Broder
     * @return
     */
    std::shared_ptr<Maze>
    Generate(int seed, int width, int height) override
    {
        auto rand = StrongRandom(seed);
        int unvisited = (width * height) - 1;
        auto builder = MazeBuilder(width, height);

        auto cell = builder.CellAt(rand.Next(0, width - 1), rand.Next(0, height - 1));

        while (unvisited > 0)
        {
            auto &&n = cell->Neighbours();
            int i = rand.Next<int>(0, (int) (n.size() - 1));
            auto random_n = n[i];

            if (random_n->links.size() == 0)
            {
                builder.AddLink(cell, random_n);
                unvisited -= 1;
            }

            cell = random_n;
        }

        builder.AddExits();

        return builder.ToMaze();
    }
};

class EllerGenerator : public MazeGenerator
{
public:
    std::shared_ptr<Maze>
    Generate(int seed, int width, int height) override
    {
        MazeBuilder builder(width, height);
        StrongRandom rand(seed);

        for (int i = 0; i < height; ++i)
        {
            // if not last row
            if (i < width - 1)
            {
                // join sets
                for (int j = 0; j < width - 1; ++j)
                {
                    bool join = rand.NextBool();

                    if (join)
                    {
                        builder.AddLink(CellPos{i, j}, CellPos{i + 1, j});
                    }
                }

                // trickle down
                for (int j = 0; j < width; ++j)
                {
                    bool join = rand.NextBool();

                    if (join)
                    {
                        builder.AddLink(CellPos{i, j}, CellPos{i, j + 1});
                    }
                }
            }
            else
            {
                // join up
                for (int j = 0; j < width; ++j)
                {
                    builder.AddLink(CellPos{i, j}, CellPos{i - 1, j});
                }
            }
        }

        builder.AddExits();

        return builder.ToMaze();
    }
};

std::shared_ptr<Maze>
MazeGenerator::Generate(int, int, int)
{
    return nullptr;
}

std::shared_ptr<MazeGenerator>
MazeGenerator::Factory(MazeGeneratorType type)
{
    switch (type)
    {
        case MazeGeneratorType::AldousBroder:return std::make_shared<AldousBroderGenerator>();
        case MazeGeneratorType::Eller:return std::make_shared<EllerGenerator>();
    }
}
