//
// Created by Nicholas Amor on 22/10/16.
//

#include <list>
#include <stack>
#include "solver.h"

using namespace mazer;

DfsSolver::DfsSolver(IMaze &maze) : maze(maze) {}

DfsSolver::~DfsSolver() {}

void DfsSolver::solve()
{
    std::vector<bool> visited(maze.getCells().size());

    std::vector<Cell *> parent(maze.getCells().size());

    std::stack<Cell *> stack;

    stack.push(&maze.getCell(0));

    while (!stack.empty())
    {
        auto& current = stack.top();
        stack.pop();

        if (!visited[current->i])
        {
            visited[current->i] = true;

            for (auto& next : current->links)
            {
                parent[next->i] = current;

                stack.push(next);
            }
        }
    }

    auto node = &maze.getCell(maze.getCells().size() - 1);
    std::list<Cell *> solution;
    while (node && parent[node->i])
    {
        solution.push_front(node);
        node = parent[node->i];
    }
    if (solution.size() > 0)
    {
        solution.push_front(&maze.getCell(0));
    }

    maze.setSolution(solution);
}
