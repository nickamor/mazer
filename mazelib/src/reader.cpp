//
// Created by Nicholas Amor on 14/10/16.
//

#include <fstream>
#include "reader.h"

using namespace mazer;

struct EdgedCell
{
public:
    int i;
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

    std::vector<EdgedCell> edgedCells;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j){
        {
            EdgedCell e{(i * width) + j, false, false, false, false};

            if (i == 0)
            {
                e.up = true;
            }

            if (i == height - 1)
            {
                e.down = true;
            }

            if (j == 0)
            {
                e.left = true;
            }

            if (j == width - 1)
            {
                e.right = true;
            }

            edgedCells.push_back(e);
        }
    }

    for (int i = 0; i < num_edges; ++i)
    {
        int x1, y1, x2, y2;

        file.read((char *)(&x1), sizeof(int));
        file.read((char *)(&y1), sizeof(int));
        file.read((char *)(&x2), sizeof(int));
        file.read((char *)(&y2), sizeof(int));

        if (x2 == width || y2 == height)
        {
            continue;
        }

        if (x1 < x2) {
            // horizontal edge
            edgedCells[(y1 * width) + x1].up = true;
            edgedCells[(y2 * width) + x2].down = true;
        } else if (y1 < y2) {
            // vertical edge
            edgedCells[(y1 * width) + x1].left = true;
            edgedCells[(y2 * width) + x2].left = true;
        }
    }

    maze.clear();
    maze.resize(width, height);

    for (int i = 0; i < width * height; ++i) {
        auto& cellEdges = edgedCells[i];
        auto& cell = maze.getCell(i);

        if (!cellEdges.up) {
            maze.link(&cell, cell.up);
        }

        if (!cellEdges.down) {
            maze.link(&cell, cell.down);
        }

        if (!cellEdges.left) {
            maze.link(&cell, cell.left);
        }

        if (!cellEdges.right) {
            maze.link(&cell, cell.right);
        }
    }
}
