#include "graphics.h"
#include "walls.h"
#include "mob.h"

float camera_x, camera_y, camera_z;
float view_x, view_y, view_z;

GLubyte getWorldAt(int x, int y, int z) {
  return world[x][y][z];
}
