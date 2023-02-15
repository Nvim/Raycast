#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include "../include/RenderWindow.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
{

    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "Window failed to init, Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL || renderer == nullptr)
    {
        std::cout << "Renderer failed: " << SDL_GetError() << std::endl;
    }
    else
    {
        std::cout << "Render W" << std::endl;
    }

}

void RenderWindow::renderRectangle(SDL_Rect *rect, s_Color *colors)
{
    SDL_SetRenderDrawColor(renderer, colors->r, colors->g, colors->b, colors->a);
    if ( SDL_RenderDrawRect(renderer, rect) < 0)
    {
        std::cout << "Erreur Creation Rectangle: " << SDL_GetError() << std::endl;
    }

}

void RenderWindow::renderFilledRectangle(SDL_Rect *rect, s_Color *colors)
{
    SDL_SetRenderDrawColor(renderer, colors->r, colors->g, colors->b, colors->a);
    if (SDL_RenderFillRect(renderer, rect) < 0)
    {
        std::cout << "Erreur Fill Rectangle: " << SDL_GetError() << std::endl;
    }
}

void RenderWindow::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);  
    std::cout << "Cleanup done" << std::endl;
}
