#ifndef ENTITY_H_
#define ENTITY_H_

typedef struct EntityS Entity;

struct EntityS {
  int x;
  int y;
  int z;
  char character;
  bool is_solid;
  int brightness;
  int original_foreground;
  int original_background;
  int foreground;
  int background;
};

Entity create_Tree(int x, int y, int z);
Entity create_Guy(int x, int y, int z);
Entity create_Torch(int x, int y, int z);
#endif
