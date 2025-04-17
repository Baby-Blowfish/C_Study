#include "position.h"

int main() {
    // int 타입 구조체 사용
    Position_int* p1 = create_position(10, 20);
    move_position(p1, 1, 2);
    print_position(p1);
    destroy_position(p1);

    // float 타입 구조체 사용
    Position_float* p2 = create_position(1.5f, 2.5f);
    move_position(p2, 0.5f, 0.5f);
    print_position(p2);
    destroy_position(p2);

    return 0;
}
