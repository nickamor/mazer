//
// Created by Nicholas Amor on 12/8/16.
//

#ifndef __MAZE_H__
#define __MAZE_H__

#include <ostream>
#include <vector>
#include <string>
#include <memory>

namespace mazer {

    /**
     * An immutable set of edges that define the pathways of a maze of defined width and height.
     */
    class maze {
    public:
        struct edge;

    private:
        int width, height;
        std::vector<edge> edges;

    public:
        class builder;

        inline int get_width() {
            return width;
        }

        inline int get_height() {
            return height;
        } 

        inline int get_num_edges() {
            return edges.size();
        }

        inline std::vector<edge> get_edges() {
            return edges;
        }

        // Print maze information
        friend std::ostream &operator<<(std::ostream &, const maze &);
    };

    /**
     * A single wall in a maze.
     */
    struct maze::edge {
        struct {
            int x, y;
        } src, dst;
    };

    /**
     * Used to define a maze.
     */
    class maze::builder {
    public:
        struct cell;

    private:
        int width, height;
        std::vector<std::vector<cell> > cells;

    public:
        builder(int width, int height, bool empty = true);

        std::shared_ptr<maze> to_maze();

        cell &cell_at(int x, int y);

        void add_edge(int x1, int y1, int x2, int y2);

        void add_link(int x1, int y1, int x2, int y2);

        void add_exits();
    };

    /**
     * A single section of the maze, with possible adjoining cells.
     */
    struct maze::builder::cell {
        int x, y;
        bool north, south, east, west;

        cell(int x, int y, bool empty) : x(x), y(y), north(empty), south(empty), east(empty), west(empty) {

        }
    };

}

#endif
