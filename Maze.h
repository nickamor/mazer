#include <ostream>
#include <vector>

#ifndef __MAZE_H__
#define __MAZE_H__

struct Edge {
	struct Cell {
		int x, y;
	} cellA, cellB;
};

struct Maze
{
	int width, height, num_edges;
	std::vector<Edge> edges;

    friend std::ostream & operator<<(std::ostream &, const Maze &);
};


#endif
