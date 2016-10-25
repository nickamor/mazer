//
// Created by Nicholas Amor on 14/10/16.
//

#ifndef MAZELIB_MAZER_H
#define MAZELIB_MAZER_H

#include <list>
#include <vector>
#include "generator.h"
#include "maze.h"
#include "reader.h"
#include "solver.h"
#include "writer.h"

namespace mazer
{

class Maze
    : public IMaze
{
public:
  Maze(const unsigned w, const unsigned h);
    Maze();
  ~Maze();

  void clear();

  std::vector<Cell> &getCells();
    Cell &getCell(int x, int y);
    Cell &getCell(int i);

    void link(Cell *lhs, Cell *rhs);

  int getWidth() const;
  int getHeight() const;

  const std::list<Cell *> &getSolution();
  void setSolution(const std::list<Cell *> &path);

  void resize(int w, int h);

  std::set<Edge> getEdges() const;

  template <typename ReaderType = BinaryReader>
  void read(const std::string& filename)
  {
      ReaderType reader(*this);
      reader.read(filename);
  }

  template <typename WriterType = BinWriter>
  void write(const std::string &filename)
  {
    WriterType writer(*this);
    writer.write(filename);
  }

  template <typename GeneratorType = AldousBroderGen>
  void generate(int seed = 0)
  {
    GeneratorType generator(*this);

    if (seed > 0)
    {
      generator.seed(seed);
    }

    generator.generate();
  }

  template <typename SolverType = BfsSolver>
  void solve()
  {
    SolverType solver(*this);
    solver.solve();
  }

private:
  const int w, h;

  std::vector<Cell> cells;
  std::list<Cell *> solution;
};
}

#endif //MAZELIB_MAZER_H
