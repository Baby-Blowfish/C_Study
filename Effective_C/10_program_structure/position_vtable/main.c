#include <stdio.h>
#include "position.h"

int main() {
    int dx = 1, dy = 2;
    float fx = 0.5f, fy = 1.5f;

    PositionHandle* p1 = create_position_int(10, 20);
    move_position(p1, &dx, &dy);
    print_position(p1);
    destroy_position(p1);

    PositionHandle* p2 = create_position_float(1.0f, 2.0f);
    move_position(p2, &fx, &fy);
    print_position(p2);
    destroy_position(p2);

    return 0;
}
