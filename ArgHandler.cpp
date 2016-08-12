#include <boost/program_options.hpp>
#include "ArgHandler.h"

namespace po = boost::program_options;

Task::Task() {

}

Task::~Task() {

}

void Task::run() {

}

bool Task::isFinalTask() {
    return false;
}

void HelpTask::run() {
	
}

bool HelpTask::isFinalTask() {
    return true;
}

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

#ifdef __TEST__

int main(void) {
    int argc = 2;
    char const *argv[] = {
        "mazer",
        "--help"
    };

    auto args = std::make_unique<ArgHandler>(argc, argv);

    auto tasks = args.getTasks();

    for each (Task task in tasks) {
        task.run();

        if (task.isFinalTask()) {
            break;
        }
    }
}

#endif // TEST
