#include <stdlib.h>
#include <ncurses.h>
#include "entity.h"

Entity create_Tree(int x, int y) {
    Entity tree = {.x = x,
                   .y = y,
                   .z = 1,
                   .character = 'T',
                   .brightness = 0,
                   .foreground = COLOR_WHITE,
                   .background = COLOR_GREEN,
                   .original_foreground = COLOR_WHITE,
                   .original_background = COLOR_BLACK};

    return tree;
}


Entity create_Guy(int x, int y) {
    Entity guy = {.x = x,
                  .y = y,
                  .z = 1,
                  .character = '@',
                  .brightness = 2,
                  .foreground = COLOR_WHITE,
                  .background = COLOR_BLACK,
                  .original_foreground = COLOR_WHITE,
                  .original_background = COLOR_BLACK};
    return guy;
}

Entity create_Torch(int x, int y) {
    Entity torch = {.x = x,
                    .y = y,
                    .z = 1,
                    .character = 'i',
                    .brightness = 5,
                    .foreground = COLOR_YELLOW,
                    .background = COLOR_BLACK,
                    .original_foreground = COLOR_YELLOW,
                    .original_background = COLOR_BLACK};
    return torch;
}
