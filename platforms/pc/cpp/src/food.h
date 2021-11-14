#ifndef FOOD_H
#define FOOD_H

#include <SDL.h>
#include "iostream"
#include <vector>

bool eat(std::vector<std::pair<int, int>> positions, int length);
void randomize();

extern std::pair<int, int> foodPos;


#endif