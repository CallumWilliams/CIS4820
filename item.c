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

void drawItem(int OBJ_ID) {
  
  switch (ITEM_ARRAY[OBJ_ID].ot) {
    case KEY:
      world[ITEM_ARRAY[OBJ_ID].pos_x][ITEM_ARRAY[OBJ_ID].pos_y][ITEM_ARRAY[OBJ_ID].pos_z] = 5;
      break;
    case TELEPORT:
      world[ITEM_ARRAY[OBJ_ID].pos_x][ITEM_ARRAY[OBJ_ID].pos_y][ITEM_ARRAY[OBJ_ID].pos_z] = 3;
      break;
    case BOUNCE:
      world[ITEM_ARRAY[OBJ_ID].pos_x][ITEM_ARRAY[OBJ_ID].pos_y][ITEM_ARRAY[OBJ_ID].pos_z] = 1;
      break;
    case FALL_CUBE:
      world[ITEM_ARRAY[OBJ_ID].pos_x][ITEM_ARRAY[OBJ_ID].pos_y][ITEM_ARRAY[OBJ_ID].pos_z] = 2;
      break;
    default:
      printf("Unexpected OBJECT_TYPE %d\n", ITEM_ARRAY[OBJ_ID].ot);
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

int playerObjectCollide(float p_x, float p_y, float p_z) {

  int i;
  for (i = 0; i < 7; i++) {
    if ((int)p_x*-1 == ITEM_ARRAY[i].pos_x &&
        (int)p_y*-1 == ITEM_ARRAY[i].pos_y &&
        (int)p_z*-1 == ITEM_ARRAY[i].pos_z &&
        ITEM_ARRAY[i].enabled) {
          removeObject(i);
          return (int)ITEM_ARRAY[i].ot;
        }
  }

  return -1;

}
