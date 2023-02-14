#pragma once
#include "RenderWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define PLAYER_SPEED 5

typedef struct playerPos
{
    int x;
    int y;
} s_PlayerPos;

class Player
{
    public:
        Player(const int p_x, const int p_y);
        void getPos(s_PlayerPos * playerPos);
        void movePlayer(int p_x, int p_y);

    private:

        int playerX;
        int playerY;
};
