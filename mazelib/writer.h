//
// Created by Nicholas Amor on 14/10/16.
//

#ifndef LIBMAZER_WRITER_H
#define LIBMAZER_WRITER_H

#include <string>

namespace mazer
{

class IWriter
{
public:
    virtual ~IWriter() = 0;
    virtual void write(const std::string& filename) = 0;
};

class BinaryWriter
    : public IWriter
{
public:
};

class VectorWriter
    : public IWriter
{
public:
};
}

#endif //LIBMAZER_WRITER_H
