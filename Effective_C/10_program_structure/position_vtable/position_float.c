#include <stdio.h>
#include <stdlib.h>
#include "position.h"

typedef struct {
    float x, y;
} PositionFloat;

static void move_float(Position p, void* dx, void* dy) {
    PositionFloat* pf = (PositionFloat*)p;
    pf->x += *(float*)dx;
    pf->y += *(float*)dy;
}

static void print_float(const Position p) {
    PositionFloat* pf = (PositionFloat*)p;
    printf("[float] Position: (%.2f, %.2f)\n", pf->x, pf->y);
}

static void destroy_float(Position p) {
    free(p);
}

static const PositionVTable float_vtable = {
    .move = move_float,
    .print = print_float,
    .destroy = destroy_float
};

PositionHandle* create_position_float(float x, float y) {
    PositionFloat* pf = malloc(sizeof(PositionFloat));
    pf->x = x;
    pf->y = y;

    PositionHandle* handle = malloc(sizeof(PositionHandle));
    handle->data = pf;
    handle->vtable = &float_vtable;

    return handle;
}
