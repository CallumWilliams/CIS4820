
/* Derived from scene.c in the The OpenGL Programming Guide */
/* Keyboard and mouse rotation taken from Swiftless Tutorials #23 Part 2 */
/* http://www.swiftless.com/tutorials/opengl/camera2.html */

/* Frames per second code taken from : */
/* http://www.lighthouse3d.com/opengl/glut/index.php?fps */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "graphics.h"

typedef struct PULSAR_WALL {

   int STARTX, STARTZ;
   int ENDX, ENDZ;
   int orientation; //0 = horizontal, 1 = vertical

}Walls;

	/* mouse function called by GLUT when a button is pressed or released */
void mouse(int, int, int, int);

	/* initialize graphics library */
extern void graphicsInit(int *, char **);

	/* lighting control */
extern void setLightPosition(GLfloat, GLfloat, GLfloat);
extern GLfloat* getLightPosition();

	/* viewpoint control */
extern void setViewPosition(float, float, float);
extern void getViewPosition(float *, float *, float *);
extern void getOldViewPosition(float *, float *, float *);
extern void setViewOrientation(float, float, float);
extern void getViewOrientation(float *, float *, float *);

	/* add cube to display list so it will be drawn */
extern int addDisplayList(int, int, int);

	/* mob controls */
extern void createMob(int, float, float, float, float);
extern void setMobPosition(int, float, float, float, float);
extern void hideMob(int);
extern void showMob(int);

	/* player controls */
extern void createPlayer(int, float, float, float, float);
extern void setPlayerPosition(int, float, float, float, float);
extern void hidePlayer(int);
extern void showPlayer(int);

	/* 2D drawing functions */
extern void  draw2Dline(int, int, int, int, int);
extern void  draw2Dbox(int, int, int, int);
extern void  draw2Dtriangle(int, int, int, int, int, int);
extern void  set2Dcolour(float []);


	/* flag which is set to 1 when flying behaviour is desired */
extern int flycontrol;
	/* flag used to indicate that the test world should be used */
extern int testWorld;
	/* flag to print out frames per second */
extern int fps;
	/* flag to indicate the space bar has been pressed */
extern int space;
	/* flag indicates the program is a client when set = 1 */
extern int netClient;
	/* flag indicates the program is a server when set = 1 */
extern int netServer;
	/* size of the window in pixels */
extern int screenWidth, screenHeight;
	/* flag indicates if map is to be printed */
extern int displayMap;

	/* frustum corner coordinates, used for visibility determination  */
extern float corners[4][3];

	/* determine which cubes are visible e.g. in view frustum */
extern void ExtractFrustum();
extern void tree(float, float, float, float, float, float, int);

/********* end of extern variable declarations **************/


	/*** collisionResponse() ***/
	/* -performs collision detection and response */
	/*  sets new xyz  to position of the viewpoint after collision */
	/* -can also be used to implement gravity by updating y position of vp*/
	/* note that the world coordinates returned from getViewPosition()
	   will be the negative value of the array indices */
void collisionResponse() {

	/* your collision code goes here */


}


	/******* draw2D() *******/
	/* draws 2D shapes on screen */
	/* use the following functions: 			*/
	/*	draw2Dline(int, int, int, int, int);		*/
	/*	draw2Dbox(int, int, int, int);			*/
	/*	draw2Dtriangle(int, int, int, int, int, int);	*/
	/*	set2Dcolour(float []); 				*/
	/* colour must be set before other functions are called	*/
void draw2D() {

   if (testWorld) {
		/* draw some sample 2d shapes */
      GLfloat green[] = {0.0, 0.5, 0.0, 0.5};
      set2Dcolour(green);
      draw2Dline(0, 0, 500, 500, 15);
      draw2Dtriangle(0, 0, 200, 200, 0, 200);

      GLfloat black[] = {0.0, 0.0, 0.0, 0.5};
      set2Dcolour(black);
      draw2Dbox(500, 380, 524, 388);
   } else {

	/* your code goes here */

   }

}


	/*** update() ***/
	/* background process, it is called when there are no other events */
	/* -used to control animations and perform calculations while the  */
	/*  system is running */
	/* -gravity must also implemented here, duplicate collisionResponse */
