#include "../include/Rays.hpp"


Rays::Rays(int playerAngle)
{
    rayAngle = playerAngle;
}

void Rays::drawRays(RenderWindow *window)
{
    int i;
    float aTan;
    

    for (i = 0; i<1; i++)
    {
        aTan = -1/tan(rayAngle);
        
        //horizontal rays:
        //look if ray is up or down with pi
        //faut tous les bails du player ça me clc
    }
}
