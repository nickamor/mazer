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
private:
    int width, height, num_edges;
    std::vector<Edge> edges;

public:
    // Print maze information
    friend std::ostream &operator<<(std::ostream &, const Maze &);

    friend class FileReader;
    friend class FileWriter;
    friend class VectorWriter;
};

#endif
