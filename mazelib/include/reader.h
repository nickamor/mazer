//
// Created by Nicholas Amor on 14/10/16.
//

#ifndef MAZELIB_READER_H
#define MAZELIB_READER_H

#include <stdexcept>
#include <string>
#include "maze.h"

namespace mazer
{

    class FileNotReadable : std::runtime_error
    {
    public:
        FileNotReadable(const std::string& filename)
                : std::runtime_error("Failed to open file for reading: " + filename) {}
    };

class IReader
{
  public:
    virtual ~IReader() = 0;
    virtual void read(const std::string &filename) = 0;
};

class BinaryReader
    : public IReader
{
  public:
    BinaryReader(IMaze& maze);
    ~BinaryReader();
    void read(const std::string &filename);

private:
    IMaze& maze;
};
}

#endif //MAZELIB_READER_H
