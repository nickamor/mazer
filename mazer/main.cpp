//
// Created by Nicholas Amor on 22/10/16.
//

#include <exception>
#include <iostream>
#include "mazer.h"

using namespace std;

using namespace mazer;

class Timer
{
  public:
    void start();
    void stop();
    auto getTime();

}

#include <string>

class Task
{
  public:
    void run();

    string name();
    double time();

}

#include <list>

class ArgumentParser
{
  public:
    ArgumentParser(int argc, char *argv[]);
    list<Task> getTasks();

}

ostream &
operator<<(ostream &os, const Timer &timer)
{
    os << timer.getTime();
    return os;
}

int main(int argc, char *argv[])
{
    auto &tasks = ArgumentParser(argc, argv).getTasks();
    auto &maze = make_shared<Maze>();

    for (auto &task : tasks)
    {
        try
        {
            maze = task.run(maze);
            cout << "Task " << task.name();
            cout << " completed in: \t" task.time() << " ms.\n";
        }
        catch (exception &e)
        {
            cerr << "Error in task " << task.name() << ", " << e.what() << endl;
        }
    }
}
