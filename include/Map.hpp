#pragma once
#include "RenderWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>

#define WALLSIZE 64
#define INIT_X 0
#define INIT_Y 0

const int mapSize = 64;
const int mapCols = 8;
const int mapLines = 8;

const int map[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0,
    0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
    0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

int xyToIndex(int x, int y);

class Map {
public:
  Map(RenderWindow *p_win, s_Color *p_color, uint8_t p_wallsize);
  void drawMap();

private:
  RenderWindow *window;
  s_Color *color;
  uint8_t wallsize;
};
