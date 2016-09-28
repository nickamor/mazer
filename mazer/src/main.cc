//
// Created by Nicholas Amor on 12/8/16.
//

#include "arguments_parser.h"
#include "maze_reader.h"

using namespace mazer;

int
main(int argc, char const *argv[])
{
    try
    {
        auto handler = ArgumentsParser(argc, argv);

        auto tasks = handler.GetTasks();

        std::shared_ptr<Maze> maze = nullptr;

        for (auto &task : tasks)
        {
            if (auto input = std::dynamic_pointer_cast<InputTask>(task))
            {
                maze = input->Read();
            }

            if (auto output = std::dynamic_pointer_cast<OutputTask>(task))
            {
                output->Write(maze);
            }

            task->Run();
        }

        return 0;
    }
    catch (std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << '\n';
        return 1;
    }
}
