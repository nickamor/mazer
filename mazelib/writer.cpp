//
// Created by Nicholas Amor on 14/10/16.
//

#include <ostream>
#include "writer.h"

using namespace mazer;

class Svg
{
public:
    struct Header {
    public:
        friend std::ostream &operator<<(std::ostream &os, const Header &) {
            os << "<svg>";
            return os;
        }
    };

    struct Footer {
    public:
        friend std::ostream &operator<<(std::ostream &os, const Footer &) {
            os << "</svg>";
            return os;
        }
    };

    struct Box {
    public:
        const int x, y, w, h;

        friend std::ostream &operator<<(std::ostream &os, const Box &box) {
            os << "x: " << box.x << " y: " << box.y << " w: " << box.w << " h: " << box.h;
            return os;
        }
    };

    struct Line {
    public:
        const int x1, y1, x2, y2;

        friend std::ostream &operator<<(std::ostream &os, const Line &line) {
            os << "x1: " << line.x1 << " y1: " << line.y1 << " x2: " << line.x2 << " y2: " << line.y2;
            return os;
        }
    };
};

IWriter::~IWriter() {}

void IWriter::write(const std::string &) {}

