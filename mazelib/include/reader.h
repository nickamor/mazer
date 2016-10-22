//
// Created by Nicholas Amor on 14/10/16.
//

#ifndef LIBMAZER_READER_H
#define LIBMAZER_READER_H

#include <string>
#include "maze.h"

namespace mazer
{

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
    ~BinaryReader();
    void read(const std::string &filename);
};
}

#endif //LIBMAZER_READER_H
