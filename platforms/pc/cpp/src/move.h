#ifndef MOVE_H
#define MOVE_H

#include <sdl.h>
#include "iostream"
#include <vector>
#include "food.h"
#include "main.h"

std::vector<std::pair<int, int>> moveSnake(std::pair<int,int> direction,std::vector<std::pair<int, int>> positions,int lenght);


#endif