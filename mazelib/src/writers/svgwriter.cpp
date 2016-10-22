//
// Created by nick on 22/10/16.
//

#include <iostream>
#include <fstream>
#include "writer.h"

using namespace mazer;

namespace Svg {
    struct Point {
    public:
        const double x, y;
    };

    static Point origin{0.5, 0.5};

    struct Header {
    public:
        const double w, h;

        friend std::ostream &operator<<(std::ostream &os, const Header &header) {
            os << "<svg viewBox='0 0 ";
            os << header.w + 1 << " ";
            os << header.h + 1 << "' ";
            os << "width='500' height='500' xmlns='http://www.w3.org/2000/svg'>";
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

    struct Background {
    public:
        friend std::ostream &operator<<(std::ostream &os, const Background &) {
            os << "<rect ";
            os << "width='100%' ";
            os << "height='100%' ";
            os << "fill='black' ";
            os << "/>";
            return os;
        }
    };

    struct Line {
    public:
        Line(const Edge& edge) : x1(edge.x1), y1(edge.y1),
                                  x2(edge.x2), y2(edge.y2), special(edge.special) {}

        const double x1, y1, x2, y2;
        const bool special;

        friend std::ostream &operator<<(std::ostream &os, const Line &line) {
            os << "<line ";
            if (line.special)
            {
                os << "stroke='red' ";
            }
            else
            {
                os << "stroke='white' ";
            }
            os << "stroke-width='0.1' ";
            os << "x1='" << origin.x + line.x1 << "' ";
            os << "y1='" << origin.y + line.y1 << "' ";
            os << "x2='" << origin.x + line.x2 << "' ";
            os << "y2='" << origin.y + line.y2 << "' ";
            os << "/>";
            return os;
        }
    };
}

SvgWriter::SvgWriter(const IMaze& maze) : maze(maze) {}

SvgWriter::~SvgWriter() {}

void SvgWriter::write(const std::string &filename)
{
    std::ofstream file(filename);

    file << Svg::Header{double(maze.getWidth()), double(maze.getHeight())} << '\n';

    file << "\t" << Svg::Background() << '\n';

    auto edges = maze.getEdges();

    for (auto& edge : edges)
    {
        file << "\t" << Svg::Line(edge) << '\n';
    }

    file << Svg::Footer() << std::endl;
}
