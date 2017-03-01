#include "mob.h"
#include "graphics.h"

void renderMob(int mobID, float mobX, float mobY, float mobZ, ORIENTATION o) {

  if (mobID > MOB_LIMIT) {
    printf("Mob count cannot exceed %d\n", MOB_LIMIT);
    exit(0);
  }

  if (world[(int)mobX][(int)mobY][(int)mobZ] != 0) {
    printf("Mob intersecting with terrain - error\n");
    exit(0);
  }

  //build center
  world[(int)mobX][(int)mobY][(int)mobZ] = 8;

  /*though the mob's "position" is in terms of floats, the actual positions
  on the grid will be in terms of integers*/

  switch(o) {
    case NORTH:
      world[(int)mobX+1][(int)mobY][(int)mobZ] = 3; //head
      world[(int)mobX][(int)mobY][(int)mobZ-1] = 3;
      world[(int)mobX][(int)mobY][(int)mobZ+1] = 3;
      world[(int)mobX-1][(int)mobY][(int)mobZ-1] = 3;
      world[(int)mobX-1][(int)mobY][(int)mobZ+1] = 3;
      break;
    case EAST:
      world[(int)mobX][(int)mobY][(int)mobZ+1] = 3; //head
      world[(int)mobX-1][(int)mobY][(int)mobZ] = 3;
      world[(int)mobX+1][(int)mobY][(int)mobZ] = 3;
      world[(int)mobX-1][(int)mobY][(int)mobZ-1] = 3;
      world[(int)mobX+1][(int)mobY][(int)mobZ-1] = 3;
      break;
    case SOUTH:
      world[(int)mobX-1][(int)mobY][(int)mobZ] = 3; //head
      world[(int)mobX][(int)mobY][(int)mobZ+1] = 3;
      world[(int)mobX][(int)mobY][(int)mobZ-1] = 3;
      world[(int)mobX+1][(int)mobY][(int)mobZ+1] = 3;
      world[(int)mobX+1][(int)mobY][(int)mobZ-1] = 3;
      break;
    case WEST:
      world[(int)mobX][(int)mobY][(int)mobZ-1] = 3; //head
      world[(int)mobX-1][(int)mobY][(int)mobZ] = 3;
      world[(int)mobX+1][(int)mobY][(int)mobZ] = 3;
      world[(int)mobX-1][(int)mobY][(int)mobZ+1] = 3;
      world[(int)mobX+1][(int)mobY][(int)mobZ+1] = 3;
      break;
    default://fail-safe
      printf("mob render error\n");
      exit(0);
  }

}

void rotateMob(int mobID, ORIENTATION newO) {



}
