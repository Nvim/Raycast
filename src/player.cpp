#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/Player.hpp"
#include "../include/Map.hpp"

Player::Player(const int p_x, const int p_y)
{
    playerX = p_x;
    playerY = p_y;
    playerAngle = PI;
    playerDeltaX = cos(playerAngle)*5;
    playerDeltaY = sin(playerAngle)*5;
}

void Player::getPos(s_PlayerPos * playerPos)
{
    playerPos->x = playerX;
    playerPos->y = playerY;
}

void Player::movePlayer(int p_x, int p_y)
{
    if (map[xyToIndex((playerY + p_y) /WALLSIZE, (playerX + p_x) /WALLSIZE)] != 1)
    {
        playerX += p_x;
        playerY += p_y;
        // std::cout << "map[ " << xyToIndex((playerY/WALLSIZE), (playerX/WALLSIZE)) << " ] == 0" << std::endl; 
    }
}

void Player::rotatePlayer(int direction)
{
    if (direction == LEFT)
    {
        playerAngle -= 0.1;
        if (playerAngle < 0)
        {
            playerAngle += 2*PI;
        }
        playerDeltaX = cos(playerAngle)*5;
        playerDeltaY = sin(playerAngle)*5;
    }
    else
    {
        playerAngle += 0.1;
        if (playerAngle > 2*PI)
        {
            playerAngle -= 2*PI;
        }
        playerDeltaX = cos(playerAngle)*5;
        playerDeltaY = sin(playerAngle)*5;
    }
}

void Player::drawPlayer( RenderWindow *window, SDL_Rect * playerSprite, s_Color * playerColors)
{
    playerSprite->x = playerX;
    playerSprite->y = playerY;
    playerSprite->h = PLAYER_SIZE;
    playerSprite->w = PLAYER_SIZE;
    window->renderFilledRectangle(playerSprite, playerColors);
    // window->renderLine(playerColors, playerX, playerY, playerX+6, playerY+6);  
    window->renderLine(playerColors, playerX, playerY, playerX+playerDeltaX*5, playerY+playerDeltaY*5);  
}


