//
// Created by Nicholas Amor on 12/8/16.
//

#include "maze_reader.h"
#include <sstream>

using namespace mazer;

Edge::Point::Point(int x, int y) : x(x), y(y) {}

Edge::Edge(int x1, int y1, int x2, int y2) : src(x1, y1), dst(x2, y2) {}

Maze::Maze(int width, int height, std::set<Edge> edges) : 
    width(width), height(height), edges(edges) {}

std::string
Maze::ToJsonString()
{
    std::stringstream out;
    out << "{" << std::endl;

    out << "\t\"width\": " << width << "," << std::endl;
    out << "\t\"height\": " << height << "," << std::endl;
    out << "\t\"num_edges\": " << edges.size() << "," << std::endl;

    out << "\t\"edges\": [" << std::endl;
    for (auto iter = edges.begin(); iter != edges.end(); ++iter)
    {
        auto &edge = *iter;
        out << "\t\t{ ";

        out << "\"x1\": " << edge.src.x << ", ";
        out << "\"y1\": " << edge.src.y << ", ";
        out << "\"x2\": " << edge.dst.x << ", ";
        out << "\"y2\": " << edge.dst.y;

        if (iter != std::end(edges))
        {
            out << " }," << std::endl;
        }
        else
        {
            out << " }" << std::endl;
        }
    }
    out << "\t]" << std::endl;
    out << "}" << std::endl;

    return out.str();
}
