#pragma once
#include "RenderWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#define PI 3.1415926535
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define PLAYER_SPEED 5
#define PLAYER_SIZE 5

typedef struct playerPos
{
    int x;
    int y;
    float angle;
    float deltaX;
    float deltaY;
} s_PlayerPos;

class Player
{
    public:
        Player(const int p_x, const int p_y);
        void getPos(s_PlayerPos * playerPos);
        void movePlayer(int p_x, int p_y);
        void rotatePlayer(int direction);
        void drawPlayer(RenderWindow *window, SDL_Rect *playerSprite, s_Color * playerColors);

    private:

        int playerX;
        int playerY;
        float playerDeltaX;
        float playerDeltaY;
        float playerAngle;
};
