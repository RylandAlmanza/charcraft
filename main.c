#include "colorutils.h"
#include "display.h"
#include "world.h"
#include "entity.h"

int gdbi;
int gdbx;
int gdby;

void draw(Display *display, World *world) {
    int x;
    int y;
    for (y = 0; y < world->height; y++) {
        for (x = 0; x < world->width; x++) {
            Cell cell;
            cell.x = x;
            cell.y = y;
            cell.z = world->map[y][x].z;
            cell.character = world->map[y][x].character;
            if (world->light_map[y][x]) {
                cell.foreground = world->map[y][x].foreground;
                cell.background = world->map[y][x].background;
            } else {
                cell.foreground = world->map[y][x].background;
                cell.background = BLACK;
            }
            display->add_cell_to_queue(display, cell);
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
                cell.background = world->map[entity->y][entity->x].background;
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
    Entity tree2 = create_Tree(15, 4);
    world.add_entity(&world, tree);
    world.add_entity(&world, tree2);
    //sync_background(&tree, world);
    //display.add_entity_to_queue(&display, tree);

    //display.draw(&display);

    draw(&display, &world);

    int ch;
    while (ch != 'q') {
        display.reset_queue(&display);
        Entity *player = world.get_entity(&world, player_id);

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
        draw(&display, &world);
    }

    destroy_Display(&display);
    destroy_World(&world);
    
    return 0;
}
