//
// Created by Nicholas Amor on 21/9/16.
//

void
test_add_links()
{
    MazeBuilder builder(2, 2);

    auto cell = builder.CellAt(0, 0);

    builder.AddLink(cell, cell->south);
    cell = cell->south;

    builder.AddLink(cell, cell->east);
    cell = cell->east;

    builder.AddLink(cell, cell->north);

    builder.AddExits();

    auto maze = builder.ToMaze();

    std::cout << maze->ToJsonString() << std::endl;
}

int
main()
{
    test_add_links();
}
