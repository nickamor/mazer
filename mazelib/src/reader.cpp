//
// Created by Nicholas Amor on 14/10/16.
//

#include <fstream>
#include "reader.h"

using namespace mazer;

struct EdgedCell
{
public:
    bool up, down, left, right;
};

IReader::~IReader() {}

BinaryReader::BinaryReader(IMaze &maze) : maze(maze) {}

BinaryReader::~BinaryReader() {}

void BinaryReader::read(const std::string &filename)
{
    int width, height, num_edges;

    std::ifstream file(filename);
    if (!file)
    {
        throw FileNotReadable(filename);
    }

    file.exceptions(std::ios::badbit | std::ios::failbit);

    file.read((char *)(&width), sizeof(int));
    file.read((char *)(&height), sizeof(int));
    file.read((char *)(&num_edges), sizeof(int));

    std::vector<Edge> edges;
    std::vector<EdgedCell> edgedCells(unsigned(width * height));

    for (int i = 0; i < num_edges; ++i)
    {
        int x1, y1, x2, y2;

        file.read((char *)(&x1), sizeof(int));
        file.read((char *)(&y1), sizeof(int));
        file.read((char *)(&x2), sizeof(int));
        file.read((char *)(&y2), sizeof(int));

//        edges.emplace_back(x1, y1, x2, y2);

        if (x1 < x2) {
            // horizontal edge
            edgedCells[(y1 * width) + x1].up = true;
            edgedCells[(y2 * width) + x2].down = true;
        } else if (y1 < y2) {
            // vertical edge
            edgedCells[(y1 * width) + x1].left = true;
            edgedCells[(y2 * width) + x2].right = true;
        }
    }

//    file.close();

    maze.clear();
    maze.resize(width, height);

//    for (auto& edge : edges)
//    {
//        int id = (edge.y1 * width) + edge.x1;
//
//        if (edge.x2 > edge.x1)
//        {
//            cells[id].link(cells[id].left);
//        }
//    }
}
