#pragma once
#include "Player.hpp"
#include "RenderWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#define DEPTH 8

typedef struct point {
  float x;
  float y;
} s_Point;

class Rays {
private:
  float xStep, yStep, xNearest, yNearest;
  float rayX, rayY;
  RenderWindow *window;

public:
  Rays(RenderWindow *p_window);
  float getLength(s_PlayerPos *playerPos);
  s_Point *castRay(s_PlayerPos *playerPos);
  void drawRay(s_PlayerPos *playerPos);
  void drawRays(s_PlayerPos *playerPos);
};
