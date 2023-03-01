#include "../include/Rays.hpp"
#include "../include/Player.hpp"
#include "../include/Map.hpp"
#include <iostream>
#include <math.h>

s_Color downColors = {0, 255, 0, 255};
s_Color upColors = {255, 0, 0, 255};

float degToRad(int a)
{
    return a*M_PI/180.0;
}

int roundToWS(int nb)
{
    int quotient = nb/WALLSIZE;
    int res;

    if ((nb%WALLSIZE)+1 > WALLSIZE/2)
    {
        res = quotient*WALLSIZE +WALLSIZE;
    }

    else 
    {
        res = quotient*WALLSIZE;
    }
    return res;
}

//true si look up, false si down
bool lookUp(s_PlayerPos *playerPos)
{
    if (playerPos->angle < PI)
    {
        return true;
    }
    return false;
}

bool lookRight(s_PlayerPos *playerPos)
{
    if (!(playerPos->angle > PI/2 && playerPos->angle < 3*PI/2))
    {
        return true;
    }
    return false;
}

Rays::Rays(RenderWindow *p_window)
{
    this->window = p_window; 
    rayX = 0;
    rayY = 0;
    xNearest = 0;
    yNearest = 0;
    xStep = 0;
    yStep = 0;
}

void Rays::drawSimpleRay(s_PlayerPos *playerPos)
{
    s_Color lineColors = {0, 100, 200, 255};
    rayY = playerPos->deltaY;
    rayX = playerPos->deltaX;
    window->renderLine(&lineColors, playerPos->x, playerPos->y, playerPos->x + rayX, playerPos->y + rayY);  
}

void Rays::drawRays(s_PlayerPos *playerPos)
{
    float playerX = playerPos->x;
    float playerY = playerPos->y;
    float playerAngle = playerPos->angle;
    s_Color lineColors = {0, 100, 200, 255};
    float aTan = tan(playerAngle);
    int DOF = 10;
    int ix, iy;
    bool horizontal = false, vertical = false;


    /* HORIZONTAL CHECKING */
    if (aTan != 0)
    {
        //calculations:
        yNearest = -(playerY - (int)(playerY / WALLSIZE) * WALLSIZE);
        if (!lookUp(playerPos))
        {
            yNearest += WALLSIZE; 
        }
        xNearest = yNearest/tan(playerAngle);

        yStep = -WALLSIZE;
        if (!lookUp(playerPos))
        {
            yStep = -yStep; 
        }
        xStep = yStep/tan(playerAngle);

        //setting rayX & rayY and incrementing until wall:
            rayX = playerX + xNearest;
            rayY = playerY + yNearest;
        int mapindex = xyToIndex(rayY, rayX);

        for (int i = 0; i < DOF; i++)
        {

            ix = int(rayX / WALLSIZE);
            iy = int(rayY / WALLSIZE);

            if (lookUp(playerPos))
            {
                iy -=1;
            }

            if (ix < 0 || iy < 0 || ix > 8 || iy > 8)
            {
                break;
            }

            if (map[ xyToIndex(iy, ix) ] == 1)
            {
                horizontal = true;
                break;
            }

            rayX += xStep;
            rayY += yStep;
        }
        window->renderLine(&upColors, playerX, playerY, rayX, rayY);
    }

    /* VERTICAL CHECKING */
    if (aTan != 1)
    {
        xNearest = -(playerX - (int)(playerX / WALLSIZE) * WALLSIZE);
        if (lookRight(playerPos))
            xNearest += WALLSIZE;

        yNearest = tan(playerAngle)*xNearest;

        xStep = WALLSIZE;
        if (!lookRight(playerPos))
            xStep = -xStep;

        yStep = tan(playerAngle)*xStep;

        rayX = playerX + xNearest;
        rayY = playerY + yNearest;

        for (int i = 0; i < DOF; i++)
        {

            ix = int(rayX / WALLSIZE) -1;
            iy = int(rayY / WALLSIZE);

            if(lookRight(playerPos))
            {
                ix += 1;
            }

            if (ix < 0 || iy < 0 || ix > 8 || iy > 8)
            {
            }

            else if (map[ xyToIndex(iy, ix) ] == 1)
            {
                
                vertical = true;
                window->renderLine(&downColors, playerX, playerY, rayX, rayY);
                break;
            }

            rayX += xStep;
            rayY += yStep;
        }

    }
}
