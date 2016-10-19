//
// Created by Nicholas Amor on 14/10/16.
//

#include "maze.h"

using namespace mazer;

Edge::Edge(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

bool Edge::operator<(const Edge &rhs) const {
  if (x1 < rhs.x1)
    return true;
  if (rhs.x1 < x1)
    return false;
  if (y1 < rhs.y1)
    return true;
  if (rhs.y1 < y1)
    return false;
  if (x2 < rhs.x2)
    return true;
  if (rhs.x2 < x2)
    return false;
  return y2 < rhs.y2;
}

bool Edge::operator>(const Edge &rhs) const {
  return rhs < *this;
}

bool Edge::operator<=(const Edge &rhs) const {
  return !(rhs < *this);
}

bool Edge::operator>=(const Edge &rhs) const {
  return !(*this < rhs);
}

Cell::Cell(int x, int y, int i) : x(x), y(y), i(i) {}

Cell::Cell() : Cell(0, 0, 0) {}

IMaze::~IMaze() {}

int IMaze::getWidth()
{
    return -1;
}

int IMaze::getHeight()
{
    return -1;
}

void IMaze::clear() {}

void IMaze::resize(int, int) {}
