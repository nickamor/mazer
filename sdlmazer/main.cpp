
#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include <random>
#include "SDL.h"
#include "mazer.h"
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
    for (auto &edge : getEdges())
    {
        if (edge.special) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        SDL_RenderDrawLine(renderer,
                           origin.x + edge.x1 * tile,
                           origin.y + edge.y1 * tile,
                           origin.x + edge.x2 * tile,
                           origin.y + edge.y2 * tile);
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
                    case SDLK_e:
                        maze = std::make_unique<DrawableMaze>(10, 10);
                        maze->generate<EllerGen>();
                        maze->solve();
                        break;
                    case SDLK_g:
                        maze = std::make_unique<DrawableMaze>(10, 10);
                        maze->generate<AldousBroderGen>();
                        maze->solve();
                        break;
                    case SDLK_F1:
                        maze->write("maze.bin");
                        break;
                    case SDLK_F5:
                        maze->write<SvgWriter>("maze.svg");
                        break;
                    case SDLK_F2:
                        maze = std::make_unique<DrawableMaze>(10, 10);
                        maze->read("maze.bin");
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
//    try
//    {
        App app;
        app.run();
//    }
//    catch (std::exception &e)
//    {
//        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "A fatal error occurred.", e.what(), NULL);
//
//        return 1;
//    }
}
