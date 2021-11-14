#include "move.h"

using namespace std;



std::vector<std::pair<int, int>> moveSnake(std::pair<int,int> direction,std::vector<std::pair<int, int>> positions, int length)
{
    positions.insert(positions.begin(), make_pair(get<0>(positions[0]) + direction.first, get<1>(positions[0]) + direction.second));
    std::vector<std::pair<int, int>> newPositions;
    if(positions[0].first<0 || positions[0].first>24 || positions[0].second<0 || positions[0].second>24) // Snake is out of bounds, reset
    {
        return newPositions;
    }
    {
        reset();
        return {make_pair(5,10), make_pair(6,10)};
    }
    if(eat(positions, length)) // Snake ate an apple, add 1 to length
    {
        newPositions.insert(newPositions.begin(), positions[0]);
    }
    for(int p = 0; p < length; p++)
    {
        if(positions[p] == positions[0] && p != 0) // Snake is eating itself, reset
        {
            return newPositions;
        }
        {
            reset();
            return {make_pair(5,10), make_pair(6,10)};
        }
        newPositions.insert(newPositions.end(), positions[p]);
    }

    return newPositions;
}