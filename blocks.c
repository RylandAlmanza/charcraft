#include <stdlib.h>
#include <ncurses.h>
#include "blocks.h"

Entity create_GrassBlock(int x, int y) {
    Entity grass_block = {.x = x,
                          .y = y,
                          .z = 0,
                          .character = '.',
                          .brightness = 0,
                          .foreground = COLOR_GREEN,
                          .background = COLOR_GREEN,
                          .original_foreground = COLOR_GREEN,
                          .original_background = COLOR_GREEN};
    return grass_block;
} 
