//
// Created by Nicholas Amor on 13/8/16.
//

#include <fstream>
#include "maze_writer.h"

using namespace mazer;

MazeWriter::MazeWriter(const std::string &filename) : filename(filename)
{

}

void
MazeWriter::Write(std::shared_ptr<Maze> maze)
{
    std::ofstream stream(filename, std::ios::binary);

    auto &&edges = maze->GetEdges();
    int width = maze->GetWidth(), height = maze->GetHeight(), num_edges = static_cast<int>(edges.size());

    stream.write(reinterpret_cast<char *>(&width), sizeof width);
    stream.write(reinterpret_cast<char *>(&height), sizeof height);
    stream.write(reinterpret_cast<char *>(&num_edges), sizeof num_edges);

    for (auto &edge : edges)
    {
        stream.write(reinterpret_cast<const char *>(&edge.src.x), sizeof edge.src.x);
        stream.write(reinterpret_cast<const char *>(&edge.src.y), sizeof edge.src.y);
        stream.write(reinterpret_cast<const char *>(&edge.dst.x), sizeof edge.dst.x);
        stream.write(reinterpret_cast<const char *>(&edge.dst.y), sizeof edge.dst.y);
    }

}
