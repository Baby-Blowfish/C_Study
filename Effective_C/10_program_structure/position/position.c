#include <stdlib.h>
#include "position.h"

// int용 구조체 정의 및 함수 구현
struct Position_int {
    int x, y;
};

Position_int* create_position_int(int x, int y) {
    Position_int* p = malloc(sizeof(Position_int));
    if (p) { p->x = x; p->y = y; }
    return p;
}

void move_position_int(Position_int* p, int dx, int dy) {
    if (p) { p->x += dx; p->y += dy; }
}

void print_position_int(const Position_int* p) {
    if (p) printf("[int] Position: (%d, %d)\n", p->x, p->y);
}

void destroy_position_int(Position_int* p) {
    free(p);
}

// float용 구조체 정의 및 함수 구현
struct Position_float {
    float x, y;
};

Position_float* create_position_float(float x, float y) {
    Position_float* p = malloc(sizeof(Position_float));
    if (p) { p->x = x; p->y = y; }
    return p;
}

void move_position_float(Position_float* p, float dx, float dy) {
    if (p) { p->x += dx; p->y += dy; }
}

void print_position_float(const Position_float* p) {
    if (p) printf("[float] Position: (%.2f, %.2f)\n", p->x, p->y);
}

void destroy_position_float(Position_float* p) {
    free(p);
}
