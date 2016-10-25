//
// Created by Nicholas Amor on 25/10/16.
//

#include <cmath>
#include "solver.h"

using namespace mazer;

DijkstraSolver::DijkstraSolver(IMaze &maze)
        : maze(maze)
{

}

DijkstraSolver::~DijkstraSolver() {}

void DijkstraSolver::solve()
{
    std::vector<Cell *> unvisited;
    std::vector<int> distance(maze.getCells().size());
    std::vector<Cell *> parent(maze.getCells().size());

    for (auto& cell : maze.getCells())
    {
        unvisited.push_back(&cell);
    }

    while (!unvisited.empty())
    {
        auto currentIter = std::find_if(unvisited.begin(), unvisited.end(), [distance](Cell* cell){
            return distance[cell->i] == 0;
        });
        auto& current = *currentIter;
        unvisited.erase(currentIter);

        for (auto& link : current->links)
        {
            auto alt = distance[current->i] + heuristic(link);

            if (distance[link->i] == 0 || alt < distance[link->i])
            {
                distance[link->i] = alt;
                parent[link->i] = current;
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

DijkstraManhattan::DijkstraManhattan(IMaze &maze) : DijkstraSolver(maze) {}

DijkstraManhattan::~DijkstraManhattan() {}

int DijkstraManhattan::heuristic(const Cell *cell) {
    return (maze.getWidth() - cell->x) + (maze.getHeight() - cell->y);
}

DijkstraEuclidean::DijkstraEuclidean(IMaze &maze) : DijkstraSolver(maze) {}

DijkstraEuclidean::~DijkstraEuclidean() {}

int DijkstraEuclidean::heuristic(const Cell *cell) {
    return int(std::sqrt(maze.getWidth() - cell->x
                         + maze.getHeight() - cell->y));
}
