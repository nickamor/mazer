//
// Created by Nicholas Amor on 12/8/16.
//

#ifndef __MAZE_H__
#define __MAZE_H__

#include <ostream>
#include <vector>
#include <set>
#include <string>
#include <memory>

namespace mazer {

    /**
     * A single wall in a maze.
     */
    struct Edge {
        struct Point {
            int x, y;

            Point(int x = 0, int y = 0);

            friend inline bool operator==(const Point &lhs, const Point &rhs) {
                return (lhs.x == rhs.x && lhs.y == rhs.y);
            };

            friend inline bool operator!=(const Point &lhs, const Point &rhs) {
                return !(lhs == rhs);
            };

            friend inline bool operator<(const Point &lhs, const Point &rhs) {
                return (lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y);
            };

            friend inline bool operator>(const Point &lhs, const Point &rhs) {
                return rhs < lhs;
            };
        } src, dst;

        Edge(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);

        friend inline bool operator==(const Edge &lhs, const Edge &rhs) {
            return (lhs.src == rhs.src && lhs.dst == rhs.dst);
        };

        friend inline bool operator!=(const Edge &lhs, const Edge &rhs) {
            return !(lhs == rhs);
        };

        friend inline bool operator<(const Edge &lhs, const Edge &rhs) {
            return (lhs.src != rhs.src ? lhs.src < rhs.src : lhs.dst < rhs.dst);
        };

        friend inline bool operator>(const Edge &lhs, const Edge &rhs) {
            return rhs < lhs;
        };
    };

    /**
     * An immutable set of edges that define the pathways of a maze of defined width and height.
     */
    class Maze {
        int width, height;
        std::set<Edge> edges;

    public:
        Maze(int width, int height, std::set<Edge> edges);

        inline int get_width() {
            return width;
        }

        inline int get_height() {
            return height;
        }

        inline int get_num_edges() {
            return edges.size();
        }

        inline std::set<Edge> get_edges() {
            return edges;
        }

        std::string to_json_string();
    };

}

#endif
