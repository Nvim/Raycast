#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <iostream>
#include "../include/RenderWindow.hpp"
#include "../include/Map.hpp"
#include "../include/Player.hpp"
#include "../include/Rays.hpp"

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "ERR " << SDL_GetError() << std::endl;
    }

    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG INIT FAILED: " << SDL_GetError() << std::endl;
    }

/****************************************************************************************************/

    s_Color mapColors = {200, 200, 200, 255};
    
    RenderWindow window("GAME", 800, 600);
    Map map(&window, &mapColors, WALLSIZE);

    Player player(INIT_X + 2*WALLSIZE, INIT_Y + 2*WALLSIZE);
    
    SDL_Event event;
    bool gameRunning = true;

    SDL_Rect playerSprite;

    s_Color playerColors = {0, 255, 0, 255};

    s_PlayerPos playerPos;
    player.getPos(&playerPos);

    Rays ray;

/****************************************************************************************************/
    
    window.clear();
    map.drawMap();
    player.drawPlayer(&window, &playerSprite, &playerColors);
    ray.drawRays(&window, &playerPos);

    window.display();

    while(gameRunning)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.key.keysym.sym)
            {
                case SDL_QUIT:
                case SDLK_ESCAPE:
                    gameRunning = false;
                    break;

                case SDLK_d:
                    player.movePlayer(PLAYER_SPEED, 0);
                    break;

                case SDLK_q:
                    player.movePlayer(-PLAYER_SPEED, 0);
                    break;

                case SDLK_s:
                    player.movePlayer(0, PLAYER_SPEED);
                    break;

                case SDLK_z: 
                    player.movePlayer(0, -PLAYER_SPEED);
                    break;
                case SDLK_RIGHT:
                    player.rotatePlayer(RIGHT);
                    break;
                case SDLK_LEFT:
                    player.rotatePlayer(LEFT);
                    break;

                default:
                    continue;
            }

            window.clear();
            map.drawMap();
            player.drawPlayer(&window, &playerSprite, &playerColors);
            player.getPos(&playerPos);
            ray.drawRays(&window, &playerPos);
            window.display();
        }
    }


    window.cleanUp();
    SDL_Quit();

    return 0;
}
