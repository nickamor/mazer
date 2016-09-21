//
// Created by Nicholas Amor on 21/9/16.
//

int
main(void)
{
    std::set <Edge> edges;
    auto maze = std::make_shared<Maze>(2, 2, edges);

    auto writer = MazeWriter("maze2.bin");

    writer.Write(maze);
}
