//
// Created by Nicholas Amor on 14/10/16.
//

#include <algorithm>
#include "maze.h"

using namespace mazer;

bool Cell::linkedTo(const Cell *cell) const {
  return std::find(links.begin(), links.end(), cell) != std::end(links);
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
