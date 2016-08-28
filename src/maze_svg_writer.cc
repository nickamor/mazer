//
// Created by Nicholas Amor on 13/8/16.
//

#include <fstream>
#include "maze_svg_writer.h"

using namespace mazer;

MazeSvgWriter::MazeSvgWriter(const std::string &filename) : filename(filename) {

}

void MazeSvgWriter::Write(std::shared_ptr<Maze> maze) {
    std::ofstream out(filename);

    int w = maze->GetWidth(), h = maze->GetHeight();
    int cell_w = 10, cell_h = 10;

    out << "<svg viewBox='0 0 " << w * 10 << " " << h * 10
        << "' width='500' height='500' xmlns='http://www.w3.org/2000/svg'>"
        << std::endl;

    out << "<rect width='" << w * (10 + 1) << "' height='" << h * (10 + 1) << "' style='fill: black' />" << std::endl;

    for (auto &edge : maze->GetEdges()) {
        out << "<line stroke='white' stroke-width='1' ";
        out << "x1='" << 5 + (edge.src.x * 10) << "' ";
        out << "y1='" << 5 + (edge.src.y * 10) << "' ";
        out << "x2='" << 5 + (edge.dst.x * 10) << "' ";
        out << "y2='" << 5 + (edge.dst.y * 10) << "'";
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
