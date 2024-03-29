#include "../include/Engine.hpp"
#include "../include/Map.hpp"
#include "../include/Player.hpp"
#include "../include/Ray.hpp"
#include "../include/RenderWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <iostream>

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "ERR " << SDL_GetError() << std::endl;
  }

  if (!(IMG_Init(IMG_INIT_PNG))) {
    std::cout << "IMG INIT FAILED: " << SDL_GetError() << std::endl;
  }

  /****************************************************************************************************/

  s_Color mapColors = {200, 200, 200, 255};

  RenderWindow window("GAME", WINDOW_WIDTH, WINDOW_HEIGHT);
  Map map(&window, &mapColors, WALLSIZE);

  Player player(float(INIT_X + 2 * WALLSIZE), float(INIT_Y + 2 * WALLSIZE));

  Engine engine(&window);

  SDL_Event event;
  bool gameRunning = true;

  SDL_Rect playerSprite;

  s_Color playerColors = {0, 255, 0, 255};

  s_PlayerPos playerPos;
  player.getPos(&playerPos);

  Ray ray(&window);

  /****************************************************************************************************/

  window.clear();
  map.drawMap();
  player.drawPlayer(&window, &playerSprite, &playerColors);
  engine.renderScene(&playerPos);
  window.display();

  while (gameRunning) {
    while (SDL_PollEvent(&event)) {
      switch (event.key.keysym.sym) {
      case SDL_QUIT:
      case SDLK_ESCAPE:
        gameRunning = false;
        break;

      case SDLK_d:
        player.movePlayer(PLAYER_SPEED, 0);
        break;

      case SDLK_q:
        player.movePlayer(-PLAYER_SPEED, 0);
        break;

      case SDLK_s:
        player.movePlayer(0, PLAYER_SPEED);
        break;

      case SDLK_z:
        player.movePlayer(0, -PLAYER_SPEED);
        break;
      case SDLK_RIGHT:
        player.rotatePlayer(RIGHT);
        break;
      case SDLK_LEFT:
        player.rotatePlayer(LEFT);
        break;

      default:
        continue;
      }

      window.clear();
      map.drawMap();
      player.drawPlayer(&window, &playerSprite, &playerColors);
      player.getPos(&playerPos);
      engine.renderScene(&playerPos);
      window.display();
    }
  }

  window.cleanUp();
  SDL_Quit();

  return 0;
}
