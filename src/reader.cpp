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

    std::vector<edge> edges(num_edges);

    for (int i = 0; i < num_edges; ++i) {
        filestream.read(reinterpret_cast<char *>(&edges[i].src.x), sizeof edges[i].src.x);
        filestream.read(reinterpret_cast<char *>(&edges[i].src.y), sizeof edges[i].src.y);
        filestream.read(reinterpret_cast<char *>(&edges[i].dst.x), sizeof edges[i].dst.x);
        filestream.read(reinterpret_cast<char *>(&edges[i].dst.y), sizeof edges[i].dst.y);
    }

    return std::make_shared<maze>(width, height, edges);
}

#ifdef __TEST__

#undef __TEST__
#include "maze.cpp"
#define __TEST__

int main()
{
    reader reader("maze.bin");
    auto maze = reader.read();

    std::cout << maze << std::endl;

    return 0;
}

#endif
