typedef enum {NORTH, SOUTH, EAST, WEST} ORIENTATION;

static int MOB_LIMIT = 10;
static int mobEnabled[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //0 = false, 1 = true
static float mob_x[10], mob_y[10], mob_z[10], mob_rot[10];

void renderMob(int mobID, float mobX, float mobY, float mobZ, ORIENTATION o);
void rotateMob(int mobID, ORIENTATION newO);
