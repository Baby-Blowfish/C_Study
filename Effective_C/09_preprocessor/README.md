# 전처리기

> 컴파일 초기 단계에서 실행되는 일부 어떤 파일의 코들르 다른 파일에 삽입하는 것, 매크로 확장 중에 식별자를 자동으로 소스 코드 세그먼트로 대체
> 개체 같은 매크로, 함수 같은 매크로를 정의하고 코드를 조건부로 포함하는 방법

| 종류 | 설명 | 예시 |
|------|------|------|
| **매크로 정의 (`#define`)** | 코드에 이름을 붙이거나 상수 정의 | `#define PI 3.14` |
| **조건부 컴파일 (`#if`, `#ifdef`, `#ifndef` 등)** | 특정 조건에 따라 코드 포함 여부 결정 | `#ifdef DEBUG` |
| **파일 포함 (`#include`)** | 다른 파일의 내용을 현재 파일에 삽입 | `#include <stdio.h>` |
| **매크로 함수** | 간단한 함수처럼 동작하는 매크로 | `#define SQUARE(x) ((x)*(x))` |
| **라인 제어 (`#line`)** | 컴파일러에게 현재 파일과 줄 번호를 알려줌 | `#line 100 "myfile.c"` |


1. **파일 포함 처리 (`#include`)**
2. **매크로 치환 (`#define`, `#undef`)**
3. **조건부 컴파일 (`#if`, `#ifdef`, `#else`, `#endif` 등)**
4. **기타 지시문 (`#error`, `#pragma`, `#line` 등)**

## 컴파일 과정

문자 매핑 -> 줄 결합 -> 토큰화 -> 전처리 -> 문자 집합 매핑 -> 문자열 연결 => 변환 -> 링크

- 전처리기는 함수나 변수, 형식에 대해서 알지 못한다. 
- 헤더 이름과 식별자, 리터럴, 그리고 (+,-, ! ..)같은 문장 부호 문자와 같은 기본 요소 ->`토큰`
- #으로 시작하는 지시문(Directive) + 토큰 <- 전처리기가 관심있는 부분
- 전처리기 출력 : 출력파일.i
  - GCC : gcc -option -E -o 출력파일.i 소스 파일.c



  ### 전체 컴파일 과정 요약 (GCC 기준)

  ```
  소스 코드 (hello.c)
    ↓
  1. 문자 매핑 (Character Mapping)
  2. 줄 결합 (Line Splicing) — 백슬래시(\) + 개행 제거
  3. 토큰화 (Tokenization) — 단어처럼 쪼갬
  4. 전처리 (Preprocessing) — #include, #define, #ifdef 등 처리
    → 출력: hello.i (전처리 결과)
  5. 컴파일 (Compilation) — 어셈블리 코드 생성
    → 출력: hello.s
  6. 어셈블 (Assembling) — 목적 파일 생성
    → 출력: hello.o
  7. 링크 (Linking) — 실행 파일 생성
    → 출력: a.out (또는 지정된 이름)
  ```

  ### 🔹 전처리기의 한계
  - 전처리기는 **함수의 구조나 문법**을 이해하지 못하고,
  - 오직 **토큰**(token) 단위로 작업함.
    - 예: `int`, `PI`, `"Hello"` 같은 리터럴과 식별자
    - `+`, `-`, `{`, `}` 같은 연산자 및 기호


  ### 예제 코드: `test.c`
  ```c
  #include <stdio.h>
  #define PI 3.14

  int main() {
      printf("PI = %f\n", PI);
      return 0;
  }
  ```

  ### 명령어: 전처리 결과 출력
  ```sh
  gcc -E -o test.i test.c
  ```

  ### 전처리 결과 파일 `test.i` 일부:
  ```c
  # 1 "test.c"
  # 1 "<built-in>"
  # 1 "<command-line>"
  # 1 "test.c"
  # 1 "/usr/include/stdio.h" 1 3 4
  ... (헤더 포함 내용)
  int main() {
      printf("PI = %f\n", 3.14);
      return 0;
  }
  ```

  - 전처리기는 **구조를 해석하지 않고**, 문자열과 토큰 수준의 **치환과 조건 분기**만 수행.
  - **매크로**, **조건부 컴파일**, **헤더 포함** 등은 모두 전처리 단계에서 처리됨.


