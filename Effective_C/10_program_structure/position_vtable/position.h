#ifndef POSITION_H
#define POSITION_H
#include <stdlib.h>

typedef void* Position;

// vtable 구조체 정의
typedef struct {
    void (*move)(Position, void* dx, void* dy);
    void (*print)(const Position);
    void (*destroy)(Position);
} PositionVTable;

// 공통 구조체 (핸들 + vtable)
typedef struct {
    void* data;
    const PositionVTable* vtable;
} PositionHandle;

// Position 생성 함수들 (각 타입별)
PositionHandle* create_position_int(int x, int y);
PositionHandle* create_position_float(float x, float y);

// 공통 API
static inline void move_position(PositionHandle* p, void* dx, void* dy) {
    p->vtable->move(p->data, dx, dy);
}

static inline void print_position(const PositionHandle* p) {
    p->vtable->print(p->data);
}

static inline void destroy_position(PositionHandle* p) {
    p->vtable->destroy(p->data);
    free(p);
}

#endif
