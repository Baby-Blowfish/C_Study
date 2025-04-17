#include <stdio.h>
#include "mymath.h"

int main() {
    int x = 3;
    int y = 4;

    printf("add(%d, %d) = %d\n", x, y, add(x, y));
    printf("square(%d) = %d\n", x, square(x));

    return 0;
}