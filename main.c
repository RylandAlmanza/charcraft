#include <ncurses.h>

#include "display.h"
#include "world.h"
#include "entity.h"

void sync_background(Entity *entity, World world) {
    if (!world.light_map[entity->y][entity->x]) {
        entity->background = COLOR_BLACK;
    } else {
        entity->background = world.map[entity->y][entity->x].original_background;
        //entity->background = COLOR_GREEN;
    }
}

void draw(Display *display, World world) {
    int i;
    for (i = 0; i < world.number_of_entities; i++) {
        sync_background(&world.entities[i], world);
        display->add_entity_to_queue(display, world.entities[i]);
    }

    int y;
    for (y = 0; y < world.height; y++) {
        int x;
        for (x = 0; x < world.width; x++) {
            sync_background(&world.map[y][x], world);
            display->add_entity_to_queue(display, world.map[y][x]);
        }
    }
    display->draw(display);
    display->reset_queue(display);
}

int main() {
    Display display = construct_Display();
    World world = construct_World(80, 24);
    
    // The player's is the first entity to be added, so it's id is 0
    int player_id = 0;
    Entity guy = create_Guy(5, 5);
    world.add_entity(&world, guy);
    //sync_background(&guy, world);
    //display.add_entity_to_queue(&display, guy);

    /*int y;
    for (y = 0; y < world.height; y++) {
        int x;
        for (x = 0; x < world.width; x++) {
            sync_background(&world.map[y][x], world);
            display.add_entity_to_queue(&display, world.map[y][x]);
        }
    }*/
    
    Entity tree = create_Tree(4, 4);
    world.add_entity(&world, tree);
    //sync_background(&tree, world);
    //display.add_entity_to_queue(&display, tree);

    //display.draw(&display);

    draw(&display, world);

    int ch;
    while (ch != 'q') {
        display.reset_queue(&display);
        Entity *player = world.get_entity(&world, player_id);

        //display.add_entity_to_queue(&display, world.map[player->y][player->x]);
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
        if (ch == 't') {
            world.add_entity(&world, create_Torch(player->x, player->y));
        }
        if (x_delta != 0 || y_delta != 0) {
            world.move_entity(&world, player_id, x_delta, y_delta);
        }
        //sync_background(player, world);
        //display.add_entity_to_queue(&display, *player);
        //display.draw(&display);
        //destroy_Entity(&clear_guy);
        draw(&display, world);
    }

    destroy_Display(&display);
    destroy_World(&world);
    
    return 0;
}
