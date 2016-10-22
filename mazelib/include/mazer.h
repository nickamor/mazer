//
// Created by Nicholas Amor on 14/10/16.
//

#ifndef LIBMAZER_MAZER_H
#define LIBMAZER_MAZER_H

#include <vector>
#include <deque>
#include "maze.h"
#include "solver.h"
#include "generator.h"
#include "writer.h"
#include "reader.h"

namespace mazer
{

class Maze
    : public IMaze
{
public:
  Maze(const unsigned w, const unsigned h);
    Maze(const Maze && maze);
  ~Maze();

  void clear();

  std::vector<Cell> &getCells();
  int getWidth();
  int getHeight();

  const std::deque<Cell *> &getSolution();
  void setSolution(const std::deque<Cell *> &path);

    void resize(int w, int h);

    std::set<Edge> getEdges();

    template <typename ReaderType>
    static Maze read(const std::string& filename)
    {
        ReaderType reader();
        return reader.read(filename);
    }

  template <typename WriterType>
  void write(const std::string &filename)
  {
    WriterType writer(*this);
    writer.write(filename);
  }

  template <typename GeneratorType = AldousBroderGen>
  void generate(int seed = 0)
  {
    GeneratorType generator(*this);

      if (seed > 0) {
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
  std::deque<Cell *> solution;
};
}

#endif //LIBMAZER_MAZER_H
