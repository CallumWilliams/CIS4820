#include "mob.h"
#include "graphics.h"

void renderMob(int mobID, float mobX, float mobY, float mobZ, ORIENTATION o) {

  if (mobID > MOB_LIMIT) {
    printf("Mob count cannot exceed %d\n", MOB_LIMIT);
    exit(0);
  }

  //build center
  world[(int)mobX][(int)mobY][(int)mobZ] = 3;

  /*though the mob's "position" is in terms of floats, the actual positions
  on the grid will be in terms of integers*/

  switch(o) {
    case NORTH:
      
      break;
    case EAST:
      break;
    case SOUTH:
      break;
    case WEST:
      break;
    default://fail-safe
      printf("mob render error\n");
      exit(0);
  }

}

void rotateMob(int mobID, ORIENTATION newO) {



}
