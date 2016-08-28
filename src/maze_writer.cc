//
// Created by Nicholas Amor on 13/8/16.
//

#include <fstream>
#include "maze_writer.h"

using namespace mazer;

MazeWriter::MazeWriter(const std::string &filename) : filename(filename) {

}

/**
 * Write the given Maze to file.
 * @param maze
 */
void MazeWriter::write(std::shared_ptr<Maze> maze) {
    std::ofstream stream(filename, std::ios::binary);

    int width = maze->get_width(), height = maze->get_height(), num_edges = maze->get_num_edges();

    stream.write(reinterpret_cast<char *>(&width), sizeof width);
    stream.write(reinterpret_cast<char *>(&height), sizeof height);
    stream.write(reinterpret_cast<char *>(&num_edges), sizeof num_edges);

    for (auto &edge : maze->get_edges()) {
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

    writer.write(maze);
}

#endif //__TEST__
