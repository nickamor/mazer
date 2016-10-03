//
// Created by Nicholas Amor on 28/9/16.
//

#include <maze_builder.h>
#include <maze_generator.h>
#include <strong_random.h>

using namespace mazer;

/**
 * Concrete implementation of MazeGenerator that uses the Aldous-Broder algorithm.
 */

AldousBroderGenerator::~AldousBroderGenerator() {

}

std::unique_ptr<Maze>
AldousBroderGenerator::Generate(int seed, int width, int height)
{
    auto rand = StrongRandom(seed);
    int unvisited = (width * height) - 1;
    auto builder = MazeBuilder(width, height);

    CellPos firstRand{rand.Next(0, width - 1), rand.Next(0, height - 1)};

    auto cell = builder.CellAt(firstRand);

    while (unvisited > 0)
    {
        auto &&n = cell->Neighbours();
        int i = rand.Next<int>(0, int(n.size() - 1));
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
