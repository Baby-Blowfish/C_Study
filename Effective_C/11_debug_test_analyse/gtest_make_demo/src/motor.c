#include "motor.h"

int clamp_speed(int speed) {
    if (speed > 100) return 100;
    if (speed < 0) return 0;
    return speed;
}

