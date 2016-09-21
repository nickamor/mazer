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
    int width = maze->GetWidth(), height = maze->GetHeight(), num_edges = edges.size();

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

#ifdef __TEST__

#include <set>

#undef __TEST__
#include "maze.cc"
#define __TEST__

int main(void) {
    std::set<Edge> edges;
    auto maze = std::make_shared<Maze>(2, 2, edges);

    auto writer = MazeWriter("maze2.bin");

    writer.Write(maze);
}

#endif //__TEST__
