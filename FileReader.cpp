#include <iostream>
#include <fstream>
#include <vector>
#include "FileReader.h"

struct Edge {
	int cellA_x, cellA_y;
	int cellB_x, cellB_y;
};

struct Maze
{
	int width, height, num_edges;
	std::vector<Edge> edges;
};

FileReader::FileReader(const char * filename) : filename(filename) {

}

FileReader::~FileReader() {

}

void FileReader::read() {
	std::ifstream filestream(filename, std::ios::binary);

	if (filestream.is_open()) {
		Maze maze;

		// filestream >> maze.width;
		// filestream >> maze.height;
		// filestream >> maze.num_edges;
		filestream.read(reinterpret_cast<char*>(&maze.width), sizeof maze.width);
		filestream.read(reinterpret_cast<char*>(&maze.height), sizeof maze.height);
		filestream.read(reinterpret_cast<char*>(&maze.num_edges), sizeof maze.num_edges);

		for (int i = 0; i < maze.num_edges; ++i) {
			Edge edge;

			// filestream >> edge.cellA_x;
			// filestream >> edge.cellA_y;
			// filestream >> edge.cellB_x;
			// filestream >> edge.cellB_y;
			filestream.read(reinterpret_cast<char*>(&edge.cellA_x), sizeof edge.cellA_x);
			filestream.read(reinterpret_cast<char*>(&edge.cellA_y), sizeof edge.cellA_y);
			filestream.read(reinterpret_cast<char*>(&edge.cellB_x), sizeof edge.cellB_x);
			filestream.read(reinterpret_cast<char*>(&edge.cellB_y), sizeof edge.cellB_y);

			maze.edges.push_back(edge);
		}

		std::cout << "Maze" << std::endl;

		std::cout << "width: " << maze.width << std::endl;
		std::cout << "height: " << maze.height << std::endl;
		std::cout << "edges: " << maze.num_edges << std::endl;

		for (int i = 0; i < maze.num_edges; ++i) {
			Edge &edge = maze.edges[i];
			std::cout << "Edge #" << i << std::endl;
			std::cout << "\t{";
			std::cout << edge.cellA_x << ", " << edge.cellA_y << ", ";
			std::cout << edge.cellB_x << ", " << edge.cellB_y;
			std::cout << "}" << std::endl;
		}
	}
}

#ifdef __TEST__
int main(int argc, char const *argv[])
{
	FileReader reader("maze.bin");
	reader.read();
	
	return 0;
}
#endif
