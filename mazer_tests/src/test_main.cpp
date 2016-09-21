//
// Created by Nicholas Amor on 21/9/16.
//

int
main(void)
{
    auto gen = MazeGenerator::Factory(1, 64, 48);

    auto maze = gen->Generate();

    auto writer = MazeSvgWriter("test.svg");

    writer.Write(maze);
}
