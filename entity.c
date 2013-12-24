#include <stdlib.h>
#include "colorutils.h"
#include "entity.h"

Entity create_Tree(int x, int y, int z) {
    Entity tree = {.x = x,
                   .y = y,
                   .z = z,
                   .character = 'T',
                   .is_solid = true,
                   .brightness = 0,
                   .foreground = WHITE,
                   .background = GREEN};
    return tree;
}


Entity create_Guy(int x, int y, int z) {
    Entity guy = {.x = x,
                  .y = y,
                  .z = z,
                  .character = '@',
                  .is_solid = true,
                  .brightness = 2,
                  .foreground = WHITE,
                  .background = TRANSPARENT};
    return guy;
}

Entity create_Torch(int x, int y, int z) {
    Entity torch = {.x = x,
                    .y = y,
                    .z = z,
                    .character = 'i',
                    .is_solid = false,
                    .brightness = 5,
                    .foreground = YELLOW,
                    .background = TRANSPARENT};
    return torch;
}
