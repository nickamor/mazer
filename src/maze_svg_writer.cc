//
// Created by Nicholas Amor on 13/8/16.
//

#include <fstream>
#include "maze_svg_writer.h"

using namespace mazer;

MazeSvgWriter::MazeSvgWriter(const std::string &filename) : filename(filename)
{

}

void
MazeSvgWriter::Write(std::shared_ptr<Maze> maze)
{
    std::ofstream out(filename);

    int w = maze->GetWidth(), h = maze->GetHeight();
    const int cell_w = 10, cell_h = 10;

    out << "<svg viewBox='0 0 " << (w + 1) * cell_w << " " << (h + 1) * cell_h
        << "' width='500' height='500' xmlns='http://www.w3.org/2000/svg'>"
        << std::endl;

    out << "<rect width='" << (w + 1) * cell_w << "' height='" << (h + 1) * cell_h << "' style='fill: black' />"
        << std::endl;

    for (auto &edge : maze->GetEdges())
    {
        out << "<line stroke='white' stroke-width='1' ";
        out << "x1='" << (cell_w / 2) + (edge.src.x * cell_w) << "' ";
        out << "y1='" << (cell_h / 2) + (edge.src.y * cell_h) << "' ";
        out << "x2='" << (cell_w / 2) + (edge.dst.x * cell_w) << "' ";
        out << "y2='" << (cell_h / 2) + (edge.dst.y * cell_h) << "'";
        out << "/>" << std::endl;
    }

    out << "</svg>";

    out.close();
}

#ifdef __TEST__

#undef __TEST__
#include "maze_reader.cc"
#include "maze.cc"
#define __TEST__

int main(void) {

    auto reader = MazeReader("maze.maze");

    auto maze = reader.Read();

    auto writer = MazeSvgWriter("test.svg");

    writer.Write(maze);
}

#endif
