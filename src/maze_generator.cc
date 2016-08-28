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
    AldousBroderGenerator(int, int, int);


    /**
     * Generate the maze using Aldous-Broder
     * @return
     */
    std::shared_ptr<Maze> generate();
};

MazeGenerator::MazeGenerator(int seed, int width, int height) : seed(seed), width(width), height(height) {

}

std::shared_ptr<Maze> MazeGenerator::generate() {
    return nullptr;
}

std::shared_ptr<MazeGenerator> MazeGenerator::factory(int seed, int width, int height) {
    return std::make_shared<AldousBroderGenerator>(seed, width, height);
}

AldousBroderGenerator::AldousBroderGenerator(int seed, int width, int height) : MazeGenerator(seed, width, height) {

}

std::shared_ptr<Maze> AldousBroderGenerator::generate() {
    auto rand = StrongRandom(seed);
    int unvisited = (width * height) - 1;
    auto builder = MazeBuilder(width, height);

    auto cell = builder.cell_at(rand.next(0, width - 1), rand.next(0, height - 1));

    while (unvisited > 0) {
        auto neighbours = cell->neighbours();
        auto neighbour = neighbours[rand.next(0, neighbours.size() - 1)];

        if (neighbour) {
            builder.add_link(cell, neighbour);
            unvisited -= 1;
        }

        cell = neighbour;
    }

    builder.add_exits();

    return builder.to_maze();
}

#ifdef __TEST__

#undef __TEST__
#include "strong_random.cc"
#include "maze.cc"
#include "maze_builder.cc"
#define __TEST__

int main() {
    auto gen = MazeGenerator::factory(1, 50, 50);
    auto m = gen->generate();

    std::cout << m << std::endl;
}

#endif
