#include "maze.h"
#include "maze_reader.h"
#include "maze_svg_writer.h"

int main(void) {
    auto reader = MazeReader("maze.maze");

    auto maze = reader.Read();

    auto writer = MazeSvgWriter("test.svg");

    writer.Write(maze);
}
