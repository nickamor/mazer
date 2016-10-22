//
// Created by Nicholas Amor on 22/10/16.
//

#include <list>
#include "solver.h"

using namespace mazer;

BfsSolver::BfsSolver(IMaze &maze) : maze(maze) {}

BfsSolver::~BfsSolver() {}

/**
 * Use Breadth-First Search to find the shortest path from the first cell to
 * the last.
 */
void BfsSolver::solve()
{
    std::vector<bool> visited(maze.getCells().size());

    // The parent of a cell is it's BFS tree parent, and also the cell one
    // closer to the first cell than it.
    std::vector<Cell *> parents(maze.getCells().size());

    std::deque<Cell *> queue;

    visited[0] = true;
    queue.push_back(&maze.getCell(0));

    // Visit each cell in breadth-first order, calculating distance and parent.
    while (!queue.empty())
    {
        auto curr = queue.front();
        queue.pop_front();

        for (auto link : curr->links)
        {
            if (!visited[link->i])
            {
                visited[link->i] = true;
                parents[link->i] = curr;
                queue.push_back(link);
            }
        }
    }

    // Get the shortest path through the maze by walking from the last cell to
    // the first.
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
