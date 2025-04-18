#include <gtest/gtest.h>

extern "C" {
    #include "motor.h"
}

TEST(MotorTest, ClampLimits) {
    EXPECT_EQ(clamp_speed(150), 99);
    EXPECT_EQ(clamp_speed(-20), 0);
    EXPECT_EQ(clamp_speed(50), 50);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

