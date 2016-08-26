//
// Created by Nicholas Amor on 13/8/16.
//

#include <fstream>
#include "writer.h"

using namespace mazer;

writer::writer(const std::string &filename) : filename(filename) {

}

/**
 * Write the given Maze to file.
 * @param maze
 */
void writer::write(std::shared_ptr<maze> maze) {
    std::ofstream stream(filename, std::ios::binary);

    int width = maze->get_width(), height = maze->get_height(), num_edges = maze->get_num_edges();

    stream.write(reinterpret_cast<char *>(&width), sizeof width);
    stream.write(reinterpret_cast<char *>(&height), sizeof height);
    stream.write(reinterpret_cast<char *>(&num_edges), sizeof num_edges);

    for (auto &edge : maze->get_edges()) {
        stream.write(reinterpret_cast<char *>(&edge.src.x), sizeof edge.src.x);
        stream.write(reinterpret_cast<char *>(&edge.src.y), sizeof edge.src.y);
        stream.write(reinterpret_cast<char *>(&edge.dst.x), sizeof edge.dst.x);
        stream.write(reinterpret_cast<char *>(&edge.dst.y), sizeof edge.dst.y);
    }
}

#ifdef __TEST__

int main(void) {
    // auto maze = std::make_shared<Maze>();

    // auto writer = writer("maze2.bin");

    // writer.write(maze);
}

#endif //__TEST__
