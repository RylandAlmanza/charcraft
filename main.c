#include <ncurses.h>

#include "display.h"
#include "world.h"
#include "entity.h"

/*Entity construct_clear_entity(int x, int y, int width, int height) {
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
}*/

void draw(Display *display, World world) {
    int i;
    for (i = 0; i < world.number_of_entities; i++) {
        display->add_entity_to_queue(display, world.entities[i]);
    }

    /*int y;
    for (y = 0; y < world.height; y++) {
        int x;
        for (x = 0; x < world.width; x++) {
            display->add_entity_to_queue(display, world.map[y][x]);
        }
    }*/
    display->draw(display);
    display->reset_queue(display);
}

void sync_background(Entity *entity, World world) {
    int i;
    for (i = 0; i < entity->number_of_cells; i++) {
        int world_x = entity->x + entity->cells[i].x;
        int world_y = entity->y + entity->cells[i].y;
        Cell tile_cell = world.map[world_y][world_x].cells[0];
        entity->cells[i].background = tile_cell.background;
    }
}

int main() {
    Display display = construct_Display();
    World world = construct_World(80, 24);
    
    // The player's is the first entity to be added, so it's id is 0
    int player_id = 0;
    Entity guy = create_Guy(5, 5);
    world.add_entity(&world, guy);
    sync_background(&guy, world);
    display.add_entity_to_queue(&display, guy);

    int y;
    for (y = 0; y < world.height; y++) {
        int x;
        for (x = 0; x < world.width; x++) {
            display.add_entity_to_queue(&display, world.map[y][x]);
        }
    }
    
    Entity tree = create_Tree(2, 2);
    world.add_entity(&world, tree);
    sync_background(&tree, world);
    display.add_entity_to_queue(&display, tree);

    display.draw(&display);

    int ch;
    while (ch != 'q') {
        display.reset_queue(&display);
        Entity *player = world.get_entity(&world, player_id);

        display.add_entity_to_queue(&display, world.map[player->y][player->x]);
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
        sync_background(player, world);
        display.add_entity_to_queue(&display, *player);
        display.draw(&display);
        //destroy_Entity(&clear_guy);
        //draw(&display, world);
    }

    destroy_Display(&display);
    destroy_World(&world);
    
    return 0;
}
