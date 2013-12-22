#include <ncurses.h>

#include "display.h"
#include "world.h"
#include "entity.h"

Entity construct_clear_entity(int x, int y, int width, int height) {
    Entity clear_entity = {.x = x, .y = y, .width = width, .height = height};
    clear_entity.cells = malloc(sizeof(Cell) * (width * height));
    int i;
    int j;
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            Cell cell = {.x = i,
                         .y = j,
                         .z = 0,
                         .character = ' ',
                         .foreground = COLOR_BLACK,
                         .background = COLOR_BLACK
                        };
            clear_entity.cells[(j * width) + i] = cell;
        }
    }
    clear_entity.number_of_cells = width * height;
    return clear_entity;
}

int main() {
    Display display = construct_Display();
    World world = construct_World();
    
    // The player's is the first entity to be added, so it's id is 0
    int player_id = 0;
    Entity guy = create_Guy(5, 5);
    world.add_entity(&world, guy);
    display.add_entity_to_queue(&display, guy);
    
    Entity tree = create_Tree(2, 2);
    world.add_entity(&world, tree);
    display.add_entity_to_queue(&display, tree);

    display.draw(&display);

    int ch;
    while (ch != 'q') {
        display.reset_queue(&display);
        Entity *player = world.get_entity(&world, player_id);
        Entity clear_guy = construct_clear_entity(player->x,
                                                  player->y,
                                                  player->width,
                                                  player->height);
        display.add_entity_to_queue(&display, clear_guy);
        ch = getch();
        int x_delta = 0;
        int y_delta = 0;
        if (ch == KEY_UP) {
            y_delta = -1;
        }
        if (ch == KEY_RIGHT) {
            x_delta = 1;
        }
        if (ch == KEY_DOWN) {
            y_delta = 1;
        }
        if (ch == KEY_LEFT) {
            x_delta = -1;
        }
        world.move_entity(&world, player_id, x_delta, y_delta);
        display.add_entity_to_queue(&display, *player);
        display.draw(&display);
        destroy_Entity(&clear_guy);
    }

    destroy_Display(&display);
    destroy_World(&world);
    
    return 0;
}
