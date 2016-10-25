//
// Created by Nicholas Amor on 22/10/16.
//

#include <list>
#include <stack>
#include "solver.h"

#include <iostream>
using namespace std;

using namespace mazer;

DfsSolver::DfsSolver(IMaze &maze) : maze(maze) {}

DfsSolver::~DfsSolver() {}

void DfsSolver::solve()
{
    std::vector<bool> visited(maze.getCells().size());
    std::vector<Cell *> parents(maze.getCells().size());
    std::stack<Cell *> stack;

    visited[0] = true;
    stack.push(&maze.getCell(0));

    while (!stack.empty())
    {
        auto& current = stack.top();
        stack.pop();

        for (auto& next : current->links)
        {
            if (!visited[next->i])
            {
                visited[next->i] = true;
                parents[next->i] = current;

                stack.push(next);
            }
        }
    }

    auto curr = &maze.getCell(maze.getCells().size() - 1);
    std::list<Cell *> solution;
    while (curr && parents[curr->i])
    {
        solution.push_front(curr);
        curr = parents[curr->i];
    }
    if (solution.size() > 0)
    {
        solution.push_front(&maze.getCell(0));
    }

    maze.setSolution(solution);
}
