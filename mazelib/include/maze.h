//
// Created by Nicholas Amor on 14/10/16.
//

#ifndef MAZELIB_MAZE_H
#define MAZELIB_MAZE_H

#include <deque>
#include <vector>
#include <set>

namespace mazer
{

struct Cell
{
public:
  int x = -1, y = -1, i = -1;
  Cell *left = nullptr, *right = nullptr, *up = nullptr, *down = nullptr;
  std::vector<Cell *> links, nbrs;

  bool linkedTo(const Cell *cell) const;
};

struct Edge
{
public:
  int x1, y1, x2, y2;
  Edge(int x1, int y1, int x2, int y2);

  bool operator<(const Edge &rhs) const;

  bool operator>(const Edge &rhs) const;

  bool operator<=(const Edge &rhs) const;

  bool operator>=(const Edge &rhs) const;
};

class IMaze
{
public:
  virtual ~IMaze() = 0;

  virtual int getWidth() const = 0;
  virtual int getHeight() const = 0;
  virtual std::vector<Cell> &getCells() = 0;
    virtual Cell &getCell(int x, int y) = 0;
    virtual Cell &getCell(int i) = 0;

    virtual void link(Cell *lhs, Cell *rhs) = 0;

  virtual const std::deque<Cell *> &getSolution() = 0;
  virtual void setSolution(const std::deque<Cell *> &solution) = 0;

  virtual std::set<Edge> getEdges() const = 0;

  virtual void clear() = 0;
  virtual void resize(int w, int h) = 0;
};
}

#endif //MAZELIB_GENERATOR_H
