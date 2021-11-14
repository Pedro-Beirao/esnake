#include "main.h"

using namespace std;

std::vector<std::pair<int, int>> positions;
std::deque<std::pair<int,int>> direction;
std::pair<int,int> dir;
int length;

// Reset snake to initial state
void reset()
{
    direction = {make_pair(1, 0)};
    dir = make_pair(1,0);
    length = 2;
}

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
    dir = make_pair(1,0);
    direction.push_back(make_pair(1, 0));
    positions.push_back(make_pair(5, 10));
    positions.push_back(make_pair(6, 10));
    initial_ticks = SDL_GetTicks();
    length = 2;
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
                    if(e.key.keysym.sym == SDLK_UP && direction[0] != make_pair(0, 1) && dir != make_pair(0, 1) && direction.size() < 3)
                    {
                        dir = make_pair(0, -1);
                        direction.push_back(make_pair(0, -1));
                    }
                    else if(e.key.keysym.sym == SDLK_DOWN && direction[0] != make_pair(0, -1)  && dir != make_pair(0, -1) && direction.size() < 3)
                    {
                        dir = make_pair(0, 1);
                        direction.push_back(make_pair(0, 1));
                    }
                    else if(e.key.keysym.sym == SDLK_LEFT && direction[0] != make_pair(1, 0) && dir != make_pair(1,0) && direction.size() < 3)
                    {
                        dir = make_pair(-1, 0);
                        direction.push_back(make_pair(-1, 0));
                    }
                    else if(e.key.keysym.sym == SDLK_RIGHT && direction[0] != make_pair(-1, 0) && dir != make_pair(-1, 0)  && direction.size() < 3)
                    {
                        dir = make_pair(1, 0);
                        direction.push_back(make_pair(1, 0));
                    }
                break;   
            }
        }
            if( initial_ticks + ms_frame < SDL_GetTicks())
            {
                if(direction.size() > 0)
                {
                    positions = moveSnake(direction[0],positions,length);
                    direction.pop_front();
                }
                else
                {
                    positions = moveSnake(dir,positions,length);
                }
                length = positions.size();
                drawGrid(window,window_surface);
                drawFood(window,window_surface);
                drawSnake(window,window_surface,positions);
                SDL_UpdateWindowSurface(window);
                initial_ticks = SDL_GetTicks();
            }
    }
}