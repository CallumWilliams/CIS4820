typedef struct PULSAR_WALL {

   int STARTX, STARTZ;
   int ENDX, ENDZ;
   int orientation; //0 = horizontal, 1 = vertical
   int enabled; //0 = false, 1 = true

}Walls;

/* wall locations */
Walls V_Walls[5][6];
Walls H_Walls[6][5];

/* wall animation variables */
Walls changedWall;
int wallVar1, wallVar2; //position of animated wall
int wallType; //type; 0 = horizontal, 1 = vertical

void drawWall(Walls w);
void removeWall(Walls w);
void animateWall(int n);
void selectWall();
