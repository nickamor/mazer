//
// Created by Nicholas Amor on 13/8/16.
//
#include "Maze.h"

#ifndef MAZER_FILEWRITER_H
#define MAZER_FILEWRITER_H

class FileWriter {
    std::string filename;
public:
    FileWriter(const std::string &filename);
    void write(const std::shared_ptr <Maze> &maze);
};


#endif //MAZER_FILEWRITER_H
