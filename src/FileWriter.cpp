//
// Created by Nicholas Amor on 13/8/16.
//

#include <fstream>
#include "FileWriter.h"

FileWriter::FileWriter(const std::string &filename) : filename(filename) {

}

/**
 * Write the given Maze to file.
 * @param maze
 */
void FileWriter::write(const std::shared_ptr<Maze> &maze) {
    std::ofstream stream(filename, std::ios::binary);

    stream.write(reinterpret_cast<char *>(&maze->width), sizeof maze->width);
    stream.write(reinterpret_cast<char *>(&maze->height), sizeof maze->height);
    stream.write(reinterpret_cast<char *>(&maze->num_edges), sizeof maze->num_edges);

    for (auto &edge : maze->edges) {
        stream.write(reinterpret_cast<char *>(&edge.cellA.x), sizeof edge.cellA.x);
        stream.write(reinterpret_cast<char *>(&edge.cellA.y), sizeof edge.cellA.y);
        stream.write(reinterpret_cast<char *>(&edge.cellB.x), sizeof edge.cellB.x);
        stream.write(reinterpret_cast<char *>(&edge.cellB.y), sizeof edge.cellB.y);
    }
}

#ifdef __TEST__

int main(void) {
    // auto maze = std::make_shared<Maze>();

    // auto writer = FileWriter("maze2.bin");

    // writer.write(maze);
}

#endif //__TEST__
