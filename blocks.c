#include <stdlib.h>
#include "blocks.h"

Entity create_GrassBlock(int x, int y) {
    Entity grass_block = {.x = x, .y = y, .width = 1, .height = 1};
    grass_block.cells = malloc(sizeof(Cell));
    Cell cell = {.x = 0,
                 .y = 0,
                 .z = 0,
                 .character = '.',
                 .light_level = 0,
                 .foreground = COLOR_GREEN,
                 .background = COLOR_GREEN};
    grass_block.cells[0] = cell;
    grass_block.number_of_cells = 1;
    return grass_block;
} 
