//
// Created by Nicholas Amor on 19/10/16.
//

#ifndef SDLMAZER_MAIN_H
#define SDLMAZER_MAIN_H

#include "SDL.h"

class IDrawable
{
public:
  virtual ~IDrawable() = 0;
  virtual void draw(SDL_Renderer *renderer) = 0;
};

class App
{
public:
  App();
  void run();

private:
  static const int tile = 48;

  SDL_Window *window;
  SDL_Renderer *renderer;
};

class DrawableMaze
    : public IDrawable,
      public mazer::Maze
{
public:
  DrawableMaze(const unsigned w, const unsigned h);
  void draw(SDL_Renderer *renderer);

private:
  SDL_Point origin;
};

#endif
