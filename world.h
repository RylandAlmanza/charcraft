#ifndef WORLD_H_
#define WORLD_H_

#include <stdbool.h>
#include "entity.h"

typedef struct WorldS World;

struct WorldS {
    int width;
    int height;
    int number_of_entities;
    Entity *entities;
    Entity **map;
    int number_of_lights;
    Cell **lights;
    bool **light_map;
    void (*add_entity)(World *self, Entity entity);
    Entity *(*get_entity)(World *self, int id);
    bool (*move_entity)(World *self, int id, int x_delta, int y_delta);
};

World construct_World(int width, int height);
void destroy_World();

#endif
