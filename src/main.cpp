#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <iostream>
#include "../include/RenderWindow.hpp"
#include "../include/Map.hpp"
#include "../include/Player.hpp"

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

    s_Color colors = {100, 0, 255, 255};
    s_PlayerPos * playerPos = new s_PlayerPos;
    
    RenderWindow window("GAME", 800, 600);
    Map map(&window, &colors, WALLSIZE);
    Player player(INIT_X + 2*WALLSIZE, INIT_Y + 2*WALLSIZE);
    player.getPos(playerPos);
    
    SDL_Event event;
    bool gameRunning = true;

    SDL_Rect playerSprite;
    playerSprite.x = playerPos->x;
    playerSprite.y = playerPos->y;
    playerSprite.h = 5;
    playerSprite.w = 5;

    s_Color playerColors = {0, 255, 0, 255};


/****************************************************************************************************/
    
    window.clear();
    map.drawMap();
    window.renderFilledRectangle(&playerSprite, &playerColors);
    window.display();

    std::cout << "Player Position: (" << playerPos->x << ", " << playerPos->y << ")" << std::endl;

    while(gameRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                gameRunning = false;
                break;
            }
            
            switch(event.key.keysym.sym)
            {
                case SDLK_d:
                    player.movePlayer(PLAYER_SPEED, 0);
                    player.getPos(playerPos);
                    std::cout << "Player Position: (" << playerPos->x << ", " << playerPos->y << ")" << std::endl;
                    break;

                case SDLK_q:
                    player.movePlayer(-PLAYER_SPEED, 0);
                    player.getPos(playerPos);
                    std::cout << "Player Position: (" << playerPos->x << ", " << playerPos->y << ")" << std::endl;
                    break;

                case SDLK_s:
                    player.movePlayer(0, PLAYER_SPEED);
                    player.getPos(playerPos);
                    std::cout << "Player Position: (" << playerPos->x << ", " << playerPos->y << ")" << std::endl;
                    break;

                case SDLK_z:
                    player.movePlayer(0, -PLAYER_SPEED);
                    player.getPos(playerPos);
                    std::cout << "Player Position: (" << playerPos->x << ", " << playerPos->y << ")" << std::endl;
                    break;

                default:
                    continue;
            }
        }
    }


    window.cleanUp();
    SDL_Quit();

    return 0;
}
