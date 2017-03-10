typedef enum {NORTH, SOUTH, EAST, WEST} ORIENTATION;

struct mob {

  int mobEnabled;
  float mob_x, mob_y, mob_z;
  ORIENTATION mob_rot;
  int COLOUR_STATE; //0 = yellow, 1 = green;

};

static int MOB_LIMIT = 10;
static float MOB_SPEED = 0.1;
static struct mob MOB[10];

void renderMob(int mobID, float mobX, float mobY, float mobZ, ORIENTATION o);
void swapColour(int mobID);
void eraseMob(int mobID);
ORIENTATION selectNewMobOrientation(int mobID);
void rotateMob(int mobID, ORIENTATION newO);
int hasCollision(int mobID);
