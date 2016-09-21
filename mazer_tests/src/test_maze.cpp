//
// Created by Nicholas Amor on 21/9/16.
//

#include <iostream>

using namespace std;

void
test_add_edges()
{
    int width = 2;
    int height = 2;
    std::set<Edge> edges;

    /**
     *   |  |  |
     *   |_____|
     **/

    edges.emplace(0, 2, 1, 2);
    edges.emplace(1, 2, 2, 2);

    edges.emplace(2, 0, 2, 1);
    edges.emplace(2, 1, 2, 2);

    edges.emplace(0, 0, 1, 0);
    edges.emplace(1, 0, 1, 2);

    edges.emplace(0, 1, 1, 1);

    Maze maze(width, height, edges);

    cout << maze.ToJsonString() << '\n';
}

int
main()
{
    test_add_edges();
}
