//
// Created by Nicholas Amor on 13/8/16.
//

#include "generator.h"
#include "strong_random.h"

using namespace mazer;

class aldous_broder_generator : public generator {
public:
    aldous_broder_generator(int, int, int);

    std::shared_ptr<maze> generate();

    static std::shared_ptr<generator> create(int, int, int);
};

generator::generator(int seed, int width, int height) : seed(seed), width(width), height(height) {

}

std::shared_ptr<maze> generator::generate() {
    return nullptr;
}

std::shared_ptr<generator> generator::factory(int seed, int width, int height) {
    return aldous_broder_generator::create(seed, width, height);
}

aldous_broder_generator::aldous_broder_generator(int seed, int width, int height) : generator(seed, width, height) {

}

std::shared_ptr<generator> aldous_broder_generator::create(int seed, int width, int height) {
    return std::make_shared<aldous_broder_generator>(seed, width, height);
}

std::shared_ptr<maze> aldous_broder_generator::generate() {
    auto rand = strong_random(seed);
    int unvisited = (width * height) - 1;
    auto builder = maze_builder(width, height);

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

    return builder.to_maze();
}

#ifdef __TEST__

#undef __TEST__
#include "strong_random.cpp"
#include "maze.cpp"
#define __TEST__

int main() {
    auto gen = generator::factory(1, 50, 50);
    auto m = gen->generate();

    std::cout << m << std::endl;
}

#endif
