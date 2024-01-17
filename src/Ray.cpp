#include "../include/Ray.hpp"
#include "../include/Map.hpp"
#include "../include/Player.hpp"
#include <iostream>
#include <iterator>
#include <math.h>
#include <ostream>

s_Color green = {0, 255, 0, 255};
s_Color red = {255, 0, 0, 255};
s_Color blue = {0, 0, 255, 255};
s_Color dark_blue = {0, 0, 190, 255};

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
  if (playerPos->angle < M_PI) {
    return true;
  }
  return false;
}

bool lookRight(s_PlayerPos *playerPos) {
  if (!(playerPos->angle > M_PI / 2 && playerPos->angle < 3 * M_PI / 2)) {
    return true;
  }
  return false;
}

Ray::Ray(RenderWindow *p_window) {
  this->window = p_window;
  rayX = 0;
  rayY = 0;
  xNearest = 0;
  yNearest = 0;
  xStep = 0;
  yStep = 0;
  horizontal = false;
  length = 0;
}

// uses playerpos & rayX/Y => no args ?
void Ray::calculateLength(s_PlayerPos *playerPos) {
  float playerX = playerPos->x;
  float playerY = playerPos->y;
  float lengthX, lengthY;

  if (lookUp(playerPos)) {
    lengthY = playerY - rayY;
  } else {
    lengthY = rayY - playerY;
  }

  if (lookRight(playerPos)) {
    lengthX = rayX - playerX;
  } else {
    lengthX = playerX - rayX;
  }

  length = sqrt((lengthX * lengthX) + (lengthY * lengthY));
}

float Ray::getLength() { return length; }

void Ray::castRay(s_PlayerPos *playerPos) {
  float playerX = playerPos->x;
  float playerY = playerPos->y;
  float playerAngle = playerPos->angle;
  float angleTan = tan(playerAngle);
  int DOF = 10;
  int ix, iy;
  float hDist = -1.0, vDist = -1.0;
  float hRayX = -1.0, hRayY = -1.0;

  /* HORIZONTAL CHECKING */
  if (angleTan != 0) {
    // valeur négative, on doit y ajouter wallsize si on regarde vers le haut
    yNearest = -(playerY - (int)(playerY / WALLSIZE) * WALLSIZE);

    if (!lookUp(playerPos)) {
      yNearest += WALLSIZE;
    }
    // -inf < angleTan < inf. racines = 0, PI, 2PI
    xNearest = -yNearest / angleTan;

    // valeur négative, si on regarde vers le bas, elle doit être positive.
    yStep = -WALLSIZE;
    if (!lookUp(playerPos)) {
      yStep = WALLSIZE;
    }
    xStep = -yStep / angleTan;

    // setting rayX & rayY and incrementing until wall:
    rayX = playerX + xNearest;
    rayY = playerY + yNearest;
    // int mapindex = xyToIndex(rayY, rayX);

    for (int i = 0; i < DOF; i++) {

      ix = int(rayX / WALLSIZE);
      iy = int(rayY / WALLSIZE);

      if (lookUp(playerPos)) {
        iy -= 1;
      }

      if (ix < 0 || iy < 0 || ix > 8 || iy > 8) {
        break;
      }

      // le rayon a percuté un mur horizontal
      if (map[xyToIndex(iy, ix)] == 1) {
        break;
      }

      rayX += xStep;
      rayY += yStep;
    }
    calculateLength(playerPos);
    hDist = length;
    hRayX = rayX, hRayY = rayY;
  }

  /* VERTICAL CHECKING */
  if (angleTan != 1) {
    xNearest = -(playerX - (int)(playerX / WALLSIZE) * WALLSIZE);
    if (lookRight(playerPos)) {
      xNearest += WALLSIZE;
    }

    yNearest = angleTan * xNearest;

    xStep = WALLSIZE;
    if (!lookRight(playerPos))
      xStep = -xStep;

    yStep = angleTan * xStep;

    rayX = playerX + xNearest;
    rayY = playerY - yNearest;

    for (int i = 0; i < DOF; i++) {

      ix = int(rayX / WALLSIZE) - 1;
      iy = int(rayY / WALLSIZE);

      if (lookRight(playerPos)) {
        ix += 1;
      }

      if (ix < 0 || iy < 0 || ix > 8 || iy > 8) {
        break; // not sure abt this
      }

      // le rayon a percuté un mur vertical
      else if (map[xyToIndex(iy, ix)] == 1) {
        break;
      }

      rayX += xStep;
      rayY -= yStep;
    }
    calculateLength(playerPos);
    vDist = length;
  }

  /* COMPARAISON */
  if (hDist < vDist) { // ray hit horizontal
    horizontal = true;
    rayX = hRayX;
    rayY = hRayY;
    length = hDist;
  } else {
    horizontal = false;
  }
}

void Ray::drawRay(s_PlayerPos *playerPos) {
  castRay(playerPos);
  if (horizontal == true) {
    window->renderLine(&red, playerPos->x, playerPos->y, rayX, rayY);
  } else {
    window->renderLine(&blue, playerPos->x, playerPos->y, rayX, rayY);
  }
}

void Ray::drawRays(s_PlayerPos *playerPos) {

  float ang = (playerPos->angle) - DEG2RAD(1) * 30;
  Ray r(window);

  for (int i = 0; i < NB_RAYS; i++) {
    if (ang > 2 * M_PI) {
      ang -= 2 * M_PI;
    }
    if (ang < 0) {
      ang += 2 * M_PI;
    }
    playerPos->angle = ang;
    r.drawRay(playerPos);
    std::cout << "Ray Length: " << r.getLength() << std::endl;
    ang += DEG2RAD(1);
  }
}

float Ray::getRayX() { return rayX; }

float Ray::getRayY() { return rayY; }

bool Ray::isHorizontal() { return horizontal; }
