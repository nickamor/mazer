
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <exception>
#include <iostream>
#include <random>
#include <vector>
#include "mazer.h"
#include "SDL.h"
#include "main.h"

using namespace mazer;

using namespace std;

IDrawable::~IDrawable() {}

void IDrawable::draw(SDL_Renderer *) {}

DrawableMaze::DrawableMaze(const unsigned w, const unsigned h) : Maze(w, h)
{
    origin.x = 5;
    origin.y = 5;
}

void DrawableMaze::draw(SDL_Renderer *renderer)
{
    static const int tile = 48;

    // draw edges
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(auto &edge : getEdges())
    {
        SDL_RenderDrawLine(renderer,
                           origin.x + edge.x1 * tile,
                           origin.y + edge.y1 * tile,
                           origin.x + edge.x2 * tile,
                           origin.y + edge.y2 * tile
        );
    }

    // draw solution path
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (auto &cell : getSolution())
    {
        SDL_RenderDrawPoint(renderer, 5 + 24 + cell->x * tile, 5 + 24 + cell->y * tile);
    }
}

App::App()
{
    SDL_CreateWindowAndRenderer(1024, 768, 0, &window, &renderer);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void App::run()
{
    auto maze = std::make_unique<DrawableMaze>(10, 10);
//    maze->generate();
//    maze->solve();

    SDL_Event event;
    bool done = false;
    while (!done)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    done = true;
                    break;
                case SDLK_g:
                    maze = std::make_unique<DrawableMaze>(10, 10);
                    maze->generate<EllerGen>();
                    maze->solve();
                    break;
                default:
                    break;
                }
                break;
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        maze->draw(renderer);

        SDL_RenderPresent(renderer);
    }
}

int main()
{
    try
    {
        App app;
        app.run();
    }
    catch (std::exception &e)
    {
        cerr << e.what() << endl;
    }
}