#ifndef POSITION_H
#define POSITION_H

#include <stdio.h>

// 내부 구조체 이름만 노출
typedef struct Position_int Position_int;
typedef struct Position_float Position_float;

// 공통 타입 핸들 정의
typedef void* Position;

// API 함수 구현
Position_int* create_position_int(int x, int y);
Position_float* create_position_float(float x, float y);

void move_position_int(Position_int* p, int dx, int dy);
void move_position_float(Position_float* p, float dx, float dy);

void print_position_int(const Position_int* p);
void print_position_float(const Position_float* p);

void destroy_position_int(Position_int* p);
void destroy_position_float(Position_float* p);

// 제네릭 매크로로 사용자 편의 제공
#define create_position(x, y) \
    _Generic((x), \
        int: create_position_int, \
        float: create_position_float)(x, y)

#define move_position(p, dx, dy) \
    _Generic((dx), \
        int: move_position_int, \
        float: move_position_float)(p, dx, dy)

#define print_position(p) \
    _Generic((p), \
        Position_int*: print_position_int, \
        Position_float*: print_position_float)(p)

#define destroy_position(p) \
    _Generic((p), \
        Position_int*: destroy_position_int, \
        Position_float*: destroy_position_float)(p)

#endif // POSITION_H

