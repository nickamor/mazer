#include <iostream>
#include <boost/program_options.hpp>
#include "FileReader.h"

int main(int argc, char const *argv[]) {
	if (argc < 2) {
		std::cout << "Usage: mazer maze.bin" << std::endl;

		return 1;
	}

	auto reader = FileReader(argv[1]);

	reader.read();

	return 0;
}
