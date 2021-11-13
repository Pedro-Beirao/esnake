#include "food.h"

using namespace std;

std::pair<int, int> foodPos;

bool eat(std::vector<std::pair<int, int>> positions, int length)
{
    std::pair<int, int> pos;
    for(auto pos : positions)
    {
        if (pos.first == foodPos.first && pos.second == foodPos.second)
        {
            randomize();
            return true;
        }
    }
    return false;
}

void randomize()
{
    foodPos.first = rand() % (20 - 1);
    foodPos.second = rand() % (20 - 1);
}