void update() {
int i, j, k;
float *la;

    static float mobSpeed = 0.1; //variable for mob speed

	/* sample animation for the test world, don't remove this code */
	/* -demo of animating mobs */
   if (testWorld) {

	/* sample of rotation and positioning of mob */
	/* coordinates for mob 0 */
      static float mob0x = 50.0, mob0y = 25.0, mob0z = 52.0;
      static float mob0ry = 0.0;
      static int increasingmob0 = 1;
	/* coordinates for mob 1 */
      static float mob1x = 50.0, mob1y = 25.0, mob1z = 52.0;
      static float mob1ry = 0.0;
      static int increasingmob1 = 1;

	/* move mob 0 and rotate */
	/* set mob 0 position */
      setMobPosition(0, mob0x, mob0y, mob0z, mob0ry);

	/* move mob 0 in the x axis */
      if (increasingmob0 == 1)
         mob0x += 0.2;
      else
         mob0x -= 0.2;
      if (mob0x > 50) increasingmob0 = 0;
      if (mob0x < 30) increasingmob0 = 1;

	/* rotate mob 0 around the y axis */
      mob0ry += 1.0;
      if (mob0ry > 360.0) mob0ry -= 360.0;

	/* move mob 1 and rotate */
      setMobPosition(1, mob1x, mob1y, mob1z, mob1ry);

	/* move mob 1 in the z axis */
	/* when mob is moving away it is visible, when moving back it */
	/* is hidden */
      if (increasingmob1 == 1) {
         mob1z += 0.2;
         showMob(1);
      } else {
         mob1z -= 0.2;
         hideMob(1);
      }
      if (mob1z > 72) increasingmob1 = 0;
      if (mob1z < 52) increasingmob1 = 1;

	   /* rotate mob 1 around the y axis */
      mob1ry += 1.0;
      if (mob1ry > 360.0) mob1ry -= 360.0;
     /* end testworld animation */

     } else {

     /* Assignment Update Code */

     /* player info */
     static float player_x = 7, player_y = 25, player_z = 7;
     static float player_rot = 0;
     setPlayerPosition(0, player_x, player_y, player_z, player_rot);

  	 /* camera positioning */


	   /* Mob 0 */
     static float mob0_x = 25, mob0_y = 25, mob0_z = 25;
     static float mob0_rot = -90;

     setMobPosition(0, mob0_x, mob0_y, mob0_z, mob0_rot);

     /* Mob 1 */
     static float mob1_x = 25, mob1_y = 27, mob1_z = 35;
     static float mob1_rot = 0;

     setMobPosition(1, mob1_x, mob1_y, mob1_z, mob1_rot);

    }
}


	/* called by GLUT when a mouse button is pressed or released */
	/* -button indicates which button was pressed or released */
	/* -state indicates a button down or button up event */
	/* -x,y are the screen coordinates when the mouse is pressed or */
	/*  released */
void mouse(int button, int state, int x, int y) {

   if (button == GLUT_LEFT_BUTTON)
      printf("left button - ");
   else if (button == GLUT_MIDDLE_BUTTON)
      printf("middle button - ");
   else
      printf("right button - ");

   if (state == GLUT_UP)
      printf("up - ");
   else
      printf("down - ");

   printf("%d %d\n", x, y);
}

void drawWall(Walls w) {

   int i, j;

   if (w.orientation == 0) {//horizontal

      for (i = w.STARTX+1; i < w.ENDX; i++) {
         for (j = 25; j < 30; j++) {
            world[i][j][w.STARTZ] = 2;
         }
      }

   } else {//vertical

      for (i = w.STARTZ+1; i < w.ENDZ; i++) {
         for (j = 25; j < 30; j++) {
            world[w.STARTX][j][i] = 2;
         }
      }

   }

}

