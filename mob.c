#include "mob.h"
#include "graphics.h"

void renderMob(int mobID, float mobX, float mobY, float mobZ, ORIENTATION o) {

  if (mobID >= MOB_LIMIT) {
    printf("Mob count cannot exceed %d\n", MOB_LIMIT);
    exit(0);
  }

  if (world[(int)mobX][(int)mobY][(int)mobZ] != 0) {
    printf("Mob intersecting with terrain - error\n");
    exit(0);
  }

  MOB[mobID].mob_x = mobX;
  MOB[mobID].mob_y = mobY;
  MOB[mobID].mob_z = mobZ;
  MOB[mobID].mob_rot = o;

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

  MOB[mobID].mobEnabled = 1;

}

void eraseMob(int mobID) {

  int i, j;

  if (mobID >= MOB_LIMIT) {
    printf("Mob id cannot exceed %d\n", MOB_LIMIT);
    exit(0);
  } else if (!MOB[mobID].mobEnabled) {
    printf("Mob %d not enabled\n", mobID);
    exit(0);
  }

  for (i = MOB[mobID].mob_x - 1; i <= MOB[mobID].mob_x + 1; i++)
    for (j = MOB[mobID].mob_z - 1; j <= MOB[mobID].mob_z + 1; j++)
      world[i][(int)MOB[mobID].mob_y][j] = 0;

  MOB[mobID].mobEnabled = 0;

}

void rotateMob(int mobID, ORIENTATION newO) {

  int i, j;

  if (mobID >= MOB_LIMIT) {
    printf("Mob id cannot exceed %d\n", MOB_LIMIT);
    exit(0);
  }

  //erase old mob
  eraseMob(mobID);

  //re-render
  renderMob(mobID, MOB[mobID].mob_x, MOB[mobID].mob_y, MOB[mobID].mob_z, newO);

}

void moveMob(int mobID) {

  printf("mob at %lf, %lf, %lf\n", MOB[mobID].mob_x, MOB[mobID].mob_y, MOB[mobID].mob_z);
  switch (MOB[mobID].mob_rot) {

    case NORTH: //UP
      MOB[mobID].mob_x += MOB_SPEED;
      break;
    case EAST: //RIGHT
      MOB[mobID].mob_z += MOB_SPEED;
      break;
    case SOUTH: //DOWN
      MOB[mobID].mob_x -= MOB_SPEED;
      break;
    case WEST: //LEFT
      MOB[mobID].mob_z -= MOB_SPEED;
      break;
    default:
      printf("orientation error detected\n");
      exit(0);

    //visual update
    eraseMob(mobID);
    renderMob(mobID, MOB[mobID].mob_x, MOB[mobID].mob_y, MOB[mobID].mob_z, MOB[mobID].mob_rot);

  }

}

int hasCollision(int mobID) {

  return 0;

}
