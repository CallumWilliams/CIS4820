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

void WORLDDRAW() {

  int i, j, k;
  /* build ground (same as -testworld) */
  for (i = 0; i < 90; i++) {
     for (j = 0; j < 90; j++) {
        world[i][24][j] = 6;
     }
  }

  /* build pillars */
  for (i = 1; i < 6; i++) {
     for (j = 1; j < 6; j++) {
        for (k = 25; k < 30; k++) {
           world[i*15][k][j*15] = 6;
        }
     }
  }

  generateWalls();

  /* boundary box */
  for (i = 0; i < 90-1; i++) {
     for (j = 25; j < 30; j++) {
        world[i][j][0] = 6;
        world[i][j][89] = 6;
     }
  }
  for (i = 0; i < 90; i++) {
     for (j = 25; j < 30; j++) {
        world[0][j][i] = 6;
        world[89][j][i] = 6;
     }
  }

  /* exit door */
  for (i = 5; i < 10; i++) {
    for (j = 25; j < 30; j++) {
      world[i][j][89] = 8;
    }
  }

  /* place player/entities */
  initMobs();
  //hard-coded initial positions
  renderMob(0, 25, 25, 25, NORTH);
  renderMob(1, 70, 25, 70, SOUTH);
  renderMob(2, 40, 25, 55, WEST);
  renderMob(3, 25, 25, 70, EAST);

  //object generation (random)
  int itemX, itemZ;
  for (i = 0; i < 7; i++) {
    generatePosition(&itemX, &itemZ);
    switch (i) {
      case 0:
        generateObject(i, KEY, itemX, 25, itemZ);
        break;
      case 1:
      case 2:
        generateObject(i, TELEPORT, itemX, 25, itemZ);
        break;
      case 3:
      case 4:
        generateObject(i, BOUNCE, itemX, 25, itemZ);
        break;
      case 5:
      case 6:
        generateObject(i, FALL_CUBE, itemX, 25, itemZ);
        break;
      default:
        printf("Unexpected item generation ID %d\n", i);
        exit(0);
    }
  }


}

void WORLDRESET() {
  int i, j;

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 5; j++) {
      H_Walls[j][i].enabled = 0;
      V_Walls[i][j].enabled = 0;
    }
  }

  initWalls();
  initMobs();
  initItems();

  WORLDDRAW();

}
