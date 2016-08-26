//
// Created by Nicholas Amor on 12/8/16.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "reader.h"

using namespace mazer;

reader::reader(const std::string &filename) : filename(filename) {

}

std::shared_ptr<maze> reader::read() {
    int width, height, num_edges;

    std::ifstream filestream(filename, std::ios::binary);

    if (!filestream.is_open()) {
        throw std::invalid_argument("Maze file does not exist.");
    }

    filestream.read(reinterpret_cast<char *>(&width), sizeof width);
    filestream.read(reinterpret_cast<char *>(&height), sizeof height);
    filestream.read(reinterpret_cast<char *>(&num_edges), sizeof num_edges);

    maze::builder builder(width, height);

    for (int i = 0; i < num_edges; ++i) {
        int x1, y1, x2, y2;

        filestream.read(reinterpret_cast<char *>(&x1), sizeof x1);
        filestream.read(reinterpret_cast<char *>(&y1), sizeof y1);
        filestream.read(reinterpret_cast<char *>(&x2), sizeof x2);
        filestream.read(reinterpret_cast<char *>(&y2), sizeof y2);

        builder.add_edge(x1, y1, x2, y2);
    }

    return builder.to_maze();
}

#ifdef __TEST__

std::ostream &operator<<(std::ostream &output, const Maze &maze) {
    output << "Maze" << std::endl;

    output << "width: " << maze.width << std::endl;
    output << "height: " << maze.height << std::endl;
    output << "edges: " << maze.num_edges << std::endl;

    for (auto& edge : maze.edges) {
        output << "\t{";
        output << edge.cellA.x << ", " << edge.cellA.y << ", ";
        output << edge.cellB.x << ", " << edge.cellB.y;
        output << "}" << std::endl;
    }

    return output;
}

int main()
{
    FileReader reader("maze.bin");
    auto maze = reader.read();

    std::cout << maze << std::endl;

    return 0;
}

#endif
