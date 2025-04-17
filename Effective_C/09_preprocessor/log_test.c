#include "log_macro.h"

int divide(int a, int b) {
    if (b == 0) {
        LOG_ERROR("Division by zero! a=%d", a);
        return 0;
    }
    LOG_INFO("Dividing %d by %d", a, b);
    return a / b;
}

int main() {
    LOG_DEBUG("Program started");
    int result = divide(10, 0);
    LOG_INFO("Result = %d", result);
    return 0;
}
