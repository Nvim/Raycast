#include "../include/Rays.hpp"
#include "../include/Map.hpp"
#include "../include/Player.hpp"
#include <iostream>
#include <math.h>

s_Color downColors = {0, 255, 0, 255};
s_Color upColors = {255, 0, 0, 255};
s_Color blue = {0, 0, 255, 255};

float degToRad(int a) { return a * M_PI / 180.0; }

int roundToWS(int nb) {
  int quotient = nb / WALLSIZE;
  int res;

  if ((nb % WALLSIZE) + 1 > WALLSIZE / 2) {
    res = quotient * WALLSIZE + WALLSIZE;
  }

  else {
    res = quotient * WALLSIZE;
  }
  return res;
}

// true si look up, false si down
bool lookUp(s_PlayerPos *playerPos) {
  if (playerPos->angle < PI) {
    return true;
  }
  return false;
}

bool lookRight(s_PlayerPos *playerPos) {
  if (!(playerPos->angle > PI / 2 && playerPos->angle < 3 * PI / 2)) {
    return true;
  }
  return false;
}

Rays::Rays(RenderWindow *p_window) {
  this->window = p_window;
  rayX = 0;
  rayY = 0;
  xNearest = 0;
  yNearest = 0;
  xStep = 0;
  yStep = 0;
}

// uses playerpos & rayX/Y => no args ?
float Rays::getLength(s_PlayerPos *playerPos) {
  float length;
  float x_x, x_y; // point arbitraire pour pythagore
  float px, xr;

  x_x = rayX;
  x_y = playerPos->y;

  if (x_x > playerPos->x) {
    px = x_x - playerPos->x;
  } else {
    px = playerPos->x - x_x;
  }

  if (x_y > playerPos->y) {
    xr = x_y - playerPos->y;
  } else {
    xr = playerPos->y - x_y;
  }

  length = sqrt((px * px) + (xr * xr));
  return length;
}

s_Point *Rays::castRay(s_PlayerPos *playerPos) {
  float playerX = playerPos->x;
  float playerY = playerPos->y;
  float playerAngle = playerPos->angle;
  s_Color lineColors = {0, 100, 200, 255};
  float aTan = tan(playerAngle);
  int DOF = 10;
  int ix, iy;
  bool horizontal = false, vertical = false;
  float hDist = -1.0, vDist = -1.0;
  float hRayX = -1.0, hRayY = -1.0;

  /* HORIZONTAL CHECKING */
  if (aTan != 0) {
    // calculations:
    yNearest = -(playerY - (int)(playerY / WALLSIZE) *
                               WALLSIZE); // valeur négative, on doit y ajouter
                                          // wallsize si on regarde vers le haut
    if (!lookUp(playerPos)) {
      yNearest += WALLSIZE;
    }
    xNearest = -yNearest / tan(playerAngle); // tan(angle) varie entre -infini
    // et infini, racines = 0, PI, 2PI.

    yStep = -WALLSIZE; // valeur négative, si on regarde vers le bas, elle doit
    // être positive.
    if (!lookUp(playerPos)) {
      yStep = WALLSIZE;
    }
    xStep = -yStep / tan(playerAngle);

    // setting rayX & rayY and incrementing until wall:
    rayX = playerX + xNearest;
    rayY = playerY + yNearest;
    int mapindex = xyToIndex(rayY, rayX);

    for (int i = 0; i < DOF; i++) {

      ix = int(rayX / WALLSIZE);
      iy = int(rayY / WALLSIZE);

      if (lookUp(playerPos)) {
        iy -= 1;
      }

      if (ix < 0 || iy < 0 || ix > 8 || iy > 8) {
        break;
      }

      if (map[xyToIndex(iy, ix)] == 1) {
        horizontal = true;
        // window->renderLine(&upColors, playerPos->x, playerPos->y, rayX,
        // rayY);
        break;
      }

      rayX += xStep;
      rayY += yStep;
    }
    hDist = getLength(playerPos);
    hRayX = rayX, hRayY = rayY;
  }

  /* VERTICAL CHECKING */
  if (aTan != 1) {
    xNearest = -(playerX - (int)(playerX / WALLSIZE) * WALLSIZE);
    if (lookRight(playerPos))
      xNearest += WALLSIZE;

    yNearest = tan(playerAngle) * xNearest;

    xStep = WALLSIZE;
    if (!lookRight(playerPos))
      xStep = -xStep;

    yStep = tan(playerAngle) * xStep;

    rayX = playerX + xNearest;
    rayY = playerY - yNearest;

    for (int i = 0; i < DOF; i++) {

      ix = int(rayX / WALLSIZE) - 1;
      iy = int(rayY / WALLSIZE);

      if (lookRight(playerPos)) {
        ix += 1;
      }

      if (ix < 0 || iy < 0 || ix > 8 || iy > 8) {
      }

      else if (map[xyToIndex(iy, ix)] == 1) {

        vertical = true;
        // window->renderLine(&downColors, playerPos->x, playerPos->y, rayX,
        // rayY);
        break;
      }

      rayX += xStep;
      rayY -= yStep;
    }
    vDist = getLength(playerPos);
  }

  s_Point *point;

  /* COMPARAISON */
  if (hDist < vDist) {
    point->x = hRayX;
    point->y = hRayY;
    return point;
  } else {
    point->x = rayX;
    point->y = rayY;
    return point;
  }
  point->x = 0;
  point->y = 0;
  return point;
}

void Rays::drawRay(s_PlayerPos *playerPos) {
  s_Point *point;
  point = castRay(playerPos);
  window->renderLine(&blue, playerPos->x, playerPos->y, point->x, point->y);
}
