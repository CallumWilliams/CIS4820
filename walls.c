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
int wallToggle = 0; //toggle variable; 0 = add wall, 1 = remove wall

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

void animateWall(int n) {

  int i;
  int animX, animZ;

  if (n <= 14) {

    if (wallType == 0) {
      animX = H_Walls[wallVar1][wallVar2].STARTX + n;
      animZ = H_Walls[wallVar1][wallVar2].STARTZ;
    } else {
      animX = V_Walls[wallVar2][wallVar1].STARTX;
      animZ = V_Walls[wallVar2][wallVar1].STARTZ + n;
    }
    if (wallToggle == 0)
      printf("adding %d %d\n", animX, animZ);
    else
      printf("removing %d %d\n", animX, animZ);

    if (world[animX][25][animZ] != 6) { //if it's not a pillar

      for (i = 25; i < 30; i++) {

        if (wallToggle == 0) {
          world[animX][i][animZ] = 5;
        } else {
          world[animX][i][animZ] = 0;
        }

      }

    }

    glutTimerFunc(200, animateWall, n+1);

  }

}

void selectWall() {

  srand(time(NULL));

  do {

    wallVar1 = rand() % 6;
    wallVar2 = rand() % 5;
    wallType = rand() % 2;

    if (wallType == 0) changedWall = H_Walls[wallVar1][wallVar2];
    else changedWall = V_Walls[wallVar2][wallVar1];

  } while (changedWall.enabled != wallToggle);

  if (wallType == 0) {
    printf("changing hwall position from %d %d to %d %d\n", changedWall.STARTX, changedWall.STARTZ, changedWall.ENDX, changedWall.ENDZ);
  } else {
    printf("changing vwall position from %d %d to %d %d\n", changedWall.STARTX, changedWall.STARTZ, changedWall.ENDX, changedWall.ENDZ);
  }
  glutTimerFunc(200, animateWall, 0);

  if (wallToggle == 1) {
    if (wallType == 0) H_Walls[wallVar1][wallVar2].enabled = 0;
    else V_Walls[wallVar2][wallVar1].enabled = 0;
    wallToggle = 0;
  } else {
    if (wallType == 0) H_Walls[wallVar1][wallVar2].enabled = 1;
    else V_Walls[wallVar2][wallVar1].enabled = 1;
    wallToggle = 1;
  }

  glutTimerFunc(7500, selectWall, 5);
}
