#include <iostream>
#include <fstream>
#include <vector>
#include "FileReader.h"

struct Edge {
	struct Cell {
		int x, y;
	} cellA, cellB;
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

Maze maze;

std::ostream & operator<<(std::ostream & output, const FileReader & fileReader) {
	output << "Maze" << std::endl;

	output << "width: " << maze.width << std::endl;
	output << "height: " << maze.height << std::endl;
	output << "edges: " << maze.num_edges << std::endl;

	for (int i = 0; i < maze.num_edges; ++i) {
		Edge &edge = maze.edges[i];
		output << "Edge #" << i << std::endl;
		output << "\t{";
		output << edge.cellA.x << ", " << edge.cellA.y << ", ";
		output << edge.cellB.x << ", " << edge.cellB.y;
		output << "}" << std::endl;
	}

	return output;
}

void FileReader::read() {
	std::ifstream filestream(filename, std::ios::binary);

	if (filestream.is_open()) {
		filestream.read(reinterpret_cast<char*>(&maze.width), sizeof maze.width);
		filestream.read(reinterpret_cast<char*>(&maze.height), sizeof maze.height);
		filestream.read(reinterpret_cast<char*>(&maze.num_edges), sizeof maze.num_edges);

		for (int i = 0; i < maze.num_edges; ++i) {
			Edge edge;

			filestream.read(reinterpret_cast<char*>(&edge.cellA.x), sizeof edge.cellA.x);
			filestream.read(reinterpret_cast<char*>(&edge.cellA.y), sizeof edge.cellA.y);
			filestream.read(reinterpret_cast<char*>(&edge.cellB.x), sizeof edge.cellB.x);
			filestream.read(reinterpret_cast<char*>(&edge.cellB.y), sizeof edge.cellB.y);

			maze.edges.push_back(edge);
		}
	}
}

#ifdef __TEST__
int main(int argc, char const *argv[])
{
	FileReader reader("maze.bin");
	reader.read();

	std::cout << reader;
	
	return 0;
}
#endif
