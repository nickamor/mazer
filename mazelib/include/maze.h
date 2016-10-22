//
// Created by Nicholas Amor on 14/10/16.
//

#ifndef LIBMAZER_MAZE_H
#define LIBMAZER_MAZE_H

#include <deque>
#include <vector>
#include <set>

namespace mazer
{

struct Cell
{
public:
  int x, y, i;
  Cell *left, *right, *up, *down;
  std::vector<Cell *> links, nbrs;

  Cell(int x, int y, int i);
  Cell();
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

  virtual const std::deque<Cell *> &getSolution() = 0;
  virtual void setSolution(const std::deque<Cell *> &solution) = 0;

  virtual std::set<Edge> getEdges() const = 0;

  virtual void clear() = 0;
  virtual void resize(int w, int h) = 0;
};
}

#endif //LIBMAZER_GENERATOR_H
