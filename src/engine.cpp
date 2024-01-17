#include "../include/Engine.hpp"
#include "../include/Map.hpp"
#include "../include/Player.hpp"
#include "../include/Ray.hpp"
#include "../include/RenderWindow.hpp"
#include <SDL2/SDL_rect.h>
#include <cmath>
#include <iostream>
#include <math.h>
#include <ostream>

s_Color vWall = {0, 0, 255, 255};
s_Color hWall = {0, 0, 170, 255};

Engine::Engine(RenderWindow *p_window) { this->window = p_window; }

void Engine::drawColumn(s_PlayerPos *playerPos) {
  float playerX = playerPos->x;
  float playerY = playerPos->y;

  Ray ray(window);        // init ray
  ray.castRay(playerPos); // cast it

  float column_w = static_cast<float>(WINDOW_WIDTH) / NB_RAYS;

  SDL_Rect rect;

  rect.x = 0;
  rect.w = column_w;

  // TODO: finish this
}

void Engine::renderScene(s_PlayerPos *playerPos) {

  Ray ray(window); // init ray
  float column_w = static_cast<float>(WINDOW_WIDTH / 2.0) / NB_RAYS;
  SDL_Rect rect;
  rect.w = ceil(column_w);
  s_PlayerPos tmpPlayerPos = {playerPos->x, playerPos->y, playerPos->angle,
                              playerPos->deltaX, playerPos->deltaY};
  float fixedLength;
  float cosAngle;

  // float ang = (playerPos->angle) - DEG2RAD(1) * 30;
  tmpPlayerPos.angle += DEG2RAD(1) * 30;
  for (int i = 0; i < NB_RAYS; i++) {
    if (tmpPlayerPos.angle > 2 * M_PI) {
      tmpPlayerPos.angle -= 2 * M_PI;
    }
    if (tmpPlayerPos.angle < 0) {
      tmpPlayerPos.angle += 2 * M_PI;
    }
    ray.castRay(&tmpPlayerPos);
    ray.drawRay(&tmpPlayerPos);

    // real playerAngle - current ray's angle
    cosAngle = (playerPos->angle - tmpPlayerPos.angle);
    if (cosAngle > 2 * M_PI) {
      cosAngle -= 2 * M_PI;
    }
    if (cosAngle < 0) {
      cosAngle += 2 * M_PI;
    }

    fixedLength = ray.getLength() * cos(cosAngle);
    rect.h = fmin((WALLSIZE * WINDOW_HEIGHT) / fixedLength, WINDOW_HEIGHT);
    rect.y = (WINDOW_HEIGHT / 2) - (rect.h / 2);

    rect.x = (WINDOW_WIDTH / 2.0) + (i * column_w);

    if (ray.isHorizontal()) {
      window->renderFilledRectangle(&rect, &hWall);
    } else {
      window->renderFilledRectangle(&rect, &vWall);
    }
    std::cout << "Rectangle height: " << rect.h << " pixels." << std::endl;
    std::cout << "Rectangle width: " << rect.w << " pixels." << std::endl;
    tmpPlayerPos.angle -= DEG2RAD(1);
  }
}
