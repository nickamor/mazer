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
     * A single wall in a maze.
     */
    struct edge {
        struct point {
            int x, y;

            point(int x = 0, int y = 0) : x(x), y(y) {}
        } src, dst;

        edge(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) : src(x1, y1), dst(x2, y2) {}
    };

    /**
     * A single section of the maze, with possible adjoining cells.
     */
    struct cell {
        cell *north, *east, *south, *west;
        std::vector<cell *> links;

        cell() : north(nullptr), east(nullptr), south(nullptr), west(nullptr) {}

        std::vector<cell *> neighbours();
    };

    /**
     * An immutable set of edges that define the pathways of a maze of defined width and height.
     */
    class maze {
        int width, height;
        std::vector<edge> edges;

    public:
        maze(int width, int height, std::vector<edge> edges);

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

        std::string to_json_string();

        friend class maze_builder;
    };

    /**
     * Used to construct a maze.
     */
    class maze_builder {
        int width, height;
        cell *cells;

    public:
        maze_builder(int width, int height, bool no_links = false);
        ~maze_builder();

        std::shared_ptr<maze> to_maze();

        cell *cell_at(int x, int y);

        void add_link(int x1, int y1, int x2, int y2);
        void add_exits();

        inline bool valid_cell(int x, int y) {
            return x > 0 && y > 0 && x < width && y < height;
        }
    };

}

#endif
