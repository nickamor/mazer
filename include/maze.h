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
    struct edge {
        struct point {
            int x, y;

            point(int x = 0, int y = 0);

            friend inline bool operator==(const point& lhs, const point& rhs) {
                return (lhs.x == rhs.x && lhs.y == rhs.y);
            };

            friend inline bool operator!=(const point& lhs, const point& rhs) {
                return !(lhs == rhs);
            };

            friend inline bool operator<(const point& lhs, const point& rhs) {
                return (lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y);
            };

            friend inline bool operator>(const point& lhs, const point& rhs) {
                return rhs < lhs;
            };
        } src, dst;

        edge(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);

        friend inline bool operator==(const edge& lhs, const edge& rhs) {
            return (lhs.src == rhs.src && lhs.dst == rhs.dst);
        };

        friend inline bool operator!=(const edge& lhs, const edge& rhs) {
            return !(lhs == rhs);
        };

        friend inline bool operator<(const edge& lhs, const edge& rhs) {
            return (lhs.src != rhs.src ? lhs.src < rhs.src : lhs.dst < rhs.dst);
        };

        friend inline bool operator>(const edge& lhs, const edge& rhs) {
            return rhs < lhs;
        };
    };

    /**
     * A single section of the maze, with possible adjoining cells.
     */
    struct cell {
        cell *north, *east, *south, *west;
        std::vector<cell *> links;

        cell();

        std::vector<cell *> neighbours();

        inline void add_link(cell* c) {
            links.push_back(c);
        };
    };

    /**
     * An immutable set of edges that define the pathways of a maze of defined width and height.
     */
    class maze {
        int width, height;
        std::set<edge> edges;

    public:
        maze(int width, int height, std::set<edge> edges);

        inline int get_width() {
            return width;
        }

        inline int get_height() {
            return height;
        } 

        inline int get_num_edges() {
            return edges.size();
        }

        inline std::set<edge> get_edges() {
            return edges;
        }

        std::string to_json_string();
    };

    /**
     * Used to construct a maze.
     */
    class maze_builder {
        int width, height;
        cell *cells;
        cell entry, exit;

    public:
        maze_builder(int width, int height);
        ~maze_builder();

        std::shared_ptr<maze> to_maze();

        cell *cell_at(int x, int y);

        void add_link(cell* lhs, cell* rhs);

        void add_exits();

        inline bool valid_cell(int x, int y) {
            return ((x >= 0 && y >= 0) && (x < width && y < height));
        }
    };

}

#endif
