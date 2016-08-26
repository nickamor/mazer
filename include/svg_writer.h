//
// Created by Nicholas Amor on 13/8/16.
//

#ifndef MAZER_VECTORWRITER_H
#define MAZER_VECTORWRITER_H

#include <string>
#include "maze.h"

namespace mazer {

    class svg_writer {
        std::string filename;
    public:
        svg_writer(const std::string &filename);

        void write(std::shared_ptr<maze> maze);
    };

}

#endif //MAZER_VECTORWRITER_H
