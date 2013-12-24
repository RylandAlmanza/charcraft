#include <stdlib.h>
#include "colorutils.h"
#include "entity.h"

Entity create_Tree(int x, int y) {
    Entity tree = {.x = x,
                   .y = y,
                   .z = 1,
                   .character = 'T',
                   .brightness = 0,
                   .foreground = WHITE,
                   .background = GREEN};
    return tree;
}


Entity create_Guy(int x, int y) {
    Entity guy = {.x = x,
                  .y = y,
                  .z = 1,
                  .character = '@',
                  .brightness = 2,
                  .foreground = WHITE,
                  .background = TRANSPARENT};
    return guy;
}

Entity create_Torch(int x, int y) {
    Entity torch = {.x = x,
                    .y = y,
                    .z = 1,
                    .character = 'i',
                    .brightness = 5,
                    .foreground = YELLOW,
                    .background = TRANSPARENT};
    return torch;
}
