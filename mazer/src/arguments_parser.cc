//
// Created by Nicholas Amor on 12/8/16.
//

#include <iostream>
#include "arguments_parser.h"
#include "maze_generator.h"
#include "maze_reader.h"
#include "maze_writer.h"
#include "maze_svg_writer.h"

namespace po = boost::program_options;

using namespace mazer;

using Ints = std::vector<int>;

class HelpTask : public Task
{
    po::options_description desc;
public:
    HelpTask(const po::options_description &desc) : desc(desc) {}

    void
    Run() override
    {
        std::cout << desc << std::endl;
    }
};

class ReadFileTask : public FileTask, public InputTask
{
public:
    ReadFileTask(const std::string &filename) : FileTask(filename) {}

    std::shared_ptr<Maze>
    Read() override
    {
        MazeReader reader(filename);
        return reader.Read();
    }
};

class WriteFileTask : public FileTask, public OutputTask
{
public:
    WriteFileTask(const std::string &filename) : FileTask(filename) {}

    void
    Write(std::shared_ptr<Maze> maze) override
    {
        MazeWriter writer(filename);
        writer.Write(maze);
    }
};

class WriteSvgTask : public FileTask, public OutputTask
{
public:
    WriteSvgTask(const std::string &filename) : FileTask(filename) {}

    void
    Write(std::shared_ptr<Maze> maze) override
    {
        MazeSvgWriter writer(filename);
        writer.Write(maze);
    }
};

class GenerateTask : public InputTask
{
    int seed, width, height;
    MazeGeneratorType type;
public:
    GenerateTask(int seed, int width, int height, 
        MazeGeneratorType type = MazeGeneratorType::AldousBroder) : 
        width(width), height(height), type(type)
    {
        if (seed == -1)
        {
            this->seed = int(std::chrono::system_clock::now()
                .time_since_epoch().count());
        }
        else
        {
            this->seed = seed;
        }
    }

    std::shared_ptr<Maze>
    Read() override
    {
        auto gen = MazeGenerator::Factory(type);
        return gen->Generate(seed, width, height);
    }

    inline int
    GetSeed()
    {
        return seed;
    }

    inline int
    GetWidth()
    {
        return width;
    }

    inline int
    GetHeight()
    {
        return height;
    }
};

Task::~Task()
{

}

void
Task::Run()
{

}

FileTask::FileTask(const std::string &filename) : filename(filename)
{

}

FileTask::~FileTask()
{

}

InputTask::~InputTask()
{

}

OutputTask::~OutputTask()
{

}

ArgumentsParser::ArgumentsParser(int argc, char const *argv[]) : 
    argc(argc), argv(argv) {}

std::vector<std::shared_ptr<Task> >
ArgumentsParser::GetTasks()
{
    po::options_description desc("Allowed options");
    po::variables_map map;

    desc.add_options()
        ("sb", po::value<std::string>(), "Save binary Maze file")
        ("lb", po::value<std::string>(), "Load binary Maze file")
        ("sv", po::value<std::string>(), "Save vector Maze file")
        ("g", po::value<Ints>()->multitoken()->
             implicit_value(Ints{-1, 50, 50}, "seed width height"),
         "Generate Maze with given seed")
        ("ga", po::value<Ints>()->multitoken()->
             implicit_value(Ints{-1, 50, 50}, "seed width height"),
         "Aldous-Broder Generate Maze with given seed")
        ("ge", po::value<Ints>()->multitoken()->
             implicit_value(Ints{-1, 50, 50}, "seed width height"),
         "Ellers Generate Maze with given seed")
        ("help", "Produce help message");
    std::vector<std::shared_ptr<Task> > tasks;

    try
    {
        po::store(po::parse_command_line(argc, argv, desc), map);
        po::notify(map);

        if (map.size() == 0 || map.count("help"))
        {
            auto task = std::make_shared<HelpTask>(desc);
            tasks.push_back(task);

            return tasks;
        }

        if (map.count("g"))
        {
            auto values = map["g"].as<Ints>();
            int seed, width, height;

            seed = values[0];
            width = values[1];
            height = values[2];

            auto task = std::make_shared<GenerateTask>(seed, width, height);
            tasks.push_back(task);
        }

        if (map.count("ga"))
        {
            auto values = map["ga"].as<Ints>();
            int seed, width, height;

            seed = values[0];
            width = values[1];
            height = values[2];

            auto task = std::make_shared<GenerateTask>(seed, width, height, 
                MazeGeneratorType::AldousBroder);
            tasks.push_back(task);
        }

        if (map.count("ge"))
        {
            auto values = map["ge"].as<Ints>();
            int seed, width, height;

            seed = values[0];
            width = values[1];
            height = values[2];

            auto task = std::make_shared<GenerateTask>(seed, width, height, 
                MazeGeneratorType::Eller);
            tasks.push_back(task);
        }

        if (map.count("lb"))
        {
            std::string filename = map["lb"].as<std::string>();
            auto task = std::make_shared<ReadFileTask>(filename);
            tasks.push_back(task);
        }

        if (map.count("sb"))
        {
            std::string filename = map["sb"].as<std::string>();
            auto task = std::make_shared<WriteFileTask>(filename);
            tasks.push_back(task);
        }

        if (map.count("sv"))
        {
            std::string filename = map["sv"].as<std::string>();
            auto task = std::make_shared<WriteSvgTask>(filename);
            tasks.push_back(task);
        }
    }
    catch (po::error_with_option_name &e)
    {
        std::cout << "WARNING: error with argument " << e.get_option_name() 
            << std::endl;
    }

    return tasks;
}
