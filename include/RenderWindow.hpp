#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_stdinc.h>

#define WINDOW_HEIGHT 512
#define WINDOW_WIDTH 1024

typedef struct Color {
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
} s_Color;

class RenderWindow {
public:
  RenderWindow(const char *p_title, int p_w, int p_h);
  void cleanUp();
  void clear();
  void renderRectangle(SDL_Rect *rect, s_Color *colors);
  void renderFilledRectangle(SDL_Rect *rect, s_Color *colors);
  void renderLine(s_Color *colors, int x1, int y1, int x2, int y2);
  void display();

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};
