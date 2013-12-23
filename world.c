#include <stdlib.h>

#include "world.h"
#include "blocks.h"

int get_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Adds an entity to the world
void World_add_entity(World *self, Entity entity) {
    // Add the entity
    self->entities[self->number_of_entities] = entity;

    // We added an entity, so let's add one to the number_of_entities variable
    self->number_of_entities = self->number_of_entities + 1;
    // And let's add some space to the entity array for next time we add an
    // entity
    self->entities = realloc(self->entities,
                             sizeof(Entity) * (self->number_of_entities + 1));

    int i;
    for (i = 0; i < entity.number_of_cells; i++) {
        if (entity.cells[i].light_level > 0) {
            self->lights[self->number_of_lights] = &entity.cells[i];
            self->number_of_lights = self->number_of_lights + 1;
            self->lights = realloc(self->lights,
                                   sizeof(Cell *) * (self->number_of_lights + 1));
            self->update_light_map(self);
        }
    }
}

void World_reset_light_map(World *self) {
    int y;
    for (y = 0; y < world.height; y++) {
        int x;
        for (x = 0; x < world.width; x++) {
            world.light_map[y][x] = false;
        }
    }
}

void World_update_light_map(World *self) {
    self->reset_light_map(self);

    int i;
    for (i = 0; i < number_of_lights; i++) {
        Cell world_cell = self->lights[i];
        world_cell.x = entity.x + cell.x;
        world_cell.y = entity.y + cell.y;
        int y;
        for (y = world_cell.y - world_cell.light_level;
             y < world_cell.y + world_cell.light_level + 1;
             y++) {
             int y_distance = get_distance(0, y, 0, world_cell.y);
             int number_of_columns = (light_level * 2) -
                                     (y_distance * 2) +
                                     1;
             int start_x = world_cell.x - ((number_of_columns - 1) / 2);
             int x;
             for (x = start_x; x < start_x + number_of_columns; x++) {
                 self->light_map[y][x] = true;
             }
        }
    }
}

// Get's an entity by it's id
Entity *World_get_entity(World *self, int id) {
    return &self->entities[id];
}

// Checks if an entity can move to a certain position without any collision. If
// it can, it will change the entity's position and return true. Otherwise, it
// will return false
bool World_move_entity(World *self, int id, int x_delta, int y_delta) {
    // Retrieve a reference to the entity by the id (which is just the
    // entities index in the world's list of entities
    Entity *entity = &self->entities[id];
    // We'll store the x and y positions that the entity is trying to move to
    // in the variables, proposed_x and proposed_y
    int proposed_x = entity->x + x_delta;
    int proposed_y = entity->y + y_delta;
    
    // Now we loop through all the world's entities and check if any of their
    // cells would collide with our selected entities cells if it were to be
    // moved to the proposed position
    int i;
    for (i = 0; i < self->number_of_entities; i++) {
        // We don't want to compare our selected entity with itself, so skip
        // the rest of this block if i matches the id
        if (i == id) continue;
        // Get a reference to the entity we're checking collision with
        Entity *entity_b = &self->entities[i];
        int a_i;
        int b_i;
        // Loop through each of the first entity's cells
        for (a_i = 0; a_i < entity->number_of_cells; a_i++) {
            // Get the cell at the index, a_i
            Cell cell_a = entity->cells[a_i];
            //Loop through each of entity b's cells
            for (b_i = 0; b_i < entity_b->number_of_cells; b_i++) {
                // Get the cell at the index, a_b
                Cell cell_b = entity_b->cells[b_i];
                // Check if the cells are in the same position
                if (cell_a.x + proposed_x == cell_b.x + entity_b->x &&
                    cell_a.y + proposed_y == cell_b.y + entity_b->y &&
                    cell_a.z == cell_b.z) {
                    // If they are, then we return false and don't move the
                    // entity
                    return false;
                }
            }
        }
    }
    // If we got this far, there will be no collisions, so let's go ahead and
    // move the entity!
    entity->x = proposed_x;
    entity->y = proposed_y;
    // And let whoever's calling the function know that it worked
    return true;
}

// Constructs a world object
World construct_World(int width, int height) {
    World world;
    world.width = width;
    world.height = height;
    world.number_of_entities = 0;
    world.entities = malloc(sizeof(Entity));
    world.number_of_lights = 0;
    world.lights = malloc(sizeof(Cell *));
    world.map = malloc(sizeof(Entity) * (world.width * world.height));
    world.light_map = malloc(sizeof(bool) * (world.width * world.height));
    int y;
    for (y = 0; y < world.height; y++) {
        world.map[y] = malloc(sizeof(Entity) * world.width);
        world.light_map[y] = malloc(sizeof(bool) * world.width);
        int x;
        for (x = 0; x < world.width; x++) {
            world.map[y][x] = create_GrassBlock(x, y);
            world.light_map[y][x] = false;
        }
    }
    world.add_entity = &World_add_entity;
    world.get_entity = &World_get_entity;
    world.move_entity = &World_move_entity;
    world.reset_light_map = &World_reset_light_map;
    world.update_light_map = &World_update_light_map;
    return world;
}

// Probably the best name for a function. Destroys the world.
void destroy_World(World *world) {
    int i;
    // Loop through all the entities and make sure they're properly destroyed
    for (i = 0; i < world->number_of_entities; i++) {
        destroy_Entity(&world->entities[i]);
    }
    int y;
    for (y = 0; y < world->height; y++) {
        int x;
        for (x = 0; x < world->width; x++) {
            destroy_Entity(&world->map[y][x]);
        }
        free(world->map[y]);
        free(world->light_map[y]);
    }
    free(world->map);
    free(world->light_map);
    // Free the entities array
    free(world->entities);
}
