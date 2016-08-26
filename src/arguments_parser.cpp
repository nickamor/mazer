//
// Created by Nicholas Amor on 12/8/16.
//

#include <iostream>
#include "arguments_parser.h"

namespace po = boost::program_options;

using namespace mazer;

class help_task : public task {
    po::options_description desc;
public:
    help_task(const po::options_description &desc);

    void run();
};

class read_file_task : public file_task, public input_task {
public:
    read_file_task(const std::string &filename);

    std::shared_ptr<maze> read();
};

class write_file_task : public file_task, public output_task {
public:
    write_file_task(const std::string &filename);

    void write(std::shared_ptr<maze> maze);
};

class write_vector_task : public file_task, public output_task {
public:
    write_vector_task(const std::string &filename);

    void write(std::shared_ptr<maze> maze);
};

class generate_task : public input_task {
public:
    generate_task(int, int, int);

    ~generate_task();

    std::shared_ptr<maze> read();
};

task::~task() {

}

void task::run() {

}

file_task::file_task(const std::string &filename) : filename(filename) {

}

file_task::~file_task() {

}

input_task::~input_task() {

}

output_task::~output_task() {

}

arguments_parser::arguments_parser(int argc, char const *argv[]) : desc("Allowed options") {
    desc.add_options()
            ("help", "Produce help message")
            ("sb", po::value<std::string>(), "Save binary Maze file")
            ("lb", po::value<std::string>(), "Load binary Maze file")
            ("sv", po::value<std::string>(), "Save vector Maze file")
            ("g", po::value<std::vector<int> >()->multitoken(), "Generate maze with given seed");

    po::store(po::parse_command_line(argc, argv, desc), map);
    po::notify(map);
}

std::vector<std::shared_ptr<task> > arguments_parser::get_tasks() {
    std::vector<std::shared_ptr<task> > tasks;

    if (map.size() == 0 || map.count("help")) {
        std::shared_ptr<task> task = std::make_shared<help_task>(desc);
        tasks.push_back(task);

        return tasks;
    }

    if (map.count("g")) {
        auto values = map["g"].as<std::vector<int> >();

        if (values.size() != 3) {
            throw new std::string("Invalid arguments");
        }

        std::shared_ptr<task> task = std::make_shared<generate_task>(values[0], values[1], values[2]);
        tasks.push_back(task);
    }

    if (map.count("lb")) {
        std::string filename = map["lb"].as<std::string>();
        std::shared_ptr<task> task = std::make_shared<read_file_task>(filename);
        tasks.push_back(task);
    }

    if (map.count("sb")) {
        std::string filename = map["sb"].as<std::string>();
        std::shared_ptr<task> task = std::make_shared<write_file_task>(filename);
        tasks.push_back(task);
    }

    if (map.count("sv")) {
        std::string filename = map["sv"].as<std::string>();
        std::shared_ptr<task> task = std::make_shared<write_vector_task>(filename);
        tasks.push_back(task);
    }

    return tasks;
}

help_task::help_task(const po::options_description &desc) : desc(desc) {

}

void help_task::run() {
    std::cout << desc << std::endl;
}

read_file_task::read_file_task(const std::string &filename) : file_task(filename) {

}

std::shared_ptr<maze> read_file_task::read() {
    return nullptr;
}

write_file_task::write_file_task(const std::string &filename) : file_task(filename) {

}

void write_file_task::write(std::shared_ptr<maze>) {

}

write_vector_task::write_vector_task(const std::string &filename) : file_task(filename) {

}

void write_vector_task::write(std::shared_ptr<maze>) {

}

generate_task::generate_task(int, int, int) {

}

generate_task::~generate_task() {

}

std::shared_ptr<maze> generate_task::read() {
    return nullptr;
}

#ifdef __TEST__

int main(void) {
    int argc = 2;
    char const *argv[] = {
        "mazer",
        "--help"
    };

    auto args = std::make_unique<arguments_parser>(argc, argv);

    auto tasks = args->get_tasks();

    for (auto & task : tasks) {
        task->run();

        if (task->is_final_task()) {
            break;
        }
    }
}

#endif // TEST
