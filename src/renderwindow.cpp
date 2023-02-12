#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include "../include/RenderWindow.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <iostream>

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{

    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "Window failed to init, Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

void RenderWindow::renderRectangle(SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    if ( SDL_RenderDrawRect(renderer, rect) < 0)
    {
        std::cout << "Erreur Creation Rectangle: " << SDL_GetError() << std::endl;
    }
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);  
}
