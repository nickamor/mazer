#include <ostream>
#include <vector>
#include <string>
#include <memory>

#ifndef __MAZE_H__
#define __MAZE_H__

struct Edge {
    struct {
        int x, y;
    } cellA, cellB;
};

class Maze {
    int width, height, num_edges;
    std::vector<Edge> edges;

    // Print maze information
    friend std::ostream &operator<<(std::ostream &, const Maze &);

    static std::shared_ptr<Maze> fromFile(const std::string &filename);

    friend class FileReader;
    friend class FileWriter;
    friend class VectorWriter;
};

#endif
