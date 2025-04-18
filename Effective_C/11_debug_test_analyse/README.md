# 디버깅과 테스트, 분석

## 어설션 (Assertions) 

  - **조건자(Predicate)**: 프로그램의 논리적 조건을 표현하는 부울 값 (`true` 또는 `false`)
  - **어설션**: 조건자가 항상 `참`이어야 한다는 “가정”을 명시적으로 표현  
    → **디버깅, 검증, 문서화**의 역할을 동시에 수행


  ### 정적 어설션 (`static_assert`)
  - **컴파일 타임**에 조건을 확인
  - `static_assert(정수 상수 식, "에러 메시지");`
  - C11부터 도입 (`_Static_assert`가 내부 명칭)

  - 구조체의 크기, 정렬, 타입 간 관계 등 **컴파일 타임 검증**
  - 오타나 실수로 인한 **패딩 문제, 제한 위반**을 미리 탐지


  ### 예제 1 – 구조체 패딩 검증
  ```c
  #include <assert.h>

  struct packed {
    unsigned int i;  // 4바이트
    char *p;         // 64bit에선 8바이트 정렬이 필요함 → i 다음에 4바이트 패딩 추가 가능
  };

  // sizeof(struct packed) == sizeof(int) + sizeof(char*) 를 기대
  static_assert(
    sizeof(struct packed) == sizeof(unsigned int) + sizeof(char *),
    "struct packed는 어떤 패딩도 가져서는 안된다."
  );
  ```
  > 구조체를 직렬화해서 파일로 저장하거나 네트워크로 송수신하거나 메모리 맵핑으로 사용하는 경우 패딩이 없어야 한다.   
  > 패딩이 없어야 정상 동작하는 코드에서 강제로 컴파일 타임에 검사하도록함.

  ### 예제 2 – 조건 삽입 시 위치
  ```c
  #include <assert.h>
  #include <stdio.h>
  #include <limits.h>

  void clear_stdin(void) {
    int c;
    do {
      c = getchar();
      static_assert(UCHAR_MAX < UINT_MAX, "FIO34-C violation");
    } while (c != EOF);
  }
  ```

  | 버전 | `_Static_assert` | `static_assert` |
  |------|------------------|------------------|
  | C11  | 함수 내부 사용 가능 | `<assert.h>`에 매크로로 정의됨 → **함수 내부 사용 시 제한될 수 있음** |
  | C23  | **폐지(deprecated)** | **정식 키워드로 승격됨** → **함수 본문에서도 사용 가능** |

  ✔ C11 기준:
  - `_Static_assert(expr, msg);`  
    → 함수 본문 안에서도 **정상 작동**
  - `static_assert(expr, msg);`  
    → 사실상 `#define static_assert _Static_assert`  
    → **함수 본문 안에서는 컴파일러에 따라 안 될 수 있음**

  ✔ C23 기준:
  - `static_assert`는 이제 **정식 키워드**
  - `#include <assert.h>` 없이도 사용 가능
  - **함수 본문 안에서도 완벽히 허용**
  - `_Static_assert`는 더 이상 권장되지 않음 (deprecated)


  ### 예제 3 – 배열 크기 검증
  ```c
  #include <assert.h>
  #include <string.h>

  static const char prefix[] = "Error No: ";
  #define ARRAYSIZE 14
  char str[ARRAYSIZE];

  static_assert(sizeof(str) > sizeof(prefix), "str은 prefix보다 커야 한다.");

  int main(void) {
    strcpy(str, prefix);
    return 0;
  }
  ```
  >  "컴파일 타임에" `prefix`보다 `str`이 더 커야 함을 보장하는 것.

 


  ### 런타임 어설션
  ` #define assert(스칼라-표현식) `
  스칼라 식이 0이면 실패한 호출에 관한 정볼를 표준 오류 스트림 stderr에 쓴다. 이후 abort 함수를 호출
  ```c
  void *dup_string(size_t size, char *str)
  {
    assert(size <= LIMIT);
    assert(str != NULL);

  }
  ```

  조건자 식은 실패한 어셜션 메시지로 나오므로 문자열 리터럴에 &&를 사용하면 실패할 때 추가 디버깅 정보를 보여 줄 수 있다.
  ```c
  void *dup_string(size_t size, char *str)
  {
    assert(size <= LIMIT && "size is larger than the expected limit");

    assert(str != NULL && "the caller must ensure str is not null");

  }
  ```


  ### **런타임 어설션 (`assert`)

  | 항목 | 내용 |
  |------|------|
  | 정의 위치 | `<assert.h>` |
  | 조건 형식 | 스칼라 타입 표현식 (ex. `int`, `char*`, `double` 등) |
  | 실패 시 동작 | `stderr`에 실패 메시지 출력 후 `abort()` 호출로 프로그램 강제 종료 |
  | 비활성화 조건 | `#define NDEBUG`를 정의하면 `assert()`는 아무 동작도 안 함 |
  | 조건식이 false일 때 출력되는 정보 | `조건식`, `__FILE__`, `__LINE__`, `__func__` (C99 이후) |


  매크로 구조 (C 표준)

  ```c
  #ifdef NDEBUG
  #define assert(condition) ((void)0)
  #else
  #define assert(condition) /* if (!(condition)) → 출력 + abort() */
  #endif
  ```

  즉:

  - `assert(x != NULL)`  
    → **x가 NULL이면 stderr에 메시지 출력 후 abort**


  🔹 추가 메시지를 넣는 테크닉

  ```c
  assert(("This must never be NULL", ptr != NULL));
  ```

  - `("문자열", 식)`은 **콤마 연산자**
  - **문자열은 평가되지 않지만**, assert 실패 시 메시지에 **"This must never be NULL"**이 함께 출력됨

  또는 더 흔하게 이렇게:

  ```c
  assert(ptr != NULL && "ptr must not be NULL");
  assert(size < 100 && "size exceeded maximum value");
  ```

  → 조건이 false일 때, **&& 뒤 문자열**이 에러 메시지로 출력됨 (GCC/Clang 기준)



  ```c
  void *dup_string(size_t size, char *str) {
      assert(size <= LIMIT && "size is larger than the expected limit");
      assert(str != NULL && "the caller must ensure str is not null");
  }
  ```

  - **LIMIT 초과**하거나 `str == NULL`이면  
    → `stderr`에 메시지 + **`abort()` 호출**
  - `assert()`는 디버깅 목적이므로 **배포 버전에서는 끄는 게 일반적**  
    → `#define NDEBUG` 정의

  ---
  ## ✅ 실행 예시 (GCC 기준)

  ### 코드
  ```c
  #include <assert.h>
  #include <stdio.h>

  int main() {
      int x = -1;
      assert(x > 0 && "x는 양수여야 합니다");
      printf("x = %d\n", x);
      return 0;
  }
  ```

  출력 (NDEBUG **정의 안 됨**)
  ```
  a.out: main.c:6: main: Assertion `x > 0 && "x는 양수여야 합니다"` failed.

  a.out: test_runtime_assert.c:6: main: Assertion `x > 0 && "x는 양수여야 합니다"' failed.
  Aborted (core dumped)
  ```

  출력 (NDEBUG **정의됨**)
  ```bash
  gcc -DNDEBUG ...
  ```

  → `assert()`는 아예 사라짐 → `x = -1` 출력만 나옴



아주 잘 정리했어!  
여기에 실제 개발 흐름과 실무 관점에서 컴파일러 플래그를 **목적별로 분류하고**,  
너가 작성한 내용을 기반으로 **명확하게 설명**을 덧붙여줄게.

---

## 컴파일러 설정 및 플래그 (GCC/Clang 기준)

  ### 📌 목적에 따른 분류

  | 목적 | 플래그 예시 | 설명 |
  |------|-------------|------|
  | **정적 분석/코드 검증** | `-Wall`, `-Wextra`, `-Werror`, `-pedantic`, `-std=c17` | 컴파일 타임 오류·경고를 최대한 잡기 위한 설정 |
  | **디버깅** | `-g3`, `-Og`, `-DDEBUG`, `assert()` | 디버깅 심볼 포함 + 코드 최적화 최소화 |
  | **성능 최적화/배포용** | `-O2`, `-O3`, `-march=native`, `-DNDEBUG` | 빠른 실행 성능에 중점. assert 제거, 디버깅 정보 없음 |
  | **보안 강화** | `-D_FORTIFY_SOURCE=2`, `-fstack-protector`, `-fPIE`, `-Wl,-z,relro` | 런타임에서 메모리 보호, 오버플로우 방지 등 |


  ### 🔸 `-O` 계열: **최적화 수준 설정**
  | 플래그 | 설명 |
  |--------|------|
  | `-O0` | 최적화 없음. **디버깅에 적합** |
  | `-Og` | 디버깅 친화적 최적화 (디버그+성능 타협) |
  | `-O2` | **일반적인 배포용 최적화 수준** |
  | `-O3` | 더 강한 최적화 (loop unrolling 등 포함, 사이즈 ↑) |
  | `-Ofast` | 성능 극대화 (정확성 무시 가능성 있음) |


  ### 🔸 `-g`, `-g3`: **디버깅 정보 포함**
  - `-g` : 기본 디버그 심볼 포함
  - `-g3`: `#define` 된 매크로 정보까지 포함 (더 많은 디버그 정보)

  ### 🔸 `-Wall`, `-Wextra`: **경고 활성화**
  - `-Wall`: 일반적인 대부분의 경고 활성화
  - `-Wextra`: 추가 경고 포함 (거의 필수)
  - `-Werror`: **경고를 오류로 간주**, 테스트/리팩토링 시 유용


  ### 🔸 `-std=c17`, `-std=gnu11` 등: **언어 표준 설정**
  - `-std=c17`: C17 표준 (엄격한 ISO 표준)
  - `-std=gnu17`: GNU 확장 포함된 C17 (GCC 기본값)
  - `-pedantic`: **표준을 위반하는 모든 코드에 경고** 발생


  ### 🔸 `-D_FORTIFY_SOURCE=2`: **보안 취약점 예방**
  - 컴파일 타임 + 런타임에 **버퍼 오버플로우 감지**
  - `-O1` 이상과 함께 동작해야 효과 있음


  ### 🔸 `-fPIE`, `-pie`, `-fPIC`, `-shared`: **ASLR/공유 라이브러리용**
  | 플래그 | 목적 |
  |--------|------|
  | `-fPIE`, `-pie` | 실행 파일을 **주소 공간 레이아웃 랜덤화(ASLR)** 지원 |
  | `-fPIC` | 공유 라이브러리에서 위치 독립 코드 생성 |
  | `-shared` | `.so` 공유 라이브러리 생성할 때 사용 |


  ### ✔ 디버깅용 빌드
  ```bash
  gcc -g3 -Og -Wall -Wextra -std=c17 -DDEBUG -o prog prog.c
  ```

  ### ✔ 분석/정적 검사용 빌드
  ```bash
  gcc -Wall -Wextra -Werror -pedantic -std=c17 -O0 -o prog prog.c
  ```

  ### ✔ 배포용 빌드
  ```bash
  gcc -O2 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector -o prog prog.c
  ```

  ### ✔ 보안 강화용 빌드 (PIE 포함)
  ```bash
  gcc -O2 -fPIE -pie -D_FORTIFY_SOURCE=2 -o secure_prog prog.c
  ```


