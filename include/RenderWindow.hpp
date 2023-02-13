#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_stdinc.h>

typedef struct Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} s_Color;

class RenderWindow
{
    public:
       RenderWindow(const char* p_title, int p_w, int p_h); 
       void cleanUp();
       void clear();
       void renderRectangle(SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
       void display();

    private:

        SDL_Window* window;
        SDL_Renderer* renderer;
};
