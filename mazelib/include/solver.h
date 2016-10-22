//
// Created by Nicholas Amor on 14/10/16.
//

#ifndef MAZELIB_SOLVER_H
#define MAZELIB_SOLVER_H

#include <deque>
#include "maze.h"

namespace mazer
{

class ISolver
{
  public:
    virtual ~ISolver() = 0;

    virtual void solve() = 0;
};

class BfsSolver
    : public ISolver
{
  public:
    BfsSolver(IMaze &maze);
    ~BfsSolver();

    void solve();

  private:
    IMaze &maze;
};

class DfsSolver
    : public ISolver
{
  public:
    DfsSolver(IMaze &maze);
    ~DfsSolver();
};

/** 
 * Implements Dijkstra's algorithm. Uses the Template Method pattern: subclasses
 * must implement the heuristic.
 */
class DijkstraSolver
    : public ISolver
{
  public:
    DijkstraSolver(IMaze &maze);
    ~DijkstraSolver();

    void solve();
    virtual int heuristic(const int x, const int y) = 0;

  protected:
    IMaze &maze;
};

class DijkstraManhattan
    : public DijkstraSolver
{
  public:
    DijkstraManhattan(IMaze &maze);
    ~DijkstraManhattan();
};

class DijkstraEuclidean
    : public DijkstraSolver
{
    DijkstraEuclidean(IMaze &maze);
    ~DijkstraEuclidean();
};
}

#endif //MAZELIB_SOLVER_H
