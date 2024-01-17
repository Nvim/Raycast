#pragma once

#include "Player.hpp"
#include "RenderWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Engine {
private:
  RenderWindow *window;
  s_PlayerPos *playerPos;

public:
  Engine(RenderWindow *p_window);
  void drawColumn(s_PlayerPos *playerPos);
  void renderScene(s_PlayerPos *playerPos);
};
