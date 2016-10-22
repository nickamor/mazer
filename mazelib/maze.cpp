//
// Created by Nicholas Amor on 14/10/16.
//

#include <algorithm>
#include "maze.h"

using namespace mazer;

Cell::Cell(int x, int y, int i)
        : x(x), y(y), i(i),
          left(nullptr), right(nullptr), up(nullptr), down(nullptr) {}

Cell::Cell() : Cell(0, 0, 0) {}

bool Cell::linkedTo(const Cell *cell) const {
  return std::find(links.begin(), links.end(), cell) != std::end(links);
}

Edge::Edge(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

bool Edge::operator<(const Edge &edge) const
{
  return x1 < edge.x1
         || (edge.x1 >= x1 && y1 < edge.y1)
         || (edge.y1 >= y1 && x2 < edge.x2)
         || (edge.x2 >= x2 && y2 < edge.y2);
}

IMaze::~IMaze() {}

int IMaze::getWidth() const
{
  return -1;
}

int IMaze::getHeight() const
{
  return -1;
}

void IMaze::clear() {}

void IMaze::resize(int, int) {}
