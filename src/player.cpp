#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../include/Player.hpp"
#include "../include/Map.hpp"

Player::Player(const int p_x, const int p_y)
{
    playerX = p_x;
    playerY = p_y;
}

void Player::getPos(s_PlayerPos * playerPos)
{
    playerPos->x = playerX;
    playerPos->y = playerY;
}

void Player::movePlayer(int p_x, int p_y)
{
    playerY += p_y;
    playerX += p_x;

    std::cout << xyToIndex(playerY, playerX ) << std::endl;

   //vérification que le joueur est dans la map 
   // if ( map[ xyToIndex(playerX + p_x, playerY + p_y) / mapCols ] == 1)
   // {
   //     std::cout << "WALL!" << std::endl;
   //     playerX += p_x;
   // }
}


