#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "entity.h"

typedef struct LayerQueueS LayerQueue;

struct LayerQueueS {
    Entity *entities;
    int length;
    void (*add_entity)(LayerQueue *self, Entity entity);
    void (*reset)(LayerQueue *self);
};

LayerQueue construct_LayerQueue();
void destroy_LayerQueue(LayerQueue *layer_queue);

typedef struct DisplayS Display;

struct DisplayS {
    LayerQueue layer_queues[5];
    void (*initialize)(Display *self);
    void (*reset_queue)(Display *self);
    void (*add_entity_to_queue)(Display *self, Entity entity);
    void (*draw)(Display *self);
};

Display construct_Display();
void destroy_Display(Display *display);

#endif
