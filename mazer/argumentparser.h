//
// Created by Nicholas Amor on 23/10/16.
//

#ifndef MAZER_ARGUMENTPARSER_H
#define MAZER_ARGUMENTPARSER_H

#include <list>
#include <memory>
#include <stdexcept>
#include "task.h"

class InvalidArguments : std::runtime_error
{
public:
    InvalidArguments(const std::string& desc)
            : std::runtime_error("Invalid command line arguments: " + desc) {}
};

class ArgumentParser
{
public:
    ArgumentParser(int argc, char *argv[]);
    std::list<std::shared_ptr<Task>>& tasks();

private:
    std::list<std::shared_ptr<Task>> _tasks;

};


#endif //MAZER_ARGUMENTPARSER_H
