#include <iostream>
#include <boost/program_options.hpp>
#include "FileReader.h"

namespace po = boost::program_options;

class Task {
public:
	virtual Task() = 0;
	virtual ~Task() = 0;
	virtual void run() = 0;

};

Task::Task() {

}

Task::~Task() {

}

void Task::run() {

}

class HelpTask : public Task {
	public:
	override void run();
}

void HelpTask::run() {
	
}

class ArgHandler {
	po::options_description desc("Allowed options");
public:
	ArgHandler(int argc, char const *argv[]);
};

ArgHandler::ArgHandler(int argc, char const *argv[]) {
	desc.add_options()
		("help", "Produce help message")
		("sb", po::value<std::string>(), "Save binary Maze file")
		("lb", po::value<std::string>(), "Load binary Maze file")
		("sv", po::value<std::string>(), "Save vector Maze file")
		("g", po::value<std::vector<int> >()->multitoken(), "Generate maze with given seed")
	;

	po::variables_map map;add_options
	po::store(po::parse_command_line(argc, argv, desc), map);
	po::notify(map);
}

int main(int argc, char const *argv[]) {
	if (argc < 2) {
		std::cout << "Usage: mazer maze.bin" << std::endl;

		return 1;
	}

	auto reader = FileReader(argv[1]);

	reader.read();

	return 0;
}
