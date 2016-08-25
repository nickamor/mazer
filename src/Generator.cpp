//
// Created by Nicholas Amor on 13/8/16.
//

#include "Generator.h"
#include "Random.h"

struct Cell {
	int x, y;
	bool north, south, east, west;
	Cell(int x, int y) : x(x), y(y), north(false), south(false), east(false), west(false) {}
};

class Grid {
	int width, height;
	std::vector<std::vector<std::shared_ptr<Cell> > > cells;
public:
	Grid(int width, int height);

	std::shared_ptr<Cell> cellAt(int x, int y);
};

Grid::Grid(int width, int height) : width(width), height(height) {
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			cells[i].push_back(std::make_shared<Cell>(i, j));
		}
	}
}

std::shared_ptr<Cell> Grid::cellAt(int x, int y) {
	return cells[x][y];
}

Generator::Generator(int seed, int width, int height) : seed(seed), width(width), height(height) {

}

std::shared_ptr<Maze> Generator::generate() {
    return nullptr;
}

AldousBroderGenerator::AldousBroderGenerator(int seed, int width, int height) : Generator(seed, width, height) {

}

std::shared_ptr<Maze> AldousBroderGenerator::generate() {
	auto rand = Random(seed);
	auto grid = std::make_shared<Grid>(width, height);
	int unvisited = width * height;

	auto cell = grid.cellAt(rand.next(0, width), rand.next(0, height));

	while (unvisited > 0) {

	}

    return nullptr;
}

#ifdef __TEST__

int main() {}

#endif
