#pragma once
#include "Player.hpp"
#include "RenderWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define DEPTH 8
#define NB_RAYS 60

#define DEG2RAD(_d) ((_d) * (PI / 180.0f))
#define RAD2DEG(_d) ((_d) * (180.0f / PI))

typedef struct point {
  float x;
  float y;
} s_Point;

class Ray {
private:
  float xStep, yStep, xNearest, yNearest;
  float rayX, rayY; // coordinates of the end of the ray (1st wall hit)
  RenderWindow *window;
  bool horizontal; // has ray hit a horizontal wall?
  float length;    // ray's length

public:
  Ray(RenderWindow *p_window);                  // constructor
  void calculateLength(s_PlayerPos *playerPos); // sets lenght based on its XY
  float getLength();                            // returns lenght of current ray

  // casts a ray, sets RayX and RayY to 1st wall hit (also sets lenght):
  void castRay(s_PlayerPos *playerPos);

  // draws the ray on the map (you have to cast it before):
  void drawRay(s_PlayerPos *playerPos);

  // casts rays in a cone, and draws them:
  void drawRays(s_PlayerPos *playerPos);

  float getRayX();
  float getRayY();
  bool isHorizontal();
};
