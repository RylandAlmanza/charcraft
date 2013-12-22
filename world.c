#include "world.h"

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
World construct_World() {
    World world;
    world.number_of_entities = 0;
    world.entities = malloc(sizeof(Entity));
    world.add_entity = &World_add_entity;
    world.get_entity = &World_get_entity;
    world.move_entity = &World_move_entity;
    return world;
}

// Probably the best name for a function. Destroys the world.
void destroy_World(World *world) {
    int i;
    // Loop through all the entities and make sure they're properly destroyed
    for (i = 0; i < world->number_of_entities; i++) {
        destroy_Entity(&world->entities[i]);
    }
    // Free the entities array
    free(world->entities);
}
