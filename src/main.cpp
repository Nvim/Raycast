#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <iostream>
#include "../include/RenderWindow.hpp"
#include "../include/Map.hpp"


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

    RenderWindow window("GAME", 800, 600);
    s_Color colors = {100, 0, 255, 255};
    Map map(&window, &colors, 25);
    SDL_Event event;
    bool gameRunning = true;

    
    window.clear();

    map.drawMap();

    window.display();
    window.clear();

    while(gameRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                gameRunning = false;
            }
        }
    }


    window.cleanUp();
    SDL_Quit();

    return 0;
}
