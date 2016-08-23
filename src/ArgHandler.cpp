#include <boost/program_options.hpp>
#include <iostream>
#include "ArgHandler.h"

namespace po = boost::program_options;

Task::~Task() {

}

void Task::run() {

}

bool Task::isFinalTask() {
    return false;
}

bool Task::isInputTask() {
    return false;
}

bool Task::isOutputTask() {
    return false;
}

std::shared_ptr<Maze> Task::read() {
    return nullptr;
}

void Task::write(std::shared_ptr<Maze>) {

}

HelpTask::HelpTask(po::options_description desc) : desc(desc) {

}

void HelpTask::run() {
    std::cout << desc << std::endl;
}

bool HelpTask::isFinalTask() {
    return true;
}

IOTask::IOTask(std::string filename) : filename(filename) {

}

ReadFileTask::ReadFileTask(std::string filename) : IOTask(filename) {

}

bool ReadFileTask::isInputTask() {
    return true;
}

WriteFileTask::WriteFileTask(std::string filename) : IOTask(filename) {

}

bool WriteFileTask::isOutputTask() {
    return true;
}

WriteVectorTask::WriteVectorTask(std::string filename) : IOTask(filename) {

}

bool WriteVectorTask::isOutputTask() {
    return true;
}

GenerateTask::GenerateTask(int, int, int) {

}

GenerateTask::~GenerateTask() {

}

bool GenerateTask::isInputTask() {
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

    if (map.size() == 0 || map.count("help")) {
        tasks.push_back(std::make_shared<HelpTask>(desc));

        return;
    }

    if (map.count("g")) {
        auto values = map["g"].as<std::vector<int> >();

        if (values.size() != 3) {
            throw new std::string("Invalid arguments");
        }

        tasks.push_back(std::make_shared<GenerateTask>(values[0], values[1], values[2]));
    }

    if (map.count("lb")) {
        std::string filename = map["lb"].as<std::string>();
        tasks.push_back(std::make_shared<ReadFileTask>(filename));
    }

    if (map.count("sb")) {
        std::string filename = map["sb"].as<std::string>();
        tasks.push_back(std::make_shared<WriteFileTask>(filename));
    }

    if (map.count("sv")) {
        std::string filename = map["sv"].as<std::string>();
        tasks.push_back(std::make_shared<WriteVectorTask>(filename));
    }
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
