#include <stdlib.h>
#include <ncurses.h>
#include "display.h"
#include "colorutils.h"

void LayerQueue_add_cell(LayerQueue *self, Cell cell) {
    self->cells[self->length] = cell;
    self->length = self->length + 1;
    self->cells = realloc(self->cells, sizeof(Cell) * (self->length + 1));
}

void LayerQueue_reset(LayerQueue *self) {
    self->length = 0;
    self->cells = realloc(self->cells, sizeof(Cell));
}

LayerQueue construct_LayerQueue() {
    LayerQueue layer_queue;
    layer_queue.length = 0;
    layer_queue.cells = malloc(sizeof(Cell));
    layer_queue.add_cell = &LayerQueue_add_cell;
    layer_queue.reset = &LayerQueue_reset;
    return layer_queue;
}

void destroy_LayerQueue(LayerQueue *layer_queue) {
    free(layer_queue->cells);
}    

void Display_reset_queue(Display *self) {
    int i;
    for (i = 0; i < 5; i++) {
        self->layer_queues[i].reset(&self->layer_queues[i]);
    }
}

void Display_add_entity_to_queue(Display *self, Entity entity) {
    int i;
    for (i = 0; i < entity.number_of_cells; i++) {
        Cell cell = entity.cells[i];
        cell.x = entity.x + cell.x;
        cell.y = entity.y + cell.y;
        self->layer_queues[cell.z].add_cell(&self->layer_queues[cell.z], cell);
    }
}

void Display_draw(Display *self) {
    int layer_number;
    for (layer_number = 0; layer_number < 5; layer_number++) {
        LayerQueue layer_queue = self->layer_queues[layer_number];
        int i;
        for (i = 0; i < layer_queue.length; i++) {
            int color_pair = get_color_pair(layer_queue.cells[i].foreground,
                                            layer_queue.cells[i].background);
            attron(COLOR_PAIR(color_pair));
            mvaddch(layer_queue.cells[i].y,
                    layer_queue.cells[i].x,
                    layer_queue.cells[i].character);
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
