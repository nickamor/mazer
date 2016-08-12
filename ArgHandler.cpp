#include <boost/program_options.hpp>
#include "ArgHandler.h"

namespace po = boost::program_options;

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
    po::options_description desc("Allowed options");

    desc.add_options()
            ("help", "Produce help message")
            ("sb", po::value<std::string>(), "Save binary Maze file")
            ("lb", po::value<std::string>(), "Load binary Maze file")
            ("sv", po::value<std::string>(), "Save vector Maze file")
            ("g", po::value<std::vector<int> >()->multitoken(), "Generate maze with given seed");

    po::variables_map map;
    po::store(po::parse_command_line(argc, argv, desc), map);
    po::notify(map);

    if (map.count("help")) {
        tasks.push_back(std::make_shared<HelpTask>());
    }

    // if (map.count("lb")) {
    // 	std::cout << "Loading file " << map["lb"].as<std::string>() << std::endl;
    // } else if (map.count("g")) {
    // 	auto values = map["g"].as<std::vector<int> >();
    // 	std::cout << "Generating map with seed %d, width %d and height %d" << values[0] << values[1] << values[2] << std::endl;
    // } else {
    // 	std::cout << "No file loaded." << std::endl;
    // 	return 1;
    // }
}

std::vector<std::shared_ptr<Task> > ArgHandler::getTasks() {
    return tasks;
}

#ifdef __TEST__

int main(void) {
    int argc = 2;
    char const *argv[] = {
        "mazer",
        "--help"
    };

    auto args = std::make_unique<ArgHandler>(argc, argv);

    auto tasks = args->getTasks();

    for (auto & task : tasks) {
        task->run();

        if (task->isFinalTask()) {
            break;
        }
    }
}

#endif // TEST
