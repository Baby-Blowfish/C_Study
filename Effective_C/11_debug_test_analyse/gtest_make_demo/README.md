# 📘 GoogleTest 매크로 & 함수 요약


## 🔹 기본 테스트 구조

```cpp
#include <gtest/gtest.h>

TEST(TestSuiteName, TestName) {
    // 테스트 내용
    EXPECT_EQ(1 + 1, 2);
}
```

## 🔹 Assertion 매크로

| 매크로 | 설명 |
|--------|------|
| `EXPECT_EQ(a, b)` | `a == b`일 것으로 기대. 실패해도 계속 진행 |
| `EXPECT_NE(a, b)` | `a != b`일 것으로 기대 |
| `EXPECT_LT(a, b)` | `a < b`일 것으로 기대 |
| `EXPECT_LE(a, b)` | `a <= b`일 것으로 기대 |
| `EXPECT_GT(a, b)` | `a > b`일 것으로 기대 |
| `EXPECT_GE(a, b)` | `a >= b`일 것으로 기대 |

```cpp
EXPECT_EQ(add(2, 2), 4);
EXPECT_NE(speed, 0);
```


## 🔹 Fatal Assertion (중단)

| 매크로 | 설명 |
|--------|------|
| `ASSERT_EQ(a, b)` | 실패 시 테스트 함수 즉시 종료 |
| `ASSERT_NE(a, b)` | 동일 |
| `ASSERT_TRUE(expr)` | `expr`이 `true`여야 함 |
| `ASSERT_FALSE(expr)` | `expr`이 `false`여야 함 |

```cpp
ASSERT_NE(ptr, nullptr);  // null이면 더 이상 진행 안 됨
```


## 🔹 일반 매크로

| 매크로 | 설명 |
|--------|------|
| `FAIL()` | 무조건 실패로 처리 |
| `SUCCEED()` | 명시적 성공 표시 |
| `ADD_FAILURE()` | 테스트는 계속하지만 실패 추가 |

```cpp
if (!connected)
    FAIL() << "Connection failed";

SUCCEED() << "No error occurred";
```



## 🔹 부동소수점 비교

| 매크로 | 설명 |
|--------|------|
| `EXPECT_FLOAT_EQ(a, b)` | float 비교 (정확한 비교) |
| `EXPECT_DOUBLE_EQ(a, b)` | double 비교 |
| `EXPECT_NEAR(a, b, abs_error)` | 오차 범위 지정 비교 |



## 🔹 문자열 비교

| 매크로 | 설명 |
|--------|------|
| `EXPECT_STREQ(a, b)` | C-style 문자열 정확히 일치 |
| `EXPECT_STRNE(a, b)` | C-style 문자열 다름 확인 |



## 🔹 테스트 그룹/환경 구성

### 🔸 여러 테스트를 공유하는 클래스 사용

```cpp
class MyFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // 매 테스트 전에 실행
    }

    void TearDown() override {
        // 매 테스트 후에 실행
    }

    int shared_value = 42;
};

TEST_F(MyFixture, TestWithFixture) {
    EXPECT_EQ(shared_value, 42);
}
```


## 🧪 테스트 실행 함수

```cpp
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

> GoogleTest에서 `main()` 함수는 위처럼 작성하거나,  
> `gtest_main` 라이브러리 사용 시 생략 가능


