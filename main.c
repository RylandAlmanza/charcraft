#include "colorutils.h"
#include "directions.h"
#include "display.h"
#include "world.h"
#include "blocks.h"
#include "entity.h"

void draw(Display *display, World *world, bool is_day) {
    int x;
    int y;
    int z;
    for (z = 0; z < 5; z++) {
        for (y = 0; y < world->height; y++) {
            for (x = 0; x < world->width; x++) {
                if (world->map[z][y][x].character == ' ') continue;
                Cell cell;
                cell.x = x;
                cell.y = y;
                cell.z = z;
                cell.character = world->map[z][y][x].character;
                if (is_day || world->light_map[y][x]) {
                    cell.foreground = world->map[z][y][x].foreground;
                    cell.background = world->map[z][y][x].background;
                } else {
                    cell.foreground = world->map[z][y][x].background;
                    cell.background = BLACK;
                }
                display->add_cell_to_queue(display, cell);
            }
        }
    }

    int i;
    for (i = 0; i < world->number_of_entities; i++) {
        Entity *entity = &world->entities[i];
        Cell cell;
        cell.x = entity->x;
        cell.y = entity->y;
        cell.z = entity->z;
        if (world->light_map[entity->y][entity->x]) {
            cell.character = entity->character;
            cell.foreground = entity->foreground;
            if (entity->background == TRANSPARENT) {
                cell.background = world->map[entity->z - 1][entity->y][entity->x].background;
            } else {
                cell.background = entity->background;
            }
        } else {
            cell.character = '?';
            cell.foreground = WHITE;
            cell.background = BLACK;
        }
        display->add_cell_to_queue(display, cell);
    }

    display->draw(display);
    display->reset_queue(display);
}

Point get_delta_from_key(int key) {
    Point delta = {.x = 0, .y = 0};
    if (key == KEY_UP) {
        delta = NORTH_DELTA;
    }
    if (key == KEY_RIGHT) {
        delta = EAST_DELTA;
    }
    if (key == KEY_DOWN) {
        delta = SOUTH_DELTA;
    }
    if (key == KEY_LEFT) {
        delta = WEST_DELTA;
    }
    return delta;
}

int main() {
    Display display = construct_Display();
    World world = construct_World(80, 24);

    bool is_day = true;
    int time = 0;
    
    // The player's is the first entity to be added, so it's id is 0
    int player_id = 0;
    Entity guy = create_Guy(5, 5, 1);
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
    
    Entity tree = create_Tree(4, 4, 1);
    Entity tree2 = create_Tree(15, 4, 1);
    world.add_entity(&world, tree);
    world.add_entity(&world, tree2);
    //sync_background(&tree, world);
    //display.add_entity_to_queue(&display, tree);

    //display.draw(&display);

    draw(&display, &world, is_day);

    int ch;
    while (ch != 'q') {
        display.reset_queue(&display);
        Entity *player = world.get_entity(&world, player_id);
        ch = getch();
        Point delta = get_delta_from_key(ch);
        if (delta.x != 0 || delta.y != 0) {
            world.move_entity(&world, player_id, delta.x, delta.y);
        }
        if (ch == 't') {
            world.add_entity(&world,
                             create_Torch(player->x, player->y, player->z));
        }
        if (ch == 'x') {
            ch = getch();
            delta = get_delta_from_key(ch);
            if (delta.x != 0 || delta.y != 0) {
                world.remove_block(&world,
                                   player->x + delta.x,
                                   player->y + delta.y,
                                   player->z);
            }
        }
        if (ch == 'z') {
            ch = getch();
            delta = get_delta_from_key(ch);
            if (delta.x != 0 || delta.y != 0) {
                world.add_block(&world,
                                create_WoodBlock(player->x + delta.x,
                                                 player->y + delta.y,
                                                 player->z));
            }
        }
        draw(&display, &world, is_day);
        time++;
        if (time == 1000) {
            time = 0;
            switch (is_day) {
                case true:
                    is_day = false;
                    break;
                case false:
                    is_day = true;
                    break;
            }
        }
    }

    destroy_Display(&display);
    destroy_World(&world);
    
    return 0;
}
