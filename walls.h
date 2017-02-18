typedef struct PULSAR_WALL {

   int STARTX, STARTZ;
   int ENDX, ENDZ;
   int orientation; //0 = horizontal, 1 = vertical
   int enabled; //0 = false, 1 = true

}Walls;

void drawWall(Walls w);
void removeWall(Walls w);
void animateWall(int n);
void selectWall();