## 단위 테스트 (Unit Testing)란

  > **단위(unit)** = 프로그램의 가장 작은 구성 요소 (보통 **함수** 단위)  
  > → 각 함수나 모듈이 **정상적으로 동작하는지 개별적으로 검증**하는 테스트


  | 이유 | 설명 |
  |------|------|
  | 🧪 개별 함수의 논리 검증 | 로직 오류, 엣지 케이스 등 빠르게 탐지 가능 |
  | 🔄 리팩토링 시 회귀 방지 | 코드를 바꿔도 동작이 깨지지 않았는지 확인 가능 |
  | 📦 모듈화/재사용성 ↑ | 인터페이스 명확화, 문서화 역할 |
  | ⚠️ 디버깅 시간 ↓ | 버그가 어디서 발생했는지 범위를 좁혀줌 |


  ### 단위 테스트의 특징

  | 항목 | 설명 |
  |------|------|
  | 독립성 | 각 테스트는 **독립적으로 실행 가능해야** 함 |
  | 반복 가능성 | 매번 같은 결과를 줘야 함 (비결정성 제거) |
  | 자동화 가능 | 테스트는 **스크립트나 CI 환경에서 자동 실행** 가능해야 함 |
  | 빠름 | 몇 초 내에 실행되어야 함 |


  ```c
  // 테스트 대상 함수
  int add(int a, int b) {
      return a + b;
  }

  // 단위 테스트 함수
  void test_add() {
      assert(add(2, 3) == 5);
      assert(add(-1, 1) == 0);
      assert(add(0, 0) == 0);
  }
  ```


  테스트 프레임워크 (C/C++ 기준)

  | 이름 | 특징 |
  |------|------|
  | **Unity** | C 언어용 경량 단위 테스트 프레임워크 |
  | **Check** | POSIX 기반 C 테스트 프레임워크 |
  | **CMocka** | 동적 메모리 테스트 지원 |
  | **GoogleTest (gtest)** | C++용 고급 테스트 프레임워크 |

  테스트 코드의 구성 패턴
  1. **테스트 대상 함수**
  2. **테스트 케이스 집합**
  3. **테스트 실행기 (main 함수 또는 테스트 러너)**


  예제 (C언어, assert만으로)

  ```c
  #include <assert.h>
  #include <stdio.h>

  int factorial(int n) {
      if (n < 0) return -1;
      if (n == 0) return 1;
      return n * factorial(n - 1);
  }

  void test_factorial() {
      assert(factorial(0) == 1);
      assert(factorial(1) == 1);
      assert(factorial(5) == 120);
      assert(factorial(-3) == -1);  // 예외 케이스
  }

  int main() {
      test_factorial();
      printf("All tests passed!\n");
      return 0;
  }
  ```


  ### CI와 통합

  - GitHub Actions, GitLab CI, Jenkins 등과 연동 가능
  - `make test` 같은 명령어로 자동 실행되도록 구성
  - 실패 시 빌드 중단


