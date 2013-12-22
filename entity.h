#ifndef ENTITY_H_
#define ENTITY_H_

#include <ncurses.h>

#include "colorutils.h"
#include "cell.h"

typedef struct EntityS Entity;

struct EntityS {
  int x;
  int y;
  int width;
  int height;
  Cell *cells;
  int number_of_cells;
};

Entity load_Entity(char *filename);
void destroy_Entity(Entity *entity);

Entity create_Tree(int x, int y);
Entity create_Guy(int x, int y);
#endif