int main(int argc, char** argv)
{
int i, j, k;
	/* initialize the graphics system */
   graphicsInit(&argc, argv);

	/* the first part of this if statement builds a sample */
	/* world which will be used for testing */
	/* DO NOT remove this code. */
	/* Put your code in the else statment below */
	/* The testworld is only guaranteed to work with a world of
		with dimensions of 100,50,100. */
   if (testWorld == 1) {
	/* initialize world to empty */
      for(i=0; i<WORLDX; i++)
         for(j=0; j<WORLDY; j++)
            for(k=0; k<WORLDZ; k++)
               world[i][j][k] = 0;

	/* some sample objects */
	/* build a red platform */
      for(i=0; i<WORLDX; i++) {
         for(j=0; j<WORLDZ; j++) {
            world[i][24][j] = 3;
         }
      }

	/* create some green and blue cubes */
      world[50][25][50] = 1;
      world[49][25][50] = 1;
      world[49][26][50] = 1;
      world[52][25][52] = 2;
      world[52][26][52] = 2;

	/* blue box shows xy bounds of the world */
      for(i=0; i<WORLDX-1; i++) {
         world[i][25][0] = 2;
         world[i][25][WORLDZ-1] = 2;
      }
      for(i=0; i<WORLDZ-1; i++) {
         world[0][25][i] = 2;
         world[WORLDX-1][25][i] = 2;
      }

	/* create two sample mobs */
	/* these are animated in the update() function */
      createMob(0, 50.0, 25.0, 52.0, 0.0);
      createMob(1, 50.0, 25.0, 52.0, 0.0);

	/* create sample player */
      createPlayer(0, 52.0, 27.0, 52.0, 0.0);

   } else {

      /* Assignment Code */

      /* build ground (same as -testworld) */
      for (i = 0; i < WORLDX; i++) {
         for (j = 0; j < WORLDZ; j++) {
            world[i][24][j] = 3;
         }
      }

      /* boundary box */
      for (i = 0; i < WORLDX-1; i++) {
         for (j = 25; j < 30; j++) {
            world[i][j][0] = 2;
            world[i][j][WORLDZ-1] = 2;
         }
      }
      for (i = 0; i < WORLDZ; i++) {
         for (j = 25; j < 30; j++) {
            world[0][j][i] = 2;
            world[WORLDX-1][j][i] = 2;
         }
      }

      /* build purple pillars */
      for (i = 1; i <= 6; i++) {
         for (j = 1; j < 6; j++) {
            for (k = 25; k < 30; k++) {
               world[i*15][k][j*15] = 6;
            }
         }
      }

      Walls V_Walls[6][6];
      Walls H_Walls[6][6];

      /* set vertical wall positions */
      for (i = 0; i < 6; i++) {
         for (j = 0; j < 6; j++) {
            V_Walls[i][j].STARTX = (i*15) + 15;
            V_Walls[i][j].STARTZ = j*15;
            V_Walls[i][j].ENDX = V_Walls[i][j].STARTX;
            V_Walls[i][j].ENDZ = (j*15) + 15;
            V_Walls[i][j].orientation = 1;
         }
      }

      /* set horizontal wall positions */
      for (i = 0; i < 6; i++) {
         for (j = 0; j < 5; j++) {
            H_Walls[i][j].STARTX = i*15;
            H_Walls[i][j].STARTZ = (j*15) + 15;
            H_Walls[i][j].ENDX = (i*15) + 15;
            H_Walls[i][j].ENDZ = H_Walls[i][j].STARTZ;
            H_Walls[i][j].orientation = 0;
         }
      }

      int wallChance;

      for (i = 0; i < 6; i++) {
         for (j = 0; j < 6; j++) {
            wallChance = rand() % 100 + 1;
            if (wallChance <= 35) drawWall(V_Walls[i][j]);
         }
      }

      for (i = 0; i < 6; i++) {
         for (j = 0; j < 5; j++) {
            wallChance = rand() % 100 + 1;
            if (wallChance <= 35) drawWall(H_Walls[i][j]);
         }
      }

      setViewPosition(-7, -26, -7);
      setViewOrientation(180, -150, 0);

      /* place player/entities */
      createPlayer(0, 7, 25, 7, 0);
      createMob(0, 25, 25, 25, -90);
      createMob(1, 25, 27, 35, 0);
      createMob(2, 80, 27, 35, 0);

   }


	/* starts the graphics processing loop */
	/* code after this will not run until the program exits */
   glutMainLoop();
   return 0;
}
