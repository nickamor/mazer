//
// Created by Nicholas Amor on 13/8/16.
//

#ifndef MAZER_MAZESVGWRITER_H
#define MAZER_MAZESVGWRITER_H

#include <string>
#include "maze.h"

namespace mazer
{

/**
 * Writes a vector graphics representation of a maze to disk.
 */
class MazeSvgWriter
{
    std::string filename;
public:
    MazeSvgWriter(const std::string &filename);

    void
    Write(std::shared_ptr<Maze> maze);
};

}

#endif //MAZER_MAZESVGWRITER_H
