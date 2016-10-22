//
// Created by Nicholas Amor on 14/10/16.
//

#ifndef LIBMAZER_WRITER_H
#define LIBMAZER_WRITER_H

#include <stdexcept>
#include <string>
#include "maze.h"

namespace mazer
{

class FailedOpeningFileException
    : public std::runtime_error
{
  public:
    FailedOpeningFileException(const std::string &filename)
        : std::runtime_error("Failed to open file: " + filename){};
};

class IWriter
{
  public:
    virtual ~IWriter() = 0;
    virtual void write(const std::string &filename) = 0;
};

class BinWriter
    : public IWriter
{
  public:
    BinWriter(const IMaze &maze);
    void write(const std::string &filename);

  private:
    const IMaze &maze;
};

class SvgWriter
    : public IWriter
{
  public:
};
}

#endif //LIBMAZER_WRITER_H
