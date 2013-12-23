#include <stdlib.h>
#include <ncurses.h>
#include "display.h"
#include "colorutils.h"

void LayerQueue_add_entity(LayerQueue *self, Entity entity) {
    self->entities[self->length] = entity;
    self->length = self->length + 1;
    self->entities = realloc(self->entities, sizeof(Entity) * (self->length + 1));
}

void LayerQueue_reset(LayerQueue *self) {
    self->length = 0;
    self->entities = realloc(self->entities, sizeof(Entity));
}

LayerQueue construct_LayerQueue() {
    LayerQueue layer_queue;
    layer_queue.length = 0;
    layer_queue.entities = malloc(sizeof(Entity));
    layer_queue.add_entity = &LayerQueue_add_entity;
    layer_queue.reset = &LayerQueue_reset;
    return layer_queue;
}

void destroy_LayerQueue(LayerQueue *layer_queue) {
    free(layer_queue->entities);
}    

void Display_reset_queue(Display *self) {
    int i;
    for (i = 0; i < 5; i++) {
        self->layer_queues[i].reset(&self->layer_queues[i]);
    }
}

void Display_add_entity_to_queue(Display *self, Entity entity) {
    self->layer_queues[entity.z].add_entity(&self->layer_queues[entity.z],
                                            entity);
}

void Display_draw(Display *self) {
    int layer_number;
    for (layer_number = 0; layer_number < 5; layer_number++) {
        LayerQueue layer_queue = self->layer_queues[layer_number];
        int i;
        for (i = 0; i < layer_queue.length; i++) {
            int color_pair = get_color_pair(layer_queue.entities[i].foreground,
                                            layer_queue.entities[i].background);
            attron(COLOR_PAIR(color_pair));
            mvaddch(layer_queue.entities[i].y,
                    layer_queue.entities[i].x,
                    layer_queue.entities[i].character);
            attroff(COLOR_PAIR(color_pair));
        }
    }
    refresh();
}


Display construct_Display() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    // Enable ncurses colors
    start_color();
    // Init color pairs
    initialize_all_color_pairs();

    Display display;
    int i;
    for (i = 0; i < 5; i++) {
        display.layer_queues[i] = construct_LayerQueue();
    }
    display.reset_queue = &Display_reset_queue;
    display.add_entity_to_queue = &Display_add_entity_to_queue;
    display.draw = &Display_draw;
    return display;
}

void destroy_Display(Display *display) {
    int i;
    for (i = 0; i < 5; i++) {
        destroy_LayerQueue(&display->layer_queues[i]);
    }
    curs_set(1);
    endwin();
}
