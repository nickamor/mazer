//
// Created by Nicholas Amor on 22/10/16.
//

#include <exception>
#include <iostream>
#include <memory>
#include "mazer.h"
#include "argumentparser.h"
#include "task.h"
#include "timer.h"

using namespace std;

using namespace mazer;

ostream &
operator<<(ostream &os, const Timer &timer)
{
    os << timer.time();
    return os;
}

int main(int argc, char *argv[])
{
    auto parser = ArgumentParser(argc, argv);
    shared_ptr<IMaze> maze = make_shared<Maze>();

    for (auto &task : parser.tasks())
    {
        try
        {
            maze = task->run(maze);
            cout << "Task " << task->name();
            cout << " completed in: \t" << task->time() << " ms.\n";
        }
        catch (exception &e)
        {
            cerr << "Error in task " << task->name()
                 << ", " << e.what() << endl;
        }
    }
}
