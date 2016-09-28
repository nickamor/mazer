//
// Created by Nicholas Amor on 12/8/16.
//

#include <iostream>
#include <fstream>
#include <set>
#include "maze_reader.h"

using namespace mazer;

MazeReader::MazeReader(const std::string &filename) : filename(filename)
{

}

std::shared_ptr<Maze>
MazeReader::Read() throw(InvalidMaze, MazeFileNotFound)
{
    int width, height, num_edges;

    std::ifstream filestream(filename, std::ios::binary);

    if (!filestream.is_open())
    {
        throw std::invalid_argument("Maze file does not exist.");
    }

    filestream.read(reinterpret_cast<char *>(&width), sizeof width);
    filestream.read(reinterpret_cast<char *>(&height), sizeof height);
    filestream.read(reinterpret_cast<char *>(&num_edges), sizeof num_edges);

    std::set<Edge> edges;

    for (int i = 0; i < num_edges; ++i)
    {
        int x1, y1, x2, y2;

        filestream.read(reinterpret_cast<char *>(&x1), sizeof x1);
        filestream.read(reinterpret_cast<char *>(&y1), sizeof y1);
        filestream.read(reinterpret_cast<char *>(&x2), sizeof x2);
        filestream.read(reinterpret_cast<char *>(&y2), sizeof y2);

        edges.emplace(x1, y1, x2, y2);
    }

    return std::make_shared<Maze>(width, height, edges);
}

#ifdef __TEST__

#undef __TEST__
#include "maze.cc"
#define __TEST__

int main()
{
    MazeReader reader("maze.bin");
    auto maze = reader.Read();

    std::cout << maze << std::endl;

    return 0;
}

#endif
