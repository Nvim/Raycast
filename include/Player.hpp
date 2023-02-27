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
    float x;
    float y;
    float angle;
    float deltaX;
    float deltaY;
} s_PlayerPos;

class Player
{
    public:
        Player(const float p_x, const float p_y);
        void getPos(s_PlayerPos * playerPos);
        void movePlayer(int p_x, int p_y);
        void rotatePlayer(int direction);
        void drawPlayer(RenderWindow *window, SDL_Rect *playerSprite, s_Color * playerColors);

    private:

        float playerX;
        float playerY;
        float playerDeltaX;
        float playerDeltaY;
        float playerAngle;
};
