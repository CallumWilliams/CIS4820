#include "graphics.h"
#include "walls.h"
#include "mob.h"

#define M_PI 3.14159265358979323846
#define VISION_CONE M_PI/4

float camera_x, camera_y, camera_z;
float view_x, view_y, view_z;

GLubyte getWorldAt(int x, int y, int z) {
  return world[x][y][z];
}
