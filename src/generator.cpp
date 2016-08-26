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
//	auto grid = std::make_shared<maze_grid>(width, height);
    int unvisited = width * height;
//	auto out_maze = std::make_shared<maze>();
    maze::builder builder(width, height);

    auto& cell = builder.cell_at(rand.next(0, width), rand.next(0, height));

    while (unvisited > 0) {

    }

    return builder.to_maze();
}

#ifdef __TEST__

int main() {}

#endif
