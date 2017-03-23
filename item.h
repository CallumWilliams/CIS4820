typedef enum {KEY, TELEPORT, BOUNCE, FALL_CUBE} OBJECT_TYPE;

struct item {

  int enabled;
  int pos_x, pos_y, pos_z;
  OBJECT_TYPE ot;

};

struct item ITEM_ARRAY[7];

void initItems();
void generateObject(int OBJ_ID, OBJECT_TYPE t, int x, int y, int z);
void removeObject(int OBJ_ID);
int playerObjectCollide(float p_x, float p_y, float p_z);
