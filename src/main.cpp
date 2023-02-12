#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <iostream>
#include "../include/RenderWindow.hpp"



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
    window.clear();

    SDL_Event event;
    bool gameRunning = true;

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

    SDL_Rect *rect = new SDL_Rect;
    rect->y = 50;
    rect->x = 100;
    rect->w = 150;
    rect->h = 75;

    window.clear();
    window.renderRectangle(rect, 255, 255, 0, 255);
    window.display();
    window.clear();


    window.cleanUp();
    SDL_Quit();

    return 0;
}
