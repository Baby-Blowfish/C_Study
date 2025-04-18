// test_static_assert.c

#include <assert.h>

#define BUFFER_SIZE -128  // 실수로 잘못 설정했다고 가정

static_assert(BUFFER_SIZE > 0, "BUFFER_SIZE는 0보다 커야 합니다!");

char buffer[BUFFER_SIZE];

int main() {
    return 0;
}