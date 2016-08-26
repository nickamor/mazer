//
// Created by Nicholas Amor on 13/8/16.
//

#ifndef MAZER_GENERATOR_H
#define MAZER_GENERATOR_H

#include <memory>
#include "maze.h"

namespace mazer {

    class generator {
    protected:
        int seed, width, height;

        generator(int seed, int width, int height);

    public:
        virtual std::shared_ptr<maze> generate() = 0;

        static std::shared_ptr<generator> factory(int seed, int width, int height);
    };

}


#endif //MAZER_GENERATOR_H
