#include <SDL.h>
#include <iostream>
#include "draw.h"
#include "move.h"
#include "food.h"
#include <vector>

using namespace std;

std::vector<std::pair<int, int>> positions;

int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          500, 500,
                                          0);

    if(!window)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if(!window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return -1;
    }
    
    bool keep_window_open = true;
    const int ms_frame = 100;
    Uint32 initial_ticks, elapsed_ms;
    std::pair<int,int> direction = make_pair(1,0);
    positions.push_back(make_pair(5, 10));
    positions.push_back(make_pair(6, 10));
    initial_ticks = SDL_GetTicks();
    int length = 2;
    randomize();
    while(keep_window_open)
    {
        SDL_Event e;
        if(SDL_PollEvent(&e) > 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    keep_window_open = false;
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_UP:
                            direction = make_pair(0,-1);
                            break;
                        case SDLK_DOWN:
                            direction = make_pair(0,1);
                            break;
                        case SDLK_LEFT:
                            direction = make_pair(-1,0);
                            break;
                        case SDLK_RIGHT:
                            direction = make_pair(1,0);
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }
            if( initial_ticks + ms_frame < SDL_GetTicks())
            {
                positions = moveSnake(direction,positions,length);
                length = positions.size();
                drawGrid(window,window_surface);
                drawFood(window,window_surface);
                drawSnake(window,window_surface,positions);
                SDL_UpdateWindowSurface(window);
                initial_ticks = SDL_GetTicks();
            }
    }
}