//
// Created by Nicholas Amor on 12/8/16.
//

#include "arguments_parser.h"
#include "reader.h"
#include "writer.h"
#include "svg_writer.h"
#include "generator.h"

using namespace mazer;

#ifndef __TEST__

int main(void) {
    auto gen = generator::factory(1, 64, 48);

    auto maze = gen->generate();

    auto writer = svg_writer("test.svg");

    writer.write(maze);
}

//int main(int argc, char const *argv[]) {
//    auto handler = arguments_parser(argc, argv);
//
//    auto tasks = handler.getTasks();
//
//    std::shared_ptr<Maze> maze = nullptr;
//
//    for (auto &task : tasks) {
//        if (task->is_input_task()) {
//            maze = task->read();
//        } else if (task->is_output_task()) {
//            task->write(maze);
//        } else {
//            task->run();
//        }
//
//        if (task->is_final_task()) {
//            break;
//        }
//    }
//
//    return 0;
//}

#else

int main() {}

#endif

