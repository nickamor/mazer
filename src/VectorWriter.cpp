//
// Created by Nicholas Amor on 13/8/16.
//

#include <fstream>
#include "VectorWriter.h"
#include "Maze.h"

VectorWriter::VectorWriter(const std::string &filename) : filename(filename) {

}

void VectorWriter::write(const std::shared_ptr<Maze> &maze) {
    std::ofstream out(filename);

    int &w = maze->width, &h = maze->height;

    float stroke_width = 0.05;

    out << "<svg viewBox='0 0 " << w << " " << h << "' width='500' height='500' xmlns='http://www.w3.org/2000/svg'>"
        << std::endl;

    out << "<rect width='" << w << "' height='" << h << "' style='fill: black' />" << std::endl;

    for (auto& edge : maze->edges) {
        out << "<line stroke='white' stroke-width='1' ";
        out << "x1='" << edge.cellA.x << "' ";
        out << "y1='" << edge.cellA.y << "' ";
        out << "x2='" << edge.cellB.x << "' ";
        out << "y2='" << edge.cellB.y << "'";
        out << "/>" << std:: endl;
    }

    out << "</svg>";

    out.close();
}

#ifdef __TEST__

int main(void) {

    // auto reader = FileReader("small.maze");

    // auto maze = reader.read();

    // auto writer = VectorWriter("test.svg");

    // writer.write(maze);

}

#endif
