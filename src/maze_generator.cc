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
class AldousBroderGenerator : public MazeGenerator {
public:
    AldousBroderGenerator(int seed, int width, int height) : MazeGenerator(seed, width, height) {

    }

    /**
     * Generate the maze using Aldous-Broder
     * @return
     */
    std::shared_ptr<Maze> Generate() override {
        auto rand = StrongRandom(seed);
        int unvisited = (width * height) - 1;
        auto builder = MazeBuilder(width, height);

        auto cell = builder.CellAt(rand.Next(0, width - 1), rand.Next(0, height - 1));

        while (unvisited > 0) {
            auto &&n = cell->Neighbours();
            int i = rand.Next<int>(0, n.size() - 1);
            auto random_n = n[i];

            if (random_n->links.size() == 0) {
                builder.AddLink(cell, random_n);
                unvisited -= 1;
            }

            cell = random_n;
        }

        builder.AddExits();

        return builder.ToMaze();
    }
};

MazeGenerator::MazeGenerator(int seed, int width, int height) : seed(seed), width(width), height(height) {

}

std::shared_ptr<Maze> MazeGenerator::Generate() {
    return nullptr;
}

std::shared_ptr<MazeGenerator> MazeGenerator::Factory(int seed, int width, int height) {
    return std::make_shared<AldousBroderGenerator>(seed, width, height);
}

#ifdef __TEST__

#undef __TEST__
#include "strong_random.cc"
#include "maze.cc"
#include "maze_builder.cc"
#define __TEST__

int main() {
    auto gen = MazeGenerator::Factory(1, 50, 50);
    auto m = gen->Generate();

    std::cout << m << std::endl;
}

#endif
