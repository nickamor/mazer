//
// Created by Nicholas Amor on 14/10/16.
//

#include "maze.h"

using namespace mazer;

Edge::Edge(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

bool Edge::operator<(const Edge &rhs) const
{
  return x1 < rhs.x1 && y1 < rhs.y1;
}

bool Edge::operator>(const Edge &rhs) const
{
  return rhs < *this;
}

bool Edge::operator<=(const Edge &rhs) const
{
  return !(rhs < *this);
}

bool Edge::operator>=(const Edge &rhs) const
{
  return !(*this < rhs);
}

Cell::Cell(int x, int y, int i)
    : x(x), y(y), i(i),
      left(nullptr), right(nullptr), up(nullptr), down(nullptr) {}

Cell::Cell() : Cell(0, 0, 0) {}

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
