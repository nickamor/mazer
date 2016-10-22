//
// Created by Nicholas Amor on 14/10/16.
//

#ifndef MAZELIB_MAZE_H
#define MAZELIB_MAZE_H

#include <list>
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
    bool special;

};

inline bool operator<(const Edge &lhs, const Edge &rhs)
{
    return lhs.x1 < rhs.x1
           || (rhs.x1 >= lhs.x1 && lhs.y1 < rhs.y1)
           || (rhs.y1 >= lhs.y1 && lhs.x2 < rhs.x2)
           || (rhs.x2 >= lhs.x2 && lhs.y2 < rhs.y2);
}

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

  virtual const std::list<Cell *> &getSolution() = 0;
  virtual void setSolution(const std::list<Cell *> &solution) = 0;

  virtual std::set<Edge> getEdges() const = 0;

  virtual void clear() = 0;
  virtual void resize(int w, int h) = 0;
};
}

#endif //MAZELIB_GENERATOR_H
