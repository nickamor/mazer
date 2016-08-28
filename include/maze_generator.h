//
// Created by Nicholas Amor on 13/8/16.
//

#ifndef MAZER_GENERATOR_H
#define MAZER_GENERATOR_H

#include <memory>
#include "maze.h"

namespace mazer {

    /**
     * Generates a random maze.
     */
    class MazeGenerator {
    protected:
        int seed, width, height;

        MazeGenerator(int seed, int width, int height);

    public:
        virtual std::shared_ptr<Maze> generate() = 0;

        static std::shared_ptr<MazeGenerator> factory(int seed, int width, int height);
    };

}


#endif //MAZER_GENERATOR_H
