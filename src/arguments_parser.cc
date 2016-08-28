//
// Created by Nicholas Amor on 12/8/16.
//

#include <iostream>
#include <exception>
#include "arguments_parser.h"
#include "maze_generator.h"
#include "maze_reader.h"
#include "maze_writer.h"
#include "maze_svg_writer.h"

namespace po = boost::program_options;

using namespace mazer;

class HelpTask : public Task {
    po::options_description desc;
public:
    HelpTask(const po::options_description &desc) : desc(desc) {}

    void Run() override {
        std::cout << desc << std::endl;
    }
};

class ReadFileTask : public FileTask, public InputTask {
public:
    ReadFileTask(const std::string &filename) : FileTask(filename) {}

    std::shared_ptr<Maze> Read() override {
        MazeReader reader(filename);
        return reader.Read();
    }
};

class WriteFileTask : public FileTask, public OutputTask {
public:
    WriteFileTask(const std::string &filename) : FileTask(filename) {}

    void Write(std::shared_ptr<Maze> maze) override {
        MazeWriter writer(filename);
        writer.Write(maze);
    }
};

class WriteSvgTask : public FileTask, public OutputTask {
public:
    WriteSvgTask(const std::string &filename) : FileTask(filename) {}

    void Write(std::shared_ptr<Maze> maze) override {
        MazeSvgWriter writer(filename);
        writer.Write(maze);
    }
};

class GenerateTask : public InputTask {
    int seed, width, height;
public:
    GenerateTask(int seed, int width, int height) : seed(seed), width(width), height(height) {}

    std::shared_ptr<Maze> Read() override {
        auto gen = MazeGenerator::Factory(seed, width, height);
        return gen->Generate();
    }

    inline int GetSeed() {
        return seed;
    }

    inline int GetWidth() {
        return width;
    }

    inline int GetHeight() {
        return height;
    }
};

Task::~Task() {

}

void Task::Run() {

}

FileTask::FileTask(const std::string &filename) : filename(filename) {

}

FileTask::~FileTask() {

}

InputTask::~InputTask() {

}

OutputTask::~OutputTask() {

}

ArgumentsParser::ArgumentsParser(int argc, char const *argv[]) : argc(argc), argv(argv) {
#ifdef __TEST__

    std::cout << argc << " arguments:" << std::endl;

    for (int i = 0; i < argc; ++i)
    {
        std::cout << argv[i] << std::endl;
    }

#endif
}

std::vector<std::shared_ptr<Task> > ArgumentsParser::GetTasks() {
    po::options_description desc("Allowed options");
    po::variables_map map;

    desc.add_options()
            ("sb", po::value<std::string>(), "Save binary Maze file")
            ("lb", po::value<std::string>(), "Load binary Maze file")
            ("sv", po::value<std::string>(), "Save vector Maze file")
            ("g", po::value<std::vector<int> >()->multitoken(), "Generate Maze with given seed")
            ("help", "Produce help message");
    std::vector<std::shared_ptr<Task> > tasks;

    try {
        po::store(po::parse_command_line(argc, argv, desc), map);
        po::notify(map);

#ifdef __TEST__

        std::cout << map.size() << " arguments parsed" << std::endl;

#endif

        if (map.size() == 0 || map.count("help")) {
            std::shared_ptr<Task> task = std::make_shared<HelpTask>(desc);
            tasks.push_back(task);

            return tasks;
        }

        if (map.count("g")) {
            auto values = map["g"].as<std::vector<int> >();

            if (values.size() != 3) {
                throw new std::runtime_error("Generate task requires exactly three arguments.");
            }

            std::shared_ptr<Task> task = std::make_shared<GenerateTask>(values[0], values[1], values[2]);
            tasks.push_back(task);
        }

        if (map.count("lb")) {
            std::string filename = map["lb"].as<std::string>();
            std::shared_ptr<Task> task = std::make_shared<ReadFileTask>(filename);
            tasks.push_back(task);
        }

        if (map.count("sb")) {
            std::string filename = map["sb"].as<std::string>();
            std::shared_ptr<Task> task = std::make_shared<WriteFileTask>(filename);
            tasks.push_back(task);
        }

        if (map.count("sv")) {
            std::string filename = map["sv"].as<std::string>();
            std::shared_ptr<Task> task = std::make_shared<WriteSvgTask>(filename);
            tasks.push_back(task);
        }
    } catch (po::unknown_option &e) {
        std::cout << "WARNING: encountered unknown option " << e.get_option_name() << std::endl;
    }

    return tasks;
}

#ifdef __TEST__

#undef __TEST__
#include "maze.cc"
#include "maze_builder.cc"
#include "maze_generator.cc"
#include "maze_reader.cc"
#include "maze_writer.cc"
#include "maze_svg_writer.cc"
#include "strong_random.cc"
#define __TEST__

using namespace std;

int main(int argc, const char *argv[]) {
    auto args = ArgumentsParser(argc, argv);

    auto tasks = args.GetTasks();

    cout << tasks.size() << " tasks:" << endl;

    for (auto & task : tasks) {
        if (auto read = dynamic_pointer_cast<ReadFileTask>(task)) {
            cout << "ReadFileTask: " << read->GetFilename() << endl;
        }

        if (auto write = dynamic_pointer_cast<WriteFileTask>(task)) {
            cout << "WriteFileTask: " << write->GetFilename() << endl;
        }

        if (auto svg = dynamic_pointer_cast<WriteSvgTask>(task)) {
            cout << "WriteSvgTask: " << svg->GetFilename() << endl;
        }

        if (auto generate = dynamic_pointer_cast<GenerateTask>(task)) {
            cout << "GenerateTask: " << generate->GetSeed() << " " << generate->GetWidth() << " " << generate->GetHeight() << endl; 
        }

        if (auto help = dynamic_pointer_cast<HelpTask>(task)) {
            cout << "HelpTask" << endl; 
        }
    }
}

#endif // TEST
