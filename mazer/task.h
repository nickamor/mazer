//
// Created by Nicholas Amor on 23/10/16.
//

#ifndef MAZER_TASK_H
#define MAZER_TASK_H

#include <memory>
#include <string>
#include "maze.h"
#include "timer.h"

using namespace mazer;

class Task
{
public:
    virtual std::string name() = 0;
    virtual std::shared_ptr<IMaze> run(std::shared_ptr<IMaze>& maze) = 0;

    double time();

protected:
    Timer timer;

};

class GenerateABTask
    : public Task
{

};

class GenerateETask
        : public Task
{

};

class SolveBfsTask
        : public Task
{

};

class SolveDfsTask
        : public Task
{

};

class SolveDManTask
        : public Task
{

};

class SolveDEucTask
        : public Task
{

};

class LoadTask
        : public Task
{

};

class SaveTask
        : public Task
{

};

class SaveSvgTask
        : public Task
{

};

#endif //MAZER_TASK_H
