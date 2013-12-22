#include <stdio.h>
#include "entity.h"

// Load an entity from a file
Entity load_Entity(char *filename) {
    FILE *entity_file = fopen(filename, "r");
    
    if (entity_file != NULL) {
        printf("Couldn't open up the file, dude.");
    }

    Entity entity;

    fscanf(entity_file,
           "%i %i %i",
           &entity.width,
           &entity.height,
           &entity.number_of_cells);
    entity.cells = malloc(sizeof(Cell) * entity.number_of_cells);

    int i;
    for (i = 0; i < entity.number_of_cells; i++) {
        Cell cell;
        fscanf(entity_file,
               "%i %i %i %c %i %i",
               &cell.x,
               &cell.y,
               &cell.z,
               &cell.character,
               &cell.foreground,
               &cell.background);
        entity.cells[i] = cell;
    }

    fclose(entity_file);

    return entity;        
}

void destroy_Entity(Entity *entity) {
    free(entity->cells);
}

Entity create_Tree(int x, int y) {
    Entity tree = {.x = x, .y = y, .width = 1, .height = 1};

    tree.cells = malloc(sizeof(Cell));
    Cell cell0 = {.x = 0,
                  .y = 0,
                  .z = 1,
                  .character = 'T',
                  .foreground = COLOR_WHITE,
                  .background = -1};
    tree.cells[0] = cell0;
    tree.number_of_cells = 1;
    return tree;
}


Entity create_Guy(int x, int y) {
    Entity guy = {.x = x, .y = y, .width = 1, .height = 1};
    guy.cells = malloc(sizeof(Cell));
    Cell cell0 = {.x = 0,
                  .y = 0,
                  .z = 1,
                  .character = '@',
                  .foreground = COLOR_WHITE,
                  .background = -1};
    guy.cells[0] = cell0;
    guy.number_of_cells = 1;
    return guy;
}

