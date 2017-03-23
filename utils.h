#include "graphics.h"
#include "walls.h"
#include "mob.h"
#include "item.h"

#define M_PI 3.14159265358979323846
#define VISION_CONE M_PI/4

float camera_x, camera_y, camera_z;
float view_x, view_y, view_z;

GLubyte getWorldAt(int x, int y, int z) {
  return world[x][y][z];
}

/* void generatePosition(int *x, int *z)
   assigns a value to x and z as a new position for a given object.
   Only allows values that are not within a wall space (i.e. between
   two pillars)
   Assumes the y height has already been established
*/
void generatePosition(int *x, int *z) {

  int randX, randZ;

  randX = rand() % 90;
  while (randX % 15 == 0) randX = rand() % 90;

  randZ = rand() % 90;
  while (randZ % 15 == 0) randZ = rand() % 90;

  *x = randX;
  *z = randZ;

}
