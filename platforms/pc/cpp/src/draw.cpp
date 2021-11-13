#include "draw.h"
#include "food.h"

using namespace std;

int gridsize = 20;
int grid_height = 25;
int grid_width = 25;


void drawGrid(SDL_Window *window, SDL_Surface *window_surface)
{
    for(int x = 0; x<grid_width; x+=1)
    {
        for(int y = 0; y<grid_height; y+=1)
        {
            if((x+y)%2==0)
            {
                SDL_Rect rect = {x*gridsize, y*gridsize, gridsize, gridsize};
                SDL_FillRect(window_surface, &rect, SDL_MapRGB(window_surface->format, 0x20, 0x20, 0x20));   
            }
            else{
                SDL_Rect rect = {x*gridsize, y*gridsize, gridsize, gridsize};
                SDL_FillRect(window_surface, &rect, SDL_MapRGB(window_surface->format, 0x00, 0x00, 0x00)); 
            }
        }
    }
}

void drawSnake(SDL_Window *window, SDL_Surface *window_surface,std::vector<std::pair<int, int>> positions)
{
    for(int i = 0; i<positions.size(); i++)
    {
        SDL_Rect rect = {get<0>(positions[i])*gridsize, get<1>(positions[i])*gridsize, gridsize, gridsize};
        SDL_FillRect(window_surface, &rect, SDL_MapRGB(window_surface->format, 0xFF, 0xFF, 0xFF));
    }
}

void drawFood(SDL_Window *window, SDL_Surface *window_surface)
{
    SDL_Rect rect = {(foodPos.first)*gridsize, (foodPos.second)*gridsize, gridsize, gridsize};
    SDL_FillRect(window_surface, &rect, SDL_MapRGB(window_surface->format, 0xFF, 0x00, 0x00));
}