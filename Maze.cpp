#include "Maze.h"

std::ostream & operator<<(std::ostream & output, const Maze & maze) {
	output << "Maze" << std::endl;

	output << "width: " << maze.width << std::endl;
	output << "height: " << maze.height << std::endl;
	output << "edges: " << maze.num_edges << std::endl;

	for (int i = 0; i < maze.num_edges; ++i) {
		const Edge &edge = maze.edges[i];
		output << "Edge #" << i << std::endl;
		output << "\t{";
		output << edge.cellA.x << ", " << edge.cellA.y << ", ";
		output << edge.cellB.x << ", " << edge.cellB.y;
		output << "}" << std::endl;
	}

	return output;
}