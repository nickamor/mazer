//
// Created by Nicholas Amor on 21/9/16.
//

int
main()
{
    auto gen = MazeGenerator::Factory(1, 50, 50);
    auto m = gen->Generate();

    std::cout << m << std::endl;
}
