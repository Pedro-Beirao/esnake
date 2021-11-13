#include "move.h"
#include "food.h"

using namespace std;



std::vector<std::pair<int, int>> moveSnake(std::pair<int,int> direction,std::vector<std::pair<int, int>> positions, int length)
{
    positions.insert(positions.begin(), make_pair(get<0>(positions[0]) + direction.first, get<1>(positions[0]) + direction.second));
    std::vector<std::pair<int, int>> newPositions;
    if(eat(positions, length))
    {
        newPositions.insert(newPositions.begin(), positions[0]);
    }
    for(int p = 0; p < length; p++)
    {
        newPositions.insert(newPositions.end(), positions[p]);
    }

    return newPositions;
}