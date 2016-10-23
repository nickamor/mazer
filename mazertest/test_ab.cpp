//
// Created by Nicholas Amor on 22/10/16.
//

#include "mazer.h"

using namespace mazer;

int main(void)
{
    Maze maze(10, 10);
    maze.generate<AldousBroderGen>();
}
