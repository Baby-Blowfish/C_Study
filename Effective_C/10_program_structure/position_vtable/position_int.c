#include <stdio.h>
#include <stdlib.h>
#include "position.h"

typedef struct {
    int x, y;
} PositionInt;

static void move_int(Position p, void* dx, void* dy) {
    PositionInt* pi = (PositionInt*)p;
    pi->x += *(int*)dx;
    pi->y += *(int*)dy;
}

static void print_int(const Position p) {
    PositionInt* pi = (PositionInt*)p;
    printf("[int] Position: (%d, %d)\n", pi->x, pi->y);
}

static void destroy_int(Position p) {
    free(p);
}

static const PositionVTable int_vtable = {
    .move = move_int,
    .print = print_int,
    .destroy = destroy_int
};

PositionHandle* create_position_int(int x, int y) {
    PositionInt* pi = malloc(sizeof(PositionInt));
    pi->x = x;
    pi->y = y;

    PositionHandle* handle = malloc(sizeof(PositionHandle));
    handle->data = pi;
    handle->vtable = &int_vtable;

    return handle;
}
