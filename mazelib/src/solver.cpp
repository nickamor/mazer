//
// Created by Nicholas Amor on 14/10/16.
//

#include <algorithm>
#include "solver.h"

using namespace mazer;

ISolver::~ISolver() {}

void ISolver::solve() {}

void DijkstraSolver::solve()
{
    heuristic(0, 0);
}
