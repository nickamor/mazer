//
// Created by Nicholas Amor on 23/10/16.
//

#include <string>
#include "argumentparser.h"

using namespace std;

ArgumentParser::ArgumentParser(int argc, char **argv)
{
    vector<pair<string, vector<string>>> pairs;

    for (int i = 0; i < argc; ++i)
    {
        string arg(argv[i]);


    }

    for (auto& pair : pairs)
    {
        if (pair.first.compare("--g") == 0)
        {
            if (pair.second.size() != 3)
            {
                throw "TODO: exception";
            }
        }
    }
}

std::list<std::shared_ptr<Task>>& ArgumentParser::tasks()
{
    return _tasks;
}
