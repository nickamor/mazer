#include <memory>
#include <vector>
#include <boost/program_options.hpp>
#include "Maze.h"

#ifndef __ARGHANDLER_H__
#define __ARGHANDLER_H__

namespace po = boost::program_options;

class Task {
public:
    virtual ~Task() = 0;

    virtual bool isInputTask();

    virtual bool isOutputTask();

    virtual bool isFinalTask();

    virtual std::shared_ptr<Maze> read();

    virtual void write(std::shared_ptr<Maze> maze);

    virtual void run();
};

class HelpTask : public Task {
    po::options_description desc;
public:
    HelpTask(po::options_description desc);

    void run();

    bool isFinalTask();
};

class IOTask : public Task {
protected:
    std::string filename;
public:
    IOTask(std::string filename);
};

class ReadFileTask : public IOTask {
public:
    ReadFileTask(std::string filename);
    bool isInputTask();
};

class WriteFileTask : public IOTask {
public:
    WriteFileTask(std::string filename);
    bool isOutputTask();
};

class WriteVectorTask : public IOTask {
public:
    WriteVectorTask(std::string filename);
    bool isOutputTask();
};

class GenerateTask : public Task {
public:
    GenerateTask(int, int, int);

    ~GenerateTask();

    bool isInputTask();
};

class ArgHandler {
    std::vector<std::shared_ptr<Task> > tasks;
public:
    ArgHandler(int argc, char const *argv[]);

    std::vector<std::shared_ptr<Task> > getTasks();
};

#endif // !__ARGHANDLER_H__
