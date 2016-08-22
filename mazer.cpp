#include "ArgHandler.h"
#include "FileReader.h"
#include "VectorWriter.h"

int main (void) {
    auto reader = FileReader("maze.bin");

    auto maze = reader.read();

    auto writer = VectorWriter("test.svg");

    writer.write(maze);
}

//int main(int argc, char const *argv[]) {
//    auto handler = ArgHandler(argc, argv);
//
//    auto tasks = handler.getTasks();
//
//    std::shared_ptr<Maze> maze = nullptr;
//
//    for (auto &task : tasks) {
//        if (task->isInputTask()) {
//            maze = task->read();
//        } else if (task->isOutputTask()) {
//            task->write(maze);
//        } else {
//            task->run();
//        }
//
//        if (task->isFinalTask()) {
//            break;
//        }
//    }
//
//    return 0;
//}
