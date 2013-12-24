#include <stdlib.h>
#include "colorutils.h"
#include "blocks.h"

Entity create_GrassBlock(int x, int y) {
    Entity grass_block = {.x = x,
                          .y = y,
                          .z = 0,
                          .character = '.',
                          .brightness = 0,
                          .foreground = WHITE,
                          .background = GREEN};
    return grass_block;
}

Entity create_WaterBlock(int x, int y) {
    Entity water_block = {.x = x,
                          .y = y,
                          .z = 0,
                          .character = '~',
                          .brightness = 0,
                          .foreground = WHITE,
                          .background = BLUE};
    return water_block;
}
