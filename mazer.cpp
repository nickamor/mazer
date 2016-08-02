#include <iostream>
#include "FileReader.h"

int main(int argc, char const *argv[]) {
	if (argc > 2) {
		std::cout << "Usage: maze.bin" << std::endl;

		return 1;
	}

	auto reader = FileReader(argv[1]);

	reader.read();

	return 0;
}
