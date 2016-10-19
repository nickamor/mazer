//
// Created by Nicholas Amor on 14/10/16.
//

#include <algorithm>
#include "solver.h"

using namespace mazer;

ISolver::~ISolver() {}

void ISolver::solve()
{
}

BfsSolver::BfsSolver(IMaze &maze)
    : maze(maze)
{
}

BfsSolver::~BfsSolver() {}

/**
 * Use Breadth-First Search to find the shortest path from the first cell to 
 * the last.
 */
void BfsSolver::solve()
{
    const int w = maze.getWidth(), h = maze.getHeight();

    // The distance of a cell is the number of cells away from the start of the
    // grid, with the first cell having a distance of 1.
    std::vector<int> distances(w * h);

    // The parent of a cell is it's BFS tree parent, and also the cell one
    // closer to the first cell than it.
    std::vector<Cell *> parents(w * h);

    auto &cells = maze.getCells();

    std::deque<Cell *> queue;

    distances[0] = 1;
    parents[0] = nullptr;
    queue.push_back(&cells[0]);

    // Visit each cell in breadth-first order, calculating distance and parent.
    while (!queue.empty())
    {
        auto curr = queue.front();
        queue.pop_front();

        for (auto link : curr->links)
        {
            if (distances[link->i] == 0)
            {
                distances[link->i] = distances[curr->i] + 1;
                parents[link->i] = curr;
                queue.push_back(link);
            }
        }
    }

    // Get the shortest path through the maze by walking from the last cell to
    // the first.
    auto curr = &cells[w * h - 1];
    while (curr && parents[curr->i])
    {
        queue.push_front(curr);
        curr = parents[curr->i];
    }
    if (queue.size() > 0)
    {
        queue.push_front(&cells[0]);
    }

    maze.setSolution(queue);
}

void DijkstraSolver::solve()
{
    heuristic(0, 0);
}
