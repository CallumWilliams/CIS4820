#include <stdlib.h>
#include <math.h>

#include "mob.h"
#include "graphics.h"

extern float camera_x, camera_y, camera_z;

/*
  void initMobs()
  Sets all inital states for mobs
*/
void initMobs() {
  int i;
  for (i = 0; i < MOB_LIMIT; i++) {
    MOB[i].COLOUR_STATE = 0;
    MOB[i].mobEnabled = 0;
  }
}

void renderMob(int mobID, float mobX, float mobY, float mobZ, ORIENTATION o) {

  if (mobID >= MOB_LIMIT) {
    printf("Mob count cannot exceed %d\n", MOB_LIMIT);
    exit(0);
  }

  if (!checkBox((int)mobX, (int)mobY, (int)mobZ) && MOB[mobID].mobEnabled == 1) {
    printf("Mob %d intersecting with terrain - error\n", mobID);
    exit(0);
  }

  MOB[mobID].mob_x = mobX;
  MOB[mobID].mob_y = mobY;
  MOB[mobID].mob_z = mobZ;
  MOB[mobID].mob_rot = o;

  //build center
  if (MOB[mobID].COLOUR_STATE == 0)
    world[(int)mobX][(int)mobY][(int)mobZ] = 1;
  else
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

/*
  int checkBox(int x, int y, int z)
  Checks a 3x3 box around the world coordinate (x, z). Checks along the y plane,
  since that is the 'level' that the mob will be on. Returns 0 (false) if any
  square is not empty. Otherwise, returns 1 (true).
*/
int checkBox(int x, int y, int z) {

  int i, j;

  for (i = x-1; i <= x+1; i++)
    for (j = z-1; j <= z+1; j++)
      if (world[i][y][j] != 0) return 0;
  return 1;

}

void swapColour(int mobID) {

  if (MOB[mobID].COLOUR_STATE == 0) {
    MOB[mobID].COLOUR_STATE = 1;
    world[(int)MOB[mobID].mob_x][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z] = 1;
  } else {
    MOB[mobID].COLOUR_STATE = 0;
    world[(int)MOB[mobID].mob_x][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z] = 8;
  }


}

/*
  void eraseMob(int mobID)
  removes (not deletes) mob entity from screen
*/
void eraseMob(int mobID) {

  int i, j;

  if (mobID >= MOB_LIMIT) {
    printf("Mob id cannot exceed %d\n", MOB_LIMIT);
    exit(0);
  } else if (MOB[mobID].mobEnabled != 1) {
    printf("Mob %d not enabled\n", mobID);
    exit(0);
  }

  switch(MOB[mobID].mob_rot) {

    case NORTH:
      for (i = (int)MOB[mobID].mob_x - 2; i <= (int)MOB[mobID].mob_x + 1; i++)
        for (j = (int)MOB[mobID].mob_z - 1; j <= (int)MOB[mobID].mob_z + 1; j++)
          world[i][(int)MOB[mobID].mob_y][j] = 0;
      break;
    case EAST:
      for (i = (int)MOB[mobID].mob_x - 1; i <= (int)MOB[mobID].mob_x + 1; i++)
        for (j = (int)MOB[mobID].mob_z - 2; j <= (int)MOB[mobID].mob_z + 1; j++)
          world[i][(int)MOB[mobID].mob_y][j] = 0;
      break;
    case SOUTH:
    for (i = (int)MOB[mobID].mob_x - 1; i <= (int)MOB[mobID].mob_x + 2; i++)
      for (j = (int)MOB[mobID].mob_z - 1; j <= (int)MOB[mobID].mob_z + 1; j++)
        world[i][(int)MOB[mobID].mob_y][j] = 0;
    break;
    case WEST:
      for (i = (int)MOB[mobID].mob_x - 1; i <= (int)MOB[mobID].mob_x + 1; i++)
        for (j = (int)MOB[mobID].mob_z - 1; j <= (int)MOB[mobID].mob_z + 2; j++)
          world[i][(int)MOB[mobID].mob_y][j] = 0;
      break;
  }

}

/*
  void deleteMob(int mobID)
  deletes mob entity from game
*/
void deleteMob(int mobID) {

  eraseMob(mobID);
  MOB[mobID].mob_x = 0;
  MOB[mobID].mob_y = 0;
  MOB[mobID].mob_z = 0;
  MOB[mobID].mobEnabled = 0;

}

ORIENTATION selectNewMobOrientation(int mobID) {

  ORIENTATION newO;

  srand(time(NULL));
  do {
    newO = rand() % 4;
  } while(newO == MOB[mobID].mob_rot); //tests if new orientation has a collision conflict

  return newO;

}

void turnLeft(int mobID) {
  ORIENTATION n = (MOB[mobID].mob_rot - 1) % 4;
  rotateMob(mobID, n);
}

void turnRight(int mobID) {
  ORIENTATION n = (MOB[mobID].mob_rot + 1) % 4;
  rotateMob(mobID, n);
}

/*
  void rotateMob(int mobID, ORIENTATION newO)
  takes MOB[mobID].mob_rot and sets to newO, and then redraws the mob
*/
void rotateMob(int mobID, ORIENTATION newO) {

  int i, j;

  if (mobID >= MOB_LIMIT) {
    printf("Mob id cannot exceed %d\n", MOB_LIMIT);
    exit(0);
  } else if (MOB[mobID].mobEnabled != 1) {
    printf("Mob %d not enabled\n", mobID);
    exit(0);
  }

  //re-draw
  eraseMob(mobID);
  renderMob(mobID, MOB[mobID].mob_x, MOB[mobID].mob_y, MOB[mobID].mob_z, newO);

}

/*
  getOldMobPosition(int mobID)
  stores position of mob[mobID] before it moves.
*/
void getOldMobPosition(int mobID) {

  MOB[mobID].old_mob_x = MOB[mobID].mob_x;
  MOB[mobID].old_mob_y = MOB[mobID].mob_y;
  MOB[mobID].old_mob_z = MOB[mobID].mob_z;

}

/*
  goToOldPosition(int mobID)
  revert current position to a previous state.
*/
void goToOldPosition(int mobID) {

  eraseMob(mobID);
  MOB[mobID].mob_x = MOB[mobID].old_mob_x;
  MOB[mobID].mob_y = MOB[mobID].old_mob_y;
  MOB[mobID].mob_z = MOB[mobID].old_mob_z;
  renderMob(mobID, MOB[mobID].mob_x, MOB[mobID].mob_y, MOB[mobID].mob_z, MOB[mobID].mob_rot);

}

void moveMob(int mobID) {

  if (mobID >= MOB_LIMIT) {
    printf("Mob id cannot exceed %d\n", MOB_LIMIT);
    exit(0);
  } else if (!MOB[mobID].mobEnabled) {
    printf("Mob %d not enabled\n", mobID);
    exit(0);
  }

  getOldMobPosition(mobID);
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

  }

  //visual update
  eraseMob(mobID);
  renderMob(mobID, MOB[mobID].mob_x, MOB[mobID].mob_y, MOB[mobID].mob_z, MOB[mobID].mob_rot);

}

