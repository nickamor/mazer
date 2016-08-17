#include <memory>
#include <vector>
#include "Maze.h"

#ifndef __ARGHANDLER_H__
#define __ARGHANDLER_H__

class Task {
public:
    virtual ~Task() = 0;

    virtual void run() = 0;

    virtual bool isFinalTask();

    virtual bool isInputTask();

    virtual bool isOutputTask();

    virtual std::shared_ptr<Maze> read();

    virtual void write(std::shared_ptr<Maze> maze);
};

class HelpTask : public Task {
public:
    void run();

    bool isFinalTask();
};

class ReadFileTask : public Task {
    bool isInputTask();
};

class WriteFileTask : public Task {
    bool isOutputTask();
};

class WriteVectorTask : public Task {
    bool isOutputTask();
};

class ArgHandler {
    std::vector<std::shared_ptr<Task> > tasks;
public:
    ArgHandler(int argc, char const *argv[]);

    std::vector<std::shared_ptr<Task> > getTasks();
};

#endif // !__ARGHANDLER_H__
