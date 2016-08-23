//
// Created by Nicholas Amor on 13/8/16.
//

#ifndef MAZER_VECTORWRITER_H
#define MAZER_VECTORWRITER_H

#include <string>
#include "Maze.h"

class VectorWriter {
    std::string filename;
public:
    VectorWriter(const std::string &filename);
    void write(const std::shared_ptr<Maze> &maze);
};


#endif //MAZER_VECTORWRITER_H
