typedef enum {NORTH, SOUTH, EAST, WEST} ORIENTATION;

struct mob {

  int mobEnabled;
  float mob_x, mob_y, mob_z;
  float old_mob_x, old_mob_y, old_mob_z;
  ORIENTATION mob_rot;
  int COLOUR_STATE; //0 = yellow, 1 = green;

};

static int MOB_LIMIT = 9; //projectile[9] is reserved for player, [0-8] for mobs
static float MOB_SPEED = 0.065;
static struct mob MOB[9];

void renderMob(int mobID, float mobX, float mobY, float mobZ, ORIENTATION o);
void swapColour(int mobID);
void eraseMob(int mobID);
ORIENTATION selectNewMobOrientation(int mobID);
void rotateMob(int mobID, ORIENTATION newO);
int hasCollision(int mobID);
int canSeePlayer(int mobID);
