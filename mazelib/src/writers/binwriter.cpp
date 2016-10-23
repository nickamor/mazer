//
// Created by Nicholas Amor on 22/10/16.
//

#include <fstream>
#include "writer.h"

using namespace mazer;

BinWriter::BinWriter(const IMaze &maze) : maze(maze) {}

void BinWriter::write(const std::string &filename)
{
    std::ofstream file(filename, std::ios::binary);

    if (!file)
    {
        throw FileNotWritable(filename);
    }

    file.exceptions(std::ios::badbit | std::ios::failbit);

    auto edges = maze.getEdges();
    int width = maze.getWidth(), height = maze.getHeight(), numEdges = int(edges.size());

    file.write(reinterpret_cast<const char *>(&width), sizeof(int));
    file.write(reinterpret_cast<const char *>(&height), sizeof(int));
    file.write(reinterpret_cast<const char *>(&numEdges), sizeof(int));

    for (auto &edge : edges)
    {
        file.write(reinterpret_cast<const char *>(&edge.x1), sizeof(int));
        file.write(reinterpret_cast<const char *>(&edge.y1), sizeof(int));
        file.write(reinterpret_cast<const char *>(&edge.x2), sizeof(int));
        file.write(reinterpret_cast<const char *>(&edge.y2), sizeof(int));
    }
}