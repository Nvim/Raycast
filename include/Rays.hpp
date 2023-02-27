#pragma once
#include "RenderWindow.hpp"
#include "Player.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#define DEPTH 8

class Rays
{
    private:
        float xStep, yStep, xNearest, yNearest;
        float rayX, rayY;
        RenderWindow *window;

    public:
        Rays(RenderWindow *p_window);
        void drawSimpleRay(s_PlayerPos *playerPos);
        void drawRays(s_PlayerPos *playerPos);
};
