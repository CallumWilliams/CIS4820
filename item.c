#include <stdlib.h>
#include <math.h>

#include "item.h"
#include "graphics.h"

void initItems() {
  int i;
  for (i = 0; i < 7; i++) {
    ITEM_ARRAY[i].enabled = 0;
  }
}

void generateObject(int OBJ_ID, OBJECT_TYPE t, int x, int y, int z) {

  ITEM_ARRAY[OBJ_ID].pos_x = x;
  ITEM_ARRAY[OBJ_ID].pos_y = y;
  ITEM_ARRAY[OBJ_ID].pos_z = z;
  ITEM_ARRAY[OBJ_ID].ot = t;
  ITEM_ARRAY[OBJ_ID].enabled = 1;

  switch (t) {
    case KEY:
      world[x][y][z] = 5;
      break;
    case TELEPORT:
      world[x][y][z] = 3;
      break;
    case BOUNCE:
      world[x][y][z] = 1;
      break;
    case FALL_CUBE:
      world[x][y][z] = 2;
      break;
    default:
      printf("Unexpected OBJECT_TYPE %d\n", t);
      exit(0);
  }

}

void removeObject(int OBJ_ID) {

  int x, y, z;

  x = ITEM_ARRAY[OBJ_ID].pos_x;
  y = ITEM_ARRAY[OBJ_ID].pos_y;
  z = ITEM_ARRAY[OBJ_ID].pos_z;
  ITEM_ARRAY[OBJ_ID].enabled = 0;

  world[x][y][z] = 0;

}
