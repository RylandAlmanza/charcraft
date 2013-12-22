#ifndef WORLD_H_
#define WORLD_H_

#include <stdbool.h>
#include "entity.h"

typedef struct WorldS World;

struct WorldS {
    int number_of_entities;
    Entity *entities;
    Entity *tiles;
    void (*add_entity)(World *self, Entity entity);
    Entity *(*get_entity)(World *self, int id);
    bool (*move_entity)(World *self, int id, int x_delta, int y_delta);
};

World construct_World();
void destroy_World();

#endif
