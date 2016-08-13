#include <iostream>
#include <fstream>
#include <vector>
#include "FileReader.h"

class MyIfStream : public std::ifstream {
public:

};

// // easy read
// void read<type> (ifstream filestream, type & buffer) {
// 	filestream.read(reinterpret_cast<char*>(&buffer), sizeof buffer);
// }

FileReader::FileReader(const std::string &filename) : filename(filename) {

}

FileReader::~FileReader() {

}

std::shared_ptr<Maze> FileReader::read() {
    auto maze = std::make_shared<Maze>();

    std::ifstream filestream(filename, std::ios::binary);

    if (!filestream.is_open()) {
        throw std::invalid_argument("Maze file does not exist.");
    }

    filestream.read(reinterpret_cast<char *>(&maze->width), sizeof maze->width);
    filestream.read(reinterpret_cast<char *>(&maze->height), sizeof maze->height);
    filestream.read(reinterpret_cast<char *>(&maze->num_edges), sizeof maze->num_edges);

    for (int i = 0; i < maze->num_edges; ++i) {
        Edge edge;

        filestream.read(reinterpret_cast<char *>(&edge.cellA.x), sizeof edge.cellA.x);
        filestream.read(reinterpret_cast<char *>(&edge.cellA.y), sizeof edge.cellA.y);
        filestream.read(reinterpret_cast<char *>(&edge.cellB.x), sizeof edge.cellB.x);
        filestream.read(reinterpret_cast<char *>(&edge.cellB.y), sizeof edge.cellB.y);

        maze->edges.push_back(edge);
    }

    return maze;
}

#ifdef __TEST__

int main(void)
{
    FileReader reader("maze.bin");
    auto maze = reader.read();

    std::cout << "Maze width: " << maze->width;
    std::cout << ", height: " << maze->height;
    std::cout << ", edges: " << maze->num_edges << std::endl;

    for (int i = 0; i < maze->num_edges; ++i) {
        Edge &edge = maze->edges[i];

        std::cout << "Edge = ";
        std::cout << edge.cellA.x << " ";
        std::cout << edge.cellA.y << " ";
        std::cout << edge.cellB.x << " ";
        std::cout << edge.cellB.y << "." << std::endl;
    }

    return 0;
}

#endif