## 파일 포함

  ###  `#include` 전처리 지시문

  ```c
  #include "파일명"
  #include <파일명>
  ```
  - **목적**: 다른 파일(주로 헤더 파일)의 내용을 현재 소스 코드에 **그대로 복사**하는 것
  - **위치**: 소스 파일 맨 위 또는 필요한 함수 정의 위
  - **확장**: 컴파일러는 전처리 과정에서 `#include`로 지정된 파일을 찾아 **그 자리**에 내용 전체를 삽입

  ### 🧠 전이적 속성 (Transitive Inclusion)

  > 포함된 파일이 또 다른 파일을 포함하면, 그 내용까지 전처리에 포함된다.

  ```c
  // file_a.h
  #define A 1

  // file_b.h
  #include "file_a.h"
  #define B 2

  // main.c
  #include "file_b.h"
  int main() {
      return A + B;
  }
  ```
  전처리된 결과 (`gcc -E main.c`)에는 `file_a.h`와 `file_b.h`의 **모든 내용**이 들어있음 → **전이적 포함**



  ###  `" "`와 `< >`의 차이

  | 구분 | `"헤더이름"` | `<헤더이름>` |
  |------|--------------|---------------|
  | 검색 위치 | 현재 소스 파일과 **같은 디렉터리 우선** | **시스템 디렉터리에서만** 검색 |
  | 용도 | **사용자 정의 헤더 파일** 포함 시 사용 | **표준 라이브러리** 또는 **시스템 헤더** 포함 시 사용 |
  | 예 | `#include "myheader.h"` | `#include <stdio.h>` |

  GCC 검색 순서
  - `" "`:
    1. 현재 파일의 디렉터리
    2. `-I`로 지정된 사용자 include 경로
    3. 시스템 경로 (e.g., `/usr/include`)
  - `< >`:
    1. `-I`로 지정된 경로는 **제외**
    2. 시스템 경로만 검색


## 조건부 포함

  ### 조건부 포함 지시문 (`#if`, `#ifdef`, `#ifndef`, `#elif`, `#else`, `#endif`)

  전처리 조건에 따라 **특정 코드 블록의 포함 여부를 제어**합니다. 플랫폼별 코드, 디버그 코드 등을 분기 처리할 때 유용합니다.

  ### 기본 문법

  ```c
  #if 조건
      // 조건이 참일 때 포함됨
  #elif 다른 조건
      // 위 조건이 거짓이고 이 조건이 참이면 포함됨
  #else
      // 위 모든 조건이 거짓일 때 포함됨
  #endif
  ```

  ### 정의된 매크로 검사

  ```c
  #ifdef IDENTIFIER      →  #if defined(IDENTIFIER)
  #ifndef IDENTIFIER     →  #if !defined(IDENTIFIER)
  ```

  ### 예시

  ```c
  #if defined(_WIN32)
      #include <windows.h>
  #elif defined(__linux__)
      #include <unistd.h>
  #else
      #error "지원하지 않는 플랫폼입니다."
  #endif
  ```


  ### `#error` 지시문

  - 명시적으로 전처리 단계에서 **컴파일을 중단하고 오류 메시지를 출력**할 수 있게 합니다.

  ```c
  #ifndef MY_HEADER
  #error "MY_HEADER가 정의되지 않았습니다."
  #endif
  ```

  > 전처기 출력 시:  
  > `error: MY_HEADER가 정의되지 않았습니다.`



  ### 헤더 보호기 (Include Guard)

  헤더 파일이 여러 번 포함될 경우, 중복 정의로 인한 컴파일 오류 방지를 위해 사용합니다.


  ```c
  #ifndef UNIQUE_IDENTIFIER
  #define UNIQUE_IDENTIFIER

  // 헤더 내용

  #endif // UNIQUE_IDENTIFIER
  ```


  `my_utils.h` → 식별자: `MY_UTILS_H`

  ```c
  #ifndef MY_UTILS_H
  #define MY_UTILS_H

  int add(int a, int b);

  #endif // MY_UTILS_H
  ```

  - 경로 + 파일 이름을 **대문자 + 언더스코어**로
  - 예: `include/utils/my_math.h` → `UTILS_MY_MATH_H`

