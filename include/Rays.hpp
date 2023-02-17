#pragma once
#include "RenderWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#define DEPTH 8

class Rays
{
    private:
        int rayX, rayY, xOffset, yOffset;
        float rayAngle;

    public:
        Rays(int playerAngle);
        void drawRays(RenderWindow *window);
};
