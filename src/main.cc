//
// Created by Nicholas Amor on 12/8/16.
//

#include "arguments_parser.h"
#include "maze_reader.h"

using namespace mazer;

#ifndef __TEST__

using namespace std;

int main(int argc, char const *argv[]) {
    auto handler = ArgumentsParser(argc, argv);

    auto tasks = handler.get_tasks();

    shared_ptr<Maze> maze = nullptr;

    for (auto &task : tasks) {
        if (auto input = dynamic_pointer_cast<InputTask>(task)) {
            maze = input->read();
        }

        if (auto output = dynamic_pointer_cast<OutputTask>(task)) {
            output->write(maze);
        }

        task->run();
    }

    return 0;
}

#else

#undef __TEST__
#include "arguments_parser.cc"
#include "maze.cc"
#include "maze_builder.cc"
#include "maze_reader.cc"
#include "maze_writer.cc"
#include "maze_generator.cc"
#include "maze_svg_writer.cc"
#include "strong_random.cc"
#define __TEST__

int main(void) {
    auto gen = MazeGenerator::factory(1, 64, 48);

    auto maze = gen->generate();

    auto writer = MazeSvgWriter("test.svg");

    writer.write(maze);
}

#endif

