#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "cell.h"

typedef struct LayerQueueS LayerQueue;

struct LayerQueueS {
    Cell *cells;
    int length;
    void (*add_cell)(LayerQueue *self, Cell cell);
    void (*reset)(LayerQueue *self);
};

LayerQueue construct_LayerQueue();
void destroy_LayerQueue(LayerQueue *layer_queue);

typedef struct DisplayS Display;

struct DisplayS {
    LayerQueue layer_queues[5];
    void (*initialize)(Display *self);
    void (*reset_queue)(Display *self);
    void (*add_cell_to_queue)(Display *self, Cell cell);
    void (*draw)(Display *self);
};

Display construct_Display();
void destroy_Display(Display *display);

#endif
