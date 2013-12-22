#ifndef CELL_H_
#define CELL_H_

typedef struct CellS Cell;

struct CellS {
  int x;
  int y;
  int z;
  char character;
  int foreground;
  int background;
};

#endif
