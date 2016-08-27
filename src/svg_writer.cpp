//
// Created by Nicholas Amor on 13/8/16.
//

#include <fstream>
#include "svg_writer.h"
#include "maze.h"

using namespace mazer;

svg_writer::svg_writer(const std::string &filename) : filename(filename) {

}

void svg_writer::write(std::shared_ptr<maze> maze) {
    std::ofstream out(filename);

    int w = maze->get_width(), h = maze->get_height();

    float stroke_width = 0.05;

    out << "<svg viewBox='0 0 " << w << " " << h << "' width='500' height='500' xmlns='http://www.w3.org/2000/svg'>"
        << std::endl;

    out << "<rect width='" << w << "' height='" << h << "' style='fill: black' />" << std::endl;

    for (auto &edge : maze->get_edges()) {
        out << "<line stroke='white' stroke-width='" << stroke_width << "' ";
        out << "x1='" << edge.src.x << "' ";
        out << "y1='" << edge.src.y << "' ";
        out << "x2='" << edge.dst.x << "' ";
        out << "y2='" << edge.dst.y << "'";
        out << "/>" << std::endl;
    }

    out << "</svg>";

    out.close();
}

#ifdef __TEST__

int main(void) {

    // auto reader = reader("small.maze");

    // auto maze = reader.read();

    // auto writer = svg_writer("test.svg");

    // writer.write(maze);

}

#endif