## 매크로 

  ### 매크로 정의 (`#define`)

  ```c
  #define 식별자 대체_목록
  ```
  - **전처리 단계에서** 식별자를 찾아 **대체_목록으로 치환**
  - 종료 조건: **첫 번째 줄 바꿈**
  - 매크로는 **함수 블록과 무관하게 전역적으로 적용**
  - **`#undef`**를 만나거나 파일이 끝날 때까지 유효


  ### 개체-유사 매크로 (Object-like Macro)

  > 단순 값이나 이름을 정의할 때 사용

  ```c
  #define PI 3.14159
  #define VERSION "1.0.0"
  ```

  사용:
  ```c
  float area = PI * r * r;
  ```


  ### 함수-유사 매크로 (Function-like Macro)

  > 인수(매개변수)를 받아서, 함수처럼 동작

  ```c
  #define SQUARE(x) ((x)*(x))
  ```

  사용:
  ```c
  int a = SQUARE(3);     // → ((3)*(3)) → 9
  int b = SQUARE(1+2);   // → ((1+2)*(1+2)) → 9 (괄호 안 쓰면 오류 발생!)
  ```

  ### 안전한 매크로 작성 규칙

  | 항목 | 설명 |
  |------|------|
  | 괄호 | 인자와 전체 식 모두 **괄호로 감쌀 것** |
  | 다중 평가 | 인자가 **여러 번 평가**될 수 있으므로 **함수보다 부작용이 클 수 있음** |
  | 예외 처리 | `_Generic`, `do { ... } while(0)` 등을 활용해 대체 가능 |


  ### 타입에 따라 분기: `_Generic` (C11)
  ```c
  #define cbrt(X) _Generic((X), \
      long double: cbrtl(X), \
      float: cbrtf(X), \
      default: cbrt(X))
  ```

  ### 반복 정의 응용: `X-Macro`

  ```c
  // header.h
  NAME(first)
  NAME(second)
  NAME(third)
  ```

  ```c
  // main.c
  enum NAMES {
      #define NAME(X) X,
      #include "header.h"
      #undef NAME
  };

  void print_name(enum NAMES name) {
      switch(name) {
          #define NAME(X) case X: puts(#X); break;
          #include "header.h"
          #undef NAME
      }
  }
  ```

  - `"X"`는 문자열이 아니라 **토큰이자 매크로 인자**이고,
  - `#X`는 문자열화 연산자 → `X`를 `"X"`로 치환
  - `#undef`는 매크로를 한 번 사용한 후 **제거하여** 재사용 가능하게 함


  ###  다중 평가

  ```c
  #define INCREMENT(x) (x + 1)

  int i = 3;
  int j = INCREMENT(i++); // → (i++ + 1) → 부작용
  ```

  해결은? **인라인 함수** 또는 **임시 변수 사용**


## 매크로 대체

아주 중요한 내용 정리 중이시고, 매크로의 **대체 기법들**에 대해 더 깊이 들어가고 계시네요.  
이번엔 정리해주신 항목들 위주로 빠진 설명을 보완하고, 각 개념을 **명확한 예제**, **설명**, **주의사항** 중심으로 재구성해 드리겠습니다.

---

# ✅ 매크로 대체 (Macro Substitution)

함수처럼 쓰이지만 **단순 치환**이며, 컴파일러가 아닌 **전처리기 수준**에서 처리


  ### 1. 함수 같은 매크로 (Function-like Macro)

  - 괄호를 이용해 인자를 받을 수 있음
  - 단순한 연산 또는 반복 코드에 사용
  - **인자의 반복 평가**로 부작용 발생 가능

  ```c
  #define SQUARE(x) ((x)*(x))
  SQUARE(2+3)  // ((2+3)*(2+3)) → 25 (OK)
  SQUARE(i++)  // ((i++)*(i++)) → 부작용!
  ```

  > ⚠ **항상 괄호를 철저하게 감싸야 함**


  ### 2. 문자열화 연산자 `#`

  - 인자를 **문자열 리터럴**로 치환

  ```c
  #define STRINGIZE(x) #x

  const char *s = STRINGIZE(Hello World);  
  // → const char *s = "Hello World";
  ```
  - 디버깅용 로그 메시지
  - 컴파일 타임 매크로 추적 등


  ### 3. 토큰 붙이기 연산자 `##`

  - 인자들을 붙여서 새로운 토큰(식별자 등)을 생성

  ```c
  #define PASTE(x, y) x ## _ ## y

  int PASTE(foo, bar) = 10;  
  // → int foo_bar = 10;
  ```

  > ⚠ 붙여진 결과가 **유효한 토큰**이어야 컴파일 가능

  ### 다중 평가

  ```c
  #define bad_abs(x) (x >= 0 ? x : -x)

  int func(int i) {
      return bad_abs(i++);  // ❌ 위험: i++ 평가 2번 → 결과 예측 불가
      // return (i++ >- 0 ? i++ : -i++)
  }
  ```

  ### 🔹 해결책
  - `static inline` 함수로 대체하거나
  - 임시 변수 매크로 패턴 사용

  ### 5. 쉼표(,)는 매크로 인수 구분자로 처리됨

  ### 🔸 예시
  ```c
  // stdatomic.h
  #define ATOMIC_VAR_INIT(value) (value)
  ```

  ```c
  #include <stdatomic.h>

  struct S {
      int x, y;
  };

  // 아래 매크로 호출은 컴파일 에러!
  _Atomic struct S val = ATOMIC_VAR_INIT({1,2});
  ```

  - `{1,2}`는 쉼표가 포함된 **하나의 인자**처럼 보이지만
  - 매크로는 쉼표를 **인자 구분자**로 해석 → `{1`, `2}`로 분리해버림

  ```c
  #define ATOMIC_VAR_INIT(value) ((value))

  _Atomic struct S val = ATOMIC_VAR_INIT((struct S){1, 2});  // ✅ OK
  ```

