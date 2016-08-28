//
// Created by Nicholas Amor on 12/8/16.
//

#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <string>
#include <iostream>
#include <memory>
#include "maze.h"

namespace mazer {

    /**
     * Deserialises a maze from disk.
     */
    class MazeReader {
    private:
        std::string filename;
    public:
        MazeReader(const std::string &filename);

        std::shared_ptr<Maze> read();
    };

}

#endif