/*
  int hasCollision(int mobID)
  returns 1 (true) if the head/either of the wings of MOB[mobID] collides with
  an object (or a non-0 world array element). Otherwise, return 0 (false)
*/
int hasCollision(int mobID) {

  switch (MOB[mobID].mob_rot) {

    case NORTH: //UP
      if (world[(int)MOB[mobID].mob_x+2][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z] != 0)
        return 1;
      else if (world[(int)MOB[mobID].mob_x+1][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z+1] != 0)
        return 1;
      else if (world[(int)MOB[mobID].mob_x+1][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z-1] != 0)
        return 1;
      break;
    case EAST: //RIGHT
      if (world[(int)MOB[mobID].mob_x][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z+2] != 0)
        return 1;
      else if (world[(int)MOB[mobID].mob_x+1][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z+1] != 0)
        return 1;
      else if (world[(int)MOB[mobID].mob_x-1][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z+1] != 0)
        return 1;
      break;
    case SOUTH: //DOWN
      if (world[(int)MOB[mobID].mob_x-2][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z] != 0)
        return 1;
      else if (world[(int)MOB[mobID].mob_x-1][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z+1] != 0)
        return 1;
      else if (world[(int)MOB[mobID].mob_x-1][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z-1] != 0)
        return 1;
      break;
    case WEST: //LEFT
      if (world[(int)MOB[mobID].mob_x][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z-2] != 0)
        return 1;
      else if (world[(int)MOB[mobID].mob_x+1][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z-1] != 0)
        return 1;
      else if (world[(int)MOB[mobID].mob_x-1][(int)MOB[mobID].mob_y][(int)MOB[mobID].mob_z-1] != 0)
        return 1;
      break;
    default:
      printf("orientation error detected\n");
      exit(0);

  }

  return 0;

}

/*
  int canSeePlayer(int mobID)
  checks if MOB[mobID] can see the player (i.e. no obstacles to them)
*/
int canSeePlayer(int mobID) {

  float r;
  float distX, distY, distZ, distance;
  float unitVectorX, unitVectorY, unitVectorZ;
  int i, j, k;
  GLubyte checkedPosition;

  distX = MOB[mobID].mob_x - (camera_x*-1);
  distY = MOB[mobID].mob_y - (camera_y*-1);
  distZ = MOB[mobID].mob_z - (camera_z*-1);

  distance = sqrt(distX*distX + distY*distY + distZ*distZ);

  unitVectorX = distX/distance;
  unitVectorY = distY/distance;
  unitVectorZ = distZ/distance;
  printf("%d %lf, %lf, %lf\n", mobID, unitVectorX, unitVectorY, unitVectorZ);
  for (i = 0 ; i < roundf(distance); i++) {

    checkedPosition = getWorldAt((int)((camera_x*-1)+(i*unitVectorX)),
                                 (int)((camera_y*-1)+(i*unitVectorY)),
                                 (int)((camera_z*-1)+(i*unitVectorZ)));

    if (checkedPosition == 0) {
      //ignore
    } else if (checkedPosition == 5 || checkedPosition == 6) {
      return 0;
    }

  }

  return 1;

}

void shoot(int mobID) {

  float distX, distZ, distance;

  createMob(mobID, MOB[mobID].mob_x, MOB[mobID].mob_y, MOB[mobID].mob_z, 0);
  //calculate projectile vector
  distX = (camera_x*-1) - MOB[mobID].mob_x;
  distZ = (camera_z*-1) - MOB[mobID].mob_z;

  distance = sqrt(distX*distX + distZ*distZ);

  MOB[mobID].proj_x = MOB[mobID].mob_x;
  MOB[mobID].proj_z = MOB[mobID].mob_z;
  MOB[mobID].p_vect_x = distX/distance;
  MOB[mobID].p_vect_z = distZ/distance;

  MOB[mobID].shoot_state = 1;


}
