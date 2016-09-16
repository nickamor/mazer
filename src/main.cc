//
// Created by Nicholas Amor on 12/8/16.
//

#include "arguments_parser.h"
#include "maze_reader.h"

using namespace mazer;

#ifndef __TEST__

using namespace std;

int main(int argc, char const *argv[]) {
  try {
    auto handler = ArgumentsParser(argc, argv);

    auto tasks = handler.GetTasks();

    shared_ptr<Maze> maze = nullptr;

    for (auto &task : tasks) {
      if (auto input = dynamic_pointer_cast<InputTask>(task)) {
        maze = input->Read();
      }

      if (auto output = dynamic_pointer_cast<OutputTask>(task)) {
        output->Write(maze);
      }

      task->Run();
    }

    return 0;
  } catch (std::exception &e) {
    cerr << e.what() << '\n';
    return 1;
  }
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
    auto gen = MazeGenerator::Factory(1, 64, 48);

    auto maze = gen->Generate();

    auto writer = MazeSvgWriter("test.svg");

    writer.Write(maze);
}

#endif