## 형식 제네릭 매크로

C 언어에서는 함수 오버로딩이 없기 때문에, **인자의 타입에 따라 적절한 동작을 선택하는 방식**이 필요
이를 위한 문법이 **C11**에서 도입된 `_Generic`입니다.

```c
_Generic(식,  
    타입1: 결과1,  
    타입2: 결과2,  
    ...  
    default: 기본값
)
```

- `식`의 타입을 판별하여,
- 가장 먼저 일치하는 `타입`의 결과로 **대체**
- 일치하는 타입이 없으면 `default` 결과로 대체


```c
#include <stdio.h>
#include <math.h>

#define my_abs(x) _Generic((x), \
    int: abs, \
    long: labs, \
    float: fabsf, \
    double: fabs, \
    default: fabs)(x) // 뒤의 (x)는 선택된 값이 함수이면 호출하기 위해서

int main() {
    printf("%d\n", my_abs(-5));        // int → abs
    printf("%f\n", my_abs(-5.3f));     // float → fabsf
    printf("%f\n", my_abs(-5.3));      // double → fabs
}
```

> 🔍 이 매크로는 `my_abs(x)`에 인자로 전달된 타입에 따라 `abs`, `labs`, `fabsf`, `fabs` 중에서 자동으로 선택됨.


문자열로 타입 이름 반환

```c
#define typename(x) _Generic((x), \
    int: "int", \
    float: "float", \
    double: "double", \
    char *: "char*", \
    default: "unknown")

printf("type: %s\n", typename(3.14f));   // 출력: type: float
```

`typeof` 없이 `inline` 함수처럼 사용

```c
#define square(x) _Generic((x), \
    int: square_int, \
    float: square_float \
)(x)

int square_int(int x) { return x * x; }
float square_float(float x) { return x * x; }

int a = square(3);      // → square_int(3)
float b = square(2.5f); // → square_float(2.5f)
```


## 미리 정의된 매크로
**C 컴파일러가 자동으로 정의**하는 것들로, **컴파일 타임 정보**, **파일 이름**, **라인 번호** 등

  ### 미리 정의된 매크로 (Predefined Macros)

  | 매크로 이름 | 설명 |
  |-------------|------|
  | `__FILE__`   | 현재 소스 파일 이름 (문자열) |
  | `__LINE__`   | 현재 줄 번호 (정수) |
  | `__DATE__`   | 컴파일한 날짜 (문자열, 예: `"Apr 17 2025"`) |
  | `__TIME__`   | 컴파일한 시간 (문자열, 예: `"13:37:02"`) |
  | `__func__`   | 현재 함수 이름 (문자열, C99부터) |
  | `__STDC__`   | ISO C 준수 컴파일러이면 `1`로 정의 |
  | `__STDC_VERSION__` | 지원하는 C 표준 버전 (C99 이상부터 정의됨) |
  | `__cplusplus` | C++ 코드일 경우 정의되며, 버전 번호 값 가짐 |

```c
#include <stdio.h>

void log_debug(const char *msg) {
    printf("[DEBUG] %s:%d in %s() → %s\n", __FILE__, __LINE__, __func__, msg);
}

int main() {
    log_debug("프로그램 시작");
    return 0;
}
```

**출력 예시**
```
[DEBUG] main.c:6 in main() → 프로그램 시작
```

```c
printf("Build date: %s\n", __DATE__);  // "Apr 17 2025"
printf("Build time: %s\n", __TIME__);  // "13:37:02"
```


| 매크로 | 의미 |
|--------|------|
| `__STDC__ == 1` | 표준 C 컴파일러임 |
| `__STDC_VERSION__ == 199409L` | C95 |
| `__STDC_VERSION__ == 199901L` | C99 |
| `__STDC_VERSION__ == 201112L` | C11 |
| `__STDC_VERSION__ == 201710L` | C17 |

```c
#ifdef __STDC_VERSION__
    #if __STDC_VERSION__ >= 201112L
        printf("C11 or later\n");
    #endif
#endif
```


