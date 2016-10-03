//
// Created by Nicholas Amor on 12/8/16.
//

#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "maze.h"

namespace mazer
{

	class InvalidMaze : public std::invalid_argument
	{
	};

	class MazeFileNotFound : public std::runtime_error
	{
	};

/**
 * Deserialises a maze from disk.
 */
class MazeReader
{
private:
    std::string filename;
public:
    MazeReader(const std::string &filename);

    // TODO: use weak_ptr here
    std::shared_ptr<Maze>
    Read() throw (InvalidMaze, MazeFileNotFound);
};

}

#endif