## ✅ 정적 분석 (Static Analysis)

  ### 📌 정의
  > 프로그램을 **실행하지 않고**, **소스코드 자체만 분석**하여  
  > **문법 오류, 스타일 위반, 보안 취약점, 메모리 오류 가능성** 등을 찾아내는 기법

  ### 🎯 목적
  - 컴파일 전에 버그와 취약점을 조기에 찾기
  - 스타일, 가이드라인 위반 점검 (MISRA-C, CERT-C 등)
  - 코드 품질 향상

  ### 🔧 주요 도구
  | 도구 | 설명 |
  |------|------|
  | `cppcheck` | C/C++ 정적 분석 도구, 메모리 누수 가능성, 미사용 변수 등 |
  | `clang-tidy` | Clang 기반 C++ 분석 도구 (모던 C++ 추천 포함) |
  | `splint` | C 언어 분석 도구, 타입 오류, 경고 가능성 |
  | `gcc -Wall -Wextra` | 컴파일러의 경고를 정적 분석처럼 활용 |
  | `sonarqube` | 정적 분석 서버 플랫폼 (CI 통합) |
  | `coverity` | 산업계에서 많이 쓰는 정적 분석 플랫폼 |

  ### 💡 예시
  ```c
  int a;
  printf("%d\n", a); // 초기화되지 않은 변수 → 경고

  char buf[10];
  strcpy(buf, input); // buffer overflow 가능성
  ```

  ### ✅ 장점
  - 실행 없이 빠르게 분석
  - 자동화 쉬움 (CI에 붙이기 좋음)
  - 광범위한 코드 스타일 분석 가능

  ### ❌ 단점
  - **실행 시간의 실제 동작은 반영 못함**
  - false positive (거짓 경고) 많을 수 있음

  ---

  ## ✅ 동적 분석 (Dynamic Analysis)

  ### 📌 정의
  > 프로그램을 **실제로 실행(run)하면서**  
  > **메모리 사용, 런타임 동작, 성능, 오류** 등을 분석하는 기법

  ### 🎯 목적
  - 런타임에 발생하는 실제 버그나 충돌 추적
  - **세그멘테이션 오류**, **메모리 누수**, **성능 병목** 발견
  - 프로그램 흐름 및 변수 상태 실시간 확인

  ### 🔧 주요 도구
  | 도구 | 설명 |
  |------|------|
  | `gdb` | GNU 디버거: 브레이크, 변수 확인, 백트레이스 |
  | `valgrind` | 메모리 누수, 잘못된 접근 등 탐지 |
  | `strace` | 시스템 콜 추적 |
  | `perf`, `gprof` | 성능 분석 도구 |
  | `asan` / `ubsan` | Address Sanitizer, Undefined Behavior Sanitizer |

  ### 💡 예시
  ```bash
  valgrind ./my_program
  == Memory leak detected ==

  gdb ./my_program
  (gdb) run
  (gdb) print score
  ```

  ### ✅ 장점
  - **실제 동작 확인 가능**
  - 런타임 버그 (세그폴트, 할당 오류 등) 추적에 강력
  - 디버깅/최적화에 필수

  ### ❌ 단점
  - 실행 가능한 환경이 필요함
  - 성능 저하 발생 가능 (특히 valgrind)
  - 자동화에 한계가 있음


## 실습

[1] 코드 작성

    ↓

[2] 정적 분석: cppcheck

    cppcheck --enable=all --inconclusive --std=c99 --language=c src include

[3] 컴파일: -Wall -Wextra -Werror

    make clean
    make CFLAGS="-Wall -Wextra -Werror -Iinclude" CXXFLAGS="-std=c++17 -Wall -Wextra -Werror -Iinclude -Ithird_party/googletest/include -Ithird_party/googletest"

[4] 유닛 테스트: GoogleTest, test.cpp

    make run

[5] 동적 분석: gdb로 디버깅 or valgrind로 메모리 확인

    gdb ./test_motor
    valgrind --leak-check=full ./test_motor

[6] 통과 → Git commit, PR

    cd ~/study/C_Study/Effective_C/11_debug_test_analyse/gtest_make_demo/
    git init
    git add .
    git commit -m "✅ Implement clamp_speed with tests, static/dynamic analysis"

