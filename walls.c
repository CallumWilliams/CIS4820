#include <stdlib.h>

#include "walls.h"
#include "graphics.h"

/* wall locations */
Walls V_Walls[5][6];
Walls H_Walls[6][5];

/* wall animation variables */
Walls changedWall;
int wallVar1, wallVar2; //position of animated wall
int wallType; //type; 0 = horizontal, 1 = vertical
int wallToggle = 0; //toggle variable; 0 = wall disabled, add wall, 1 = wall enabled, remove wall

void drawWall(Walls w) {

  int i, j;

  if (w.orientation == 0) {//horizontal

     for (i = w.STARTX; i <= w.ENDX; i++) {
        for (j = 25; j < 30; j++) {
          world[i][j][w.STARTZ] = 5;
        }
     }

  } else {//vertical

     for (i = w.STARTZ; i <= w.ENDZ; i++) {
        for (j = 25; j < 30; j++) {
          world[w.STARTX][j][i] = 5;
        }
     }

  }

}

void removeWall(Walls w) {

   int i, j;

   if (w.orientation == 0) {//horizontal

      for (i = w.STARTX+1; i < w.ENDX; i++) {
         for (j = 25; j < 30; j++) {
            world[i][j][w.STARTZ] = 0;
         }
      }

   } else {//vertical

      for (i = w.STARTZ+1; i < w.ENDZ; i++) {
         for (j = 25; j < 30; j++) {
            world[w.STARTX][j][i] = 0;
         }
      }

   }

}

void generateWalls() {

  int i, j;
  /* set vertical wall positions */
  for (i = 0; i < 5; i++) {
     for (j = 0; j < 6; j++) {
        V_Walls[i][j].STARTX = (i*15) + 15;
        V_Walls[i][j].STARTZ = (j*15) + 1;
        V_Walls[i][j].ENDX = V_Walls[i][j].STARTX;
        V_Walls[i][j].ENDZ = (j*15) + 14;
        V_Walls[i][j].orientation = 1;
        V_Walls[i][j].enabled = 0;
     }
  }

  /* set horizontal wall positions */
  for (i = 0; i < 6; i++) {
     for (j = 0; j < 5; j++) {
        H_Walls[i][j].STARTX = (i*15) + 1;
        H_Walls[i][j].STARTZ = (j*15) + 15;
        H_Walls[i][j].ENDX = (i*15) + 14;
        H_Walls[i][j].ENDZ = H_Walls[i][j].STARTZ;
        H_Walls[i][j].orientation = 0;
        H_Walls[i][j].enabled = 0;
     }
  }

  int wallChance; int wallCount = 0;
  srand(time(NULL));

  for (i = 0; i < 5; i++) {
     for (j = 0; j < 6; j++) {
        wallChance = rand() % 100 + 1;
        if (wallChance <= 30 && wallCount < 25) {
          drawWall(V_Walls[i][j]);
          V_Walls[i][j].enabled = 1;
          wallCount++;
        }
     }
  }

  for (i = 0; i < 6; i++) {
     for (j = 0; j < 6; j++) {
        wallChance = rand() % 100 + 1;
        if (wallChance <= 30 && wallCount < 20) {
          drawWall(H_Walls[i][j]);
          H_Walls[i][j].enabled = 1;
          wallCount++;
        }
     }
  }

}

void animateWall(int n) {

  int i;
  int animX, animZ;
  if (n < 15) {

    if (wallType == 0) {
      animX = H_Walls[wallVar1][wallVar2].STARTX + n;
      animZ = H_Walls[wallVar1][wallVar2].STARTZ;
    } else {
      animX = V_Walls[wallVar2][wallVar1].STARTX;
      animZ = V_Walls[wallVar2][wallVar1].STARTZ + n;
    }

    for (i = 25; i < 30; i++) {

      if (wallToggle == 0 && world[animX][i][animZ] == 0)
        world[animX][i][animZ] = 5;
      else if (wallToggle == 1 && world[animX][i][animZ] == 5)
        world[animX][i][animZ] = 0;

    }

  } else {
    if (wallToggle == 0) wallToggle = 1;
    else wallToggle = 0;
  }

}

void selectWall() {

  do {

    wallVar1 = rand() % 6;
    wallVar2 = rand() % 5;
    wallType = rand() % 2;

    if (wallType == 0) changedWall = H_Walls[wallVar1][wallVar2];
    else changedWall = V_Walls[wallVar2][wallVar1];

  } while (changedWall.enabled != wallToggle);

  if (wallToggle == 1) {
    if (wallType == 0) H_Walls[wallVar1][wallVar2].enabled = 0;
    else V_Walls[wallVar2][wallVar1].enabled = 0;
  } else {
    if (wallType == 0) H_Walls[wallVar1][wallVar2].enabled = 1;
    else V_Walls[wallVar2][wallVar1].enabled = 1;
  }

}
