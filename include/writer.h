//
// Created by Nicholas Amor on 13/8/16.
//

#ifndef MAZER_FILEWRITER_H
#define MAZER_FILEWRITER_H

#include "maze.h"

namespace mazer {

    class writer {
        std::string filename;
    public:
        writer(const std::string &filename);

        void write(std::shared_ptr<maze> maze);
    };

}

#endif //MAZER_FILEWRITER_H
