#include "../include/Rays.hpp"
#include "../include/Player.hpp"
#include "../include/Map.hpp"

s_Color downColors = {0, 255, 0, 255};
s_Color upColors = {255, 0, 0, 255};

void Rays::drawRays(RenderWindow *window, s_PlayerPos *playerPos)
{

    int facing;
    int dy = playerPos->deltaY;
    s_Color lineColors;

    if (dy < 0)
    {
        facing = UP;
        lineColors = upColors; 
    }
    
    else
    {
        facing = DOWN;
        lineColors = downColors;
    }

    while(map[xyToIndex(playerPos->deltaX, dy)] != 1)
    {
        dy = dy+dy;
    }
    
    window->renderLine(&lineColors, playerPos->x, playerPos->y, playerPos->x+ playerPos->deltaX, playerPos->y+dy);  
}
