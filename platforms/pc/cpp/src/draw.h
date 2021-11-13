#ifndef DRAW_H
#define DRAW_H

#include <sdl.h>
#include "move.h"
#include "iostream"
#include <vector>

void drawGrid(SDL_Window *window, SDL_Surface *window_surface);
void drawSnake(SDL_Window *window, SDL_Surface *window_surface, std::vector<std::pair<int, int>> positions);
void drawFood(SDL_Window *window, SDL_Surface *window_surface);

#endif
