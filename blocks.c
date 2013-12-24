#include <stdlib.h>
#include "colorutils.h"
#include "blocks.h"

Entity create_AirBlock(int x, int y, int z) {
    Entity air_block = {.x = x,
                        .y = y,
                        .z = z,
                        .character = ' ',
                        .brightness = 0,
                        .is_solid = false,
                        .foreground = BLACK,
                        .background = BLACK};
    return air_block;
} 
Entity create_GrassBlock(int x, int y, int z) {
    Entity grass_block = {.x = x,
                          .y = y,
                          .z = z,
                          .character = '.',
                          .is_solid = true,
                          .brightness = 0,
                          .foreground = WHITE,
                          .background = GREEN};
    return grass_block;
}

Entity create_WaterBlock(int x, int y, int z) {
    Entity water_block = {.x = x,
                          .y = y,
                          .z = z,
                          .character = '~',
                          .is_solid = true,
                          .brightness = 0,
                          .foreground = WHITE,
                          .background = BLUE};
    return water_block;
}

Entity create_WoodBlock(int x, int y, int z) {
    Entity wood_block = {.x = x,
                         .y = y,
                         .z = z,
                         .character = '#',
                         .is_solid = true,
                         .brightness = 0,
                         .foreground = WHITE,
                         .background = YELLOW};
    return wood_block;
}
