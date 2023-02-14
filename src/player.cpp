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
    playerX += p_x;
    playerY += p_y;

   //vérification que le joueur est dans la map 
   if ( map[ (playerX - INIT_X) / WALLSIZE ] == 0)
   {
       std::cout << "WALL!" << std::endl;
   }
}


