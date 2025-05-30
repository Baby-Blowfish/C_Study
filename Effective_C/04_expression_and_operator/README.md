# 식과 연산자
> 연산자(operator) : 연산하는 데 사용되는 키워드나 하나 이상의 문장 부호(punctuation)문자

> 식(expreesion) : 연산자가 하나 이상의 피연산자에 적용되어 값을 계산하거나 파생 작업이 발생하면 식, 연산자와 피연산자의 시퀸스

> 피연산자 : 식별자와 상수, 문자 리터럴, 다른 식

## 단순 할당
> simple assignment : 왼쪽 피연산자로 지정한 개체의 값을 오른쪽 피연산자의 값으로 대체, 오른쪽 피연산자의 값은 할당식의 형식으로 변환

> 피연산자 =(할당연산자) 피연산자

```c
int i = 21; // 초기화 선언, 이니셜라이저 
int j = 7;  // 할당식은 아님
i = j;  // 단순 할당
```

  ### l-value와 r-value란?

  | 구분 | 의미 | 기억 방법 | 예시 |
  |------|------|-----------|------|
  | **l-value** | 메모리 주소를 가지는 **식별 가능한 개체** | "왼쪽에 올 수 있음" | 변수 `i`, 배열 원소 `arr[0]`, 포인터 역참조 `*p` |
  | **r-value** | **값 그 자체**, 메모리 주소와 직접 연결되지 않음 | "오른쪽에만 올 수 있음" | `5`, `i + 3`, `x * y`, 함수 반환값 |


  ### 더 정확한 정의 (C 표준에 가까운 설명)

  - **l-value (locator value)**: 메모리 내 어떤 **위치(location)**를 **지칭**하는 값.
  - **r-value (read value)**: 연산에 사용되는 **실제 값**으로, **메모리 주소가 없어도 되는** 값.


  ```c
  int i = 5;  // i는 l-value, 5는 r-value
  ```
  - `i`: 메모리 상의 주소를 가진 변수 → **l-value**
  - `5`: 그냥 값 → **r-value**

  ```c
  j = i + 12;
  ```
  - `i`: l-value인데, **r-value로 자동 변환되어 사용됨**
  - `i + 12`: 연산 결과이므로 **r-value**
  - `j`: **l-value**, 결과값(r-value)을 받아 저장

  ```c
  7 = i;  // ❌ 컴파일 에러
  ```
  - `7`은 **r-value**이므로 왼쪽에 올 수 없음
  - 할당식에서 왼쪽은 반드시 **l-value**여야 함


  | 사용 위치 | 요구 타입 | 설명 |
  |-----------|-----------|------|
  | 할당식 왼쪽 | **l-value** | 주소가 있어야 값을 저장할 수 있음 |
  | 할당식 오른쪽 | **r-value 또는 l-value** | 값으로 평가되기만 하면 OK |
  | `&` 연산자 | l-value만 가능 | 주소를 가져오려면 위치가 있어야 함 |

  ```c
  signed char c;
  int i = INT_MAX;
  long k;
  k = (c = i);  // 분석해봅시다
  ```
  1. `i`: l-value  
  2. `c = i`: `i`는 r-value로 변환되어 `c`에 할당됨  
    - 여기서 `i` 값은 `signed char`로 변환됨 → 오버플로우 발생 가능 (`c`에 저장됨)
  3. `k = (c = i)`: 괄호 안 전체는 **할당식 → l-value → r-value로 평가 가능**
    - 최종적으로 `c`의 값이 `long` 타입으로 변환되어 `k`에 할당됨


  ### l-value → r-value 변환

  ```c
  int x = 5;
  int y = x;  // x는 l-value이지만, 이 자리에선 r-value로 쓰임
  ```
  → 즉, **주소로 식별 가능한 개체(l-value)**를 **값(r-value)**로 **자동 변환**하는 것


  ```c
  int i = 5;
  int j = i + 3;
  ```
  | 표현 | 종류     | 의미                 |
  |------|----------|----------------------|
  | `i`  | l-value  | 메모리에서 주소 가진 변수 |
  | `5`  | r-value  | 값 그 자체           |
  | `i + 3` | r-value | 연산 결과 값 (주소 없음) |
  | `j` | l-value | 값을 저장할 변수 (주소 있음) |

## 평가
> 식을 단일 값으로 단순화 하는것

> 값계산과 파생 작업의 시작을 포함

  ### 값계산 (value computation)
  - 식 평가의 결과값을 계산하는것
  - 개체의 정체성 결정이나 이전에 개체에 할당된 값 읽기 포함
  
    ```c
    a[i] + f() + 9
    ```
  - 피연산자의 값 계산은 연산자의 결과값 계산 전에 이루어져야 한다.

  ### 파생작업 (side effects)
  - 값 계산 이외의 모든 작업
  - 개체에 쓰거나 volatile 한정 형식의 개체에 대한 접근, 입출력, 할당, 함수 호출등이 있다.

## 함수 호출
- 함수 지정자의 주소를 평가
- 각 인수도 개별적으로 평가
  - 인수 평가 순서는 미정의
  - f(x++, ++x)의 결과는 컴파일러마다 다르다!
- 함수 호출
  - 지역 변수 생성
  - 인수 복사
  - 본문 실행
  - 리턴값 계산

  ### 함수 지정자 (function designator)
    - 함수 형식을 갖고 함수를 호출하는 데 사용되는 식
    ```c
    int x = 11;
    int y = 21;
    int max_of_x_and_y = max(x, y); // max는 함수 지정자
    ```
    - 함수 지정자는 컴파일 시 함수 반환 형식에 대한 포인터로 변환됨
    - 각 인수 값은 해당 매개 변수 형식의 개체 할당 할 수 있는 형식이어야 함
    - 인수의 개수와 형식은 함수에서 받아들이는 매개변수의 개수 및 형식과 일치해야함
    - 가변 개수의 인수를 허용하는 가변 인수 함수를 지원
    - max : 함수 지정자 -> 자동으로 함수 포인터로 변환됨 int(*)(int, int)
    - &max : 함수 주소를 명시적으로 취한 것 -> 동일한 함수 포인터 타입
    ```c
    int f(void)
    {
      return 0;
    }

    void g(int (*func)(void))
    {
      if(func() != 0)
        printf("g failed\n");
    }

    g(f);  // f는 함수 지정자에서 함수 포인터로 변환됨 함수 포인터 인수로 g를 호출
    ```
    ```c
    int max(int a, int b) {
        return a > b ? a : b;
    }

    int x = 11;
    int y = 21;
    int m = max(x, y);
    ```
    - x, y는 각각 int로 평가 → r-value

    - max(x, y) 호출 시:

      함수 이름 max → 함수 포인터로 암시적 변환

      인수 x, y → 각각 평가된 후 복사되어 전달됨

    - 정적 타입 검사 수행: 인수 개수와 타입이 함수 정의와 맞는지 확인

## 증가 및 감소 연산자
- ++ : 증가 연산자
- -- : 감소 연산자
- 수정할 수 있는 l-value를 각각 증가시키거나 감소시킴, 단항 연산자
- 접두사 연산자(prefix operator) : 값을 반환하기 전에 연산, c++에서는 l-value로 평가 될수 있음 거의 r-value로 평가됨
- 접미사 연산자(postfix operator) : 값을 반환한 다음에 연산, 평가는 r-value
- 
  ```c
  int i = 5;
  int e;  // 표현식의 결과
  e = i++; // 접미사 증가 : i = 6, e = 5
  e = i--; // 접미사 감소 : i = 5, e = 4
  e = ++i;  // 접두사 증가 : i = 7, e = 7
  e = --i;  // 접두사 감소 : i = 4, e = 4
  ```
## 연산자 우선순위 및 결합성
- 연산자 우선순위 : 주어진 식에서 수행해야 하는 연산의 순위를 지시하는 규칙
- 결합성 : 명시적인 괄호를 사용하지 않을 때 우선순위가 같은 연산을 그룹화하는 방법을 결정
  ### 왼쪽 결합성 연산자
  - 연산을 왼쪽에서 오른쪽으로 그룹화
  ### 오른쪽 결합성 연산자
  - 연산을 오른쪽에서 왼쪽으로 그룹화


  ### 연산자 우선순위 및 결합성 표
  | 우선순위 | 연산자 | 설명 | 결합성 |
  |:--:|:--|:--|:--:|
  | 1 | `()` `[]` `->` `.` | 함수 호출, 배열 접근, 구조체 멤버 접근 | **왼 → 오** |
  | 2 | `++` `--` (후위) | 후위 증감 | **왼 → 오** |
  | 3 | `+` `-` `!` `~` `++` `--` `*` `&` `(type)` `sizeof` `_Alignof` | **단항 연산자**: 부호, 논리부정, 비트부정, 전위 증감, 역참조, 주소 연산, 형변환 등 | **오 → 왼** |
  | 4 | `*` `/` `%` | 곱셈, 나눗셈, 나머지 | **왼 → 오** |
  | 5 | `+` `-` | 덧셈, 뺄셈 | **왼 → 오** |
  | 6 | `<<` `>>` | 비트 시프트 | **왼 → 오** |
  | 7 | `<` `<=` `>` `>=` | 관계 연산자 | **왼 → 오** |
  | 8 | `==` `!=` | 등가/부등 | **왼 → 오** |
  | 9 | `&` | 비트 AND | **왼 → 오** |
  | 10 | `^` | 비트 XOR | **왼 → 오** |
  | 11 | `\|` | 비트 OR | **왼 → 오** |
  | 12 | `&&` | 논리 AND | **왼 → 오** |
  | 13 | `\|\|` | 논리 OR | **왼 → 오** |
  | 14 | `?:` | 조건(삼항) 연산자 | **오 → 왼** |
  | 15 | `=` `+=` `-=` `*=` `/=` `%=` `<<=` `>>=` `&=` `^=` `|=` | 대입 연산자 | **오 → 왼** |
  | 16 | `,` | 콤마 연산자 | **왼 → 오** |


## 평가 순서 
> C 연산자의 피연산자에 대한 평가 순서는 일반적으로 지정되어 있지 않다.
  ```c
  int glob;
  int f(void)
  {
    return glob + 10;
  }

  int g(void)
  {
    glob = 42;
    return golb;
  }

  int main(void)
  {
    int max_value = max(f(),g());
  }
  ```
- 전역 변수 glob는 공유 상태
- max함수의 인수 평가 순서에 따라 42 or 52 반환
- 실행이 인터리브(interleave) 하지 않음

  ```c
  int f_val = f();
  int g_val = g();
  int max_value = max(f_val, g_val);
  ```
- 순차적으로 계산되는 것을 보장

  ```c
  printf("%d\n", ++i + ++j * --k);
  ```
  ### 용어 정리
  | 용어 | 한국어 | 의미 |
  |------|--------|------|
  | **sequence point** | 시퀀스 포인트 | 어떤 표현식의 **앞/뒤로 연산이 반드시 완료되는 시점** |
  | **unsequenced evaluation** | 비순차 평가 | 피연산자들 간에 **누가 먼저 평가될지 정해지지 않음** |
  | **unspecified order** | 순서 미정의 | 둘 중 **무엇이 먼저 실행될지** 정해져 있지 않음 |
  | **undefined behavior** | 정의되지 않은 동작 | 프로그램 동작 자체가 **예측 불가능** (버그 가능성) |

  ```c
  a = ++i + i++;
  ```

  - `++i`: i를 증가시키고 사용 → **부작용 발생**
  - `i++`: i를 사용하고 증가시킴 → **부작용 발생**

  ➡ 이 둘 사이에는 **시퀀스 포인트가 없음**
  ➡ 평가 순서도 **정해지지 않음**
  ➡ 동일 변수(i)에 **두 번 이상 부작용**
  ➡ **undefined behavior (정의되지 않은 동작)** 발생 ⚠️


  ### Sequence Point (시퀀스 포인트)

  > **C에서 어떤 연산이 끝나고, 그 이후의 연산이 반드시 그 결과를 본다는 “중간 지점”**

  즉, **그 지점 전까지의 모든 부작용이 반드시 끝나야 한다**.

  ```c
  i = 0;
  i++;    // i == 1
  ```

  ```c
  i = 1;
  j = (i++) + 5;  // i++ 실행 후 i는 2, j는 6
  ```

  ```c
  func1(), func2();  // 함수 호출 후 콤마 연산자는 시퀀스 포인트!
  ```

  ```c
  if (x) { ... }     // 조건 평가 끝나야 블록 실행 가능 → 시퀀스 포인트
  ```

  ```c
  a = b;  // = 자체는 시퀀스 포인트가 아님!
  ```


  ### 비순차 평가 (Unsequenced Evaluation)
  > **연산자 피연산자 사이에 누가 먼저 실행될지 정해지지 않음**

  ```c
  printf("%d\n", ++i + ++j * --k);
  ```

  - `++i`, `++j`, `--k` 중 **누가 먼저 실행될지 모름**
  - 하지만 서로 다른 변수니까 → 위험은 **없음**

  ➡ 이것은 **비순차 평가**지만, **UB는 아님**



  ### 정의되지 않은 동작 (UB)

  ```c
  int i = 1;
  int x = i++ + ++i;
  ```

  - `i++`: 사용 후 증가 (부작용)
  - `++i`: 먼저 증가 (부작용)
  - `i`라는 **하나의 변수에 두 번 부작용** + **시퀀스 포인트 없음**

  ➡ **undefined behavior**  
  ➡ 컴파일러마다 결과 다름, 최악은 프로그램 이상

## sizeof 연산자
  - size_t형식의 부호 없는 정수 반환, #include <stddef.h> 또는 #include <stdio.h>에서 정의됨, 항상 양의 정수
  - 컴파일 타임 연산 : 대부분의 경우 컴파일 타임에 평가됨
  - 값이 아님	: sizeof는 연산자이지 함수가 아님
  - 괄호 생략 가능	: sizeof x ← x가 변수면 괄호 생략 가능
  - 평가 안 함	: 표현식을 sizeof 안에 넣어도 실행은 안 됨 (side effect 없음)
  - 
  ```c
  sizeof(type)        // 타입의 크기
  sizeof(expression)  // 표현식의 결과값의 타입 크기
  sizeof(int)         // 4 (32bit 시스템 기준)
  sizeof(x)           // 변수 x의 타입 크기
  sizeof(x + 1)       // x + 1의 결과 타입 크기 (연산 결과에 따라 달라짐)
  int i = 10;
  sizeof(i++);  // 컴파일 타임에 i의 타입을 평가 → i는 증가하지 않음
  printf("%d\n", i); // 여전히 10
  sizeof(void*)   // 64bit기준 8byte
  int arr[10];
  sizeof(arr);         // 10 * sizeof(int) → 예: 40
  sizeof(&arr);        // 포인터의 크기 → 예: 8
  sizeof(arr[0]);      // int 하나 → 4
  struct S {
      char a;
      int b;
  };
  sizeof(struct S);  // 예: 8 (패딩 포함)
  int *p;
  sizeof(p);      // 보통 8 (64bit 시스템에서 포인터는 8바이트)
  sizeof(*p);     // p가 가리키는 대상 크기 → int → 4
  int f();
  sizeof(f);     // ⚠️ 오류! 함수는 크기를 측정할 수 없음
  sizeof(&f);    // 함수 포인터 크기 → 8
  sizeof(3);     // 3은 int → 결과: 4
  sizeof(3.0);   // 3.0은 double → 결과: 8
  sizeof('A');   // 문자 리터럴 → int → 결과: 4

  void bar(int (*arr)[10]) {
      printf("sizeof in bar: %lu\n", sizeof(*arr));  // *arr은 배열 전체 → 40
  }

  void foo(int arr[10]) {
      printf("sizeof in foo: %lu\n", sizeof(arr));   // decay → pointer → 8
  }

  void foop(int *arr) {
      printf("sizeof in foop: %lu\n", sizeof(arr));  // pointer → 8
  }

  int main() {
      int arr[10];


      foo(arr);              // 8
      foop(arr);             // 8
      bar(&arr);             // 40 — 배열 전체를 포인터로 전달

      printf("sizeof in main: %lu\n", sizeof(arr));  // 40

      return 0;
  }
  ```

  ### decay
  > c에서 배열이 자동으로 포인터로 변환되는 현상
  - 배열 이름이 표현식에 들어가는 순간 자동으로 그 배열의 첫 번쨰 요소의 주소로 변환됨
  - arr -> &arr[0]
  - 대입, 함수인자, 산술연산, 비교연산, 반환값
  - sizeof(), &, _Alignof, typeof(), 초기화 시
  ```c
  int arr[5] = {1, 2, 3, 4, 5};
  int *p = arr;       // decay 발생 → arr → &arr[0]
  ```
    arr은 사실 int[5] 타입
    그런데 int *p에 대입하려고 하니까
    → C가 arr을 자동으로 int*로 변환
    → 정확히는 &arr[0]로 decay
  - 대입, 함수 인자, if() 비교, arr + 1 연산
  - sizeof(arr), &arr 에서는 발생하지 않음
    | 항목 | `arr` | `&arr` |
    |------|-------|--------|
    | 의미 | 첫 요소 주소 | 배열 전체 주소 |
    | 타입 | `int *` | `int (*)[5]` |
    | `+1` 시 이동량 | `4 bytes` (int 하나) | `20 bytes` (배열 전체) |
    | `sizeof` | 배열 전체 크기 (20) | 포인터 크기 (8) |
    | 함수 인자 전달 | `int *` | `int (*)[5]` |


  - `sizeof`로 배열 크기를 구할 수 없는 이유
  ```c
  void foo(int arr[]) {
      printf("%lu\n", sizeof(arr));  // ❌ 40 아님! 8 나옴
  }
  ```
  - 배열 이름 `arr[]`은 함수 인자로 받을 때 **자동으로 decay되어** `int* arr`가 됨
  - 그래서 `sizeof(arr)`는 배열이 아니라 **포인터의 크기**만 측정됨
  - 일반적으로 `sizeof(int*)` → **8바이트** (64비트 시스템 기준)

  - 반면, main 함수에서는?
  ```c
  int arr[10];
  printf("%lu\n", sizeof(arr));  // ✅ 40 (10 * 4)
  ```
  - 여기서는 `arr`이 **진짜 배열 타입(int[10])** 이므로 decay되지 않고
  - `sizeof(arr)` = **배열 전체 크기 = 요소 크기 × 개수**

  - 해결 방법: 배열 포인터 사용
  ```c
  void foo(int (*arr)[10]) {  // 배열 포인터로 받기
      printf("%lu\n", sizeof(*arr));  // ✅ 40
  }
  ```
  - `*arr`은 `int[10]` 타입 → 배열 크기 유지됨

  - decay 때문에 생기는 함수 인자 문제
  ```c
  void print_length(int arr[]) {
      size_t len = sizeof(arr) / sizeof(arr[0]);  // ❌ 항상 2 (8/4)
      printf("len = %zu\n", len);
  }
  ```
  - `arr[]` → `int* arr`로 decay
  - `sizeof(arr)` = `sizeof(int*)` → 8 (64비트 시스템)
  - `sizeof(arr[0])` = 4  
  → 8 / 4 = **2** ← ❌ 실제 배열 길이 아님

  - 배열 크기를 별도로 넘겨라
  ```c
  void print_length(int *arr, size_t len) {
      printf("len = %zu\n", len);
  }
  ```


  - 2차원 배열에서 decay는 한 번만 일어난다
  ```c
  int arr[3][5];
  ```
  - `arr`의 타입: `int[3][5]`
  - decay 순서
    | 표현 | 타입 |
    |------|------|
    | `arr` | `int[3][5]` |
    | `arr` → decay | `int (*)[5]` ← 3개의 행 중 첫 행의 **주소** |
    | `arr[0]` | `int[5]` |
    | `arr[0]` → decay | `int*` ← 첫 번째 행의 첫 번째 요소의 주소 |

  - 함수로 넘겨보자
  ```c
  void foo(int arr[][5]) {
      printf("%lu\n", sizeof(arr));  // ❌ 8
      printf("%lu\n", sizeof(arr[0]));  // ✅ 20
  }
  ```
  - `arr`은 decay되어 `int (*)[5]`
  - `arr[0]`은 `int[5]`, `sizeof(arr[0])` = 20

  - 포인터 배열과 배열 포인터의 차이
  ```c
  int *a[3];     // 포인터 배열: 3개의 int* 포인터
  int (*b)[3];   // 배열 포인터: int[3]의 주소
  ```
  | 표현 | 의미 |
  |------|------|
  | `int *a[3]` | `a`는 배열, 요소는 `int*|
  | `int (*b)[3]` | `b`는 포인터, 가리키는 대상이 `int[3]` |

  ```c
    #include <stdio.h>

  // [1] 함수: 2차원 배열을 decay된 포인터로 받음
  void decay2D(int arr[][3]) {
    // decay : int [][3] -> int (*)[3] : 1차원 배열 int[3]을 가리키는 포인터
    printf("[decay2D] sizeof(arr) = %lu\n", sizeof(arr));       // (int (*)[3] 포인터 이므로 -> 8
    printf("[decay2D] sizeof(arr[0]) = %lu\n", sizeof(arr[0])); // int[3] -> 첫번째 행 -> 12(4*3)
    printf("[decay2D] arr[1][2] = %d\n", arr[1][2]); // 실제 값 확인용    
  }

  // [2] 함수: 배열 포인터로 받음
  void array_ptr(int (*arr)[3]) {
      // int (*)[3]
      printf("[array_ptr] sizeof(*arr) = %lu\n", sizeof(*arr));   // int[3] -> 12(4*3)

    // 배열 포인터로 역참조해서 값 출력
    printf("[array_ptr] (*arr)[2] = %d\n", (*arr)[2]); // 첫 번째 행의 세 번째 값
  }

  // [3] 함수: 포인터 배열 받기
  void pointer_array(int *arr[3]) {
      // decay : int *[3] -> int ** : 정수 포인터를 가리키는 포인터
      printf("[pointer_array] sizeof(arr) = %lu\n", sizeof(arr)); // int** -> 8
          // 포인터 배열 dereference → arr[2]는 포인터, *arr[2]은 값
    printf("[pointer_array] *arr[2] = %d\n", *arr[2]); // arr[2]가 가리키는 값
  }

  // [4] 함수: 이중 포인터 받기
  void double_ptr(int **p) {
      // int ** : 정수 포인터를 가리키는 포인터
      printf("[double_ptr] sizeof(p) = %lu\n", sizeof(p));        // int** -> 8
          // 이중 포인터 역참조
    printf("[double_ptr] *p[2] = %d\n", *p[2]); // p[2]가 가리키는 값
  }

  int main() {
      int arr2D[2][3] = {{1,2,3}, {4,5,6}}; // int[2][3] => 2행 3열의 2차원 배열, 일반 표현식에서는 decay되어 int (*)[3]이 된다.
      // arr[i] : int[3]
      // arr[i][j] : int

      int (*p)[3] = arr2D;    // 배열 포인터    decay  : 2차원 배열 int[2][3] -> 첫번째 행의 포인터 int(*)[3] 
      int *q = arr2D[0];      // 포인터        decay  : 1차원 배열 int[3]    -> 첫번째 행의 첫 요소의 주소 int *
      int *q1 = arr2D[1];     // 포인터        decay  : 1차원 배열 int[3]    -> 두번째 행의 첫 요소의 주소 int *
      int x = arr2D[1][2];    // int형 변수    decay  : int형 변수 int       -> 두번째 행의 세번째 요소 int
      int *ptrs[3];         // 포인터 배열 (3개의 int* 슬롯)
      int **pp;             // 이중 포인터

      // 포인터 배열 초기화
      for (int i = 0; i < 3; i++) {
          ptrs[i] = &arr2D[0][i];
      }
      pp = ptrs;

      // 배열 크기 확인
      printf("[main] sizeof(arr2D) = %lu\n", sizeof(arr2D));              // decay 발생 x -> int[2][3] -> 24(4*2*3)
      printf("[main] sizeof(arr2D[0]) = %lu\n", sizeof(arr2D[0]));        // decay 발생 x -> int[3] -> 12(4*3)
      printf("[main] sizeof(arr2D[0][0]) = %lu\n", sizeof(arr2D[0][0]));  // decay 발생 x -> int -> 4
      printf("[main] sizeof(&arr2D) = %lu\n", sizeof(&arr2D));            // decay 발생 x -> int (*)[2][3] -> 8 (배열 전체 주소)
      // 함수 호출
      decay2D(arr2D);         // 2차원 배열 int [2][3]   -> decay 이후 : int (*)[3]
      array_ptr(&arr2D[1]);   // 배열 포인터 int (*)[3] 넘겨 주려면 -> arr2D[1] 주소를 넘겨줘야함,   
      // pointer_array(); 인수는 포인터 배열이므로 -> int *[3] 포인터 배열의 주소를 넘겨줘야함
      // 그런데 arr2D는 배열 포인터는 되지만 포인터 배열이 될 수 없음
      // 그래서 포인터 배열 ptrs를 만든거임
      pointer_array(ptrs);    // 포인터 배열 int *[3]    -> decay 이후 : int **
      double_ptr(pp);         // 이중 포인터 int **

      return 0;
  }
  ```
  


## 산술 연산자

### 단항 연산자 +와 -
  - 단일 피연산자에 대해 연산한다.
  - 양수와 음수를 표현
  - 정수 형식이면 연산 결과는 확장된 형식
  - ```-25``` 음의 정수 상수는 없다, 실제로는 단항연산자 앞에 25가 있는 int형식의 r-value이다.

### 논리 부정 연산자
  - 단항 논리 부정 연산자 !
  - 피연산자의 값이 0이 아니면 결과는 0
  - 피연산자의 값이 0이면 결과는 1
  - int형식

### 곱하기 연산자
  - 이항 곱하기 연산자 : *, /, %
  - 일반 산술 변환은 곱하기 피연산자에 대해 암시적으로 수행됨
  - 나머지는 정수 피연산자에 대해서만 동작
  - 유클리드, 하한, 자르기 등의 정수 나눗셈이 있지만 C에서는 잘라내기 나눗셈을 구현
  - 잘라내기 나눗셈 : 연산자의 결과는 분수부분이 삭제된 대수적 몫이다. == 0 방향으로 잘라내기
  - 나머지와 피제수는 항상 같은 부호를 갖는다.
  ```C
  bool is_odd(int n)
  {
    return n % 2 == 1;
  } // 음수에서는 나머지와 피제수가 같은 부호를 가지므로 음수이자 홀수 일때 -1이 되어 false로 판명됨

  bool is_odd(int n)
  {
    return n % 2 != 0;
  } // 따라서 0의 나머지는 나뉠 수의 부호에 상관 없이 같으므로 나머지가 0인지 확인하는게 정확한 방법

  bool is_even(int n)
  {
    return n % 2 == 0;
  } 
  ```

## 비트 연산자
> bitwise operator : 개체의 비트나 정수의 표현을 조작할 수 있다. (| & ^ ~)

> bitmap을 표현하는 개체에 사용된다. 각 비트는 무언가 켜짐이나 꺼짐, 활성화됨이나 비활성화됨 등등

> 부호 비트가 비트맵 안에서는 값으로 사용될 수 있으며로 비트맵은 부호가 없는 정수 형식을 가장 잘 표현함

  ### 보수 연산자
  - 단항 보수 연산자 : ~ 정수 형식의 단일 피연산자에 대해 작동하고 피연산자의 비트 보수(원래 값의 각 비트가 뒤바뀐 값)을 반환
  - POSIX umask : 파일의 권한 모드는 마스크의 보수와 프로세서가 요청한 권한모드 설정간의 논리 AND 연산의 결과
  - 피연산자에 대해 정수 확장이 수행되고 결과는 확장된 형식
  ```C
  unsigned char uc = UCHAR_MAX;
  int i  = ~uc;
  ```
  - uc가 ~연산자의 피연산자로 사용되면 uc는 0확장을 통해 32비트 signed int로 확장되 0x000000FF가 된다. 이 값의 보수는 0xFFFFFF00이다
  - 이러한 결과를 방지하기 위해 모든 비트 조작은 충분히 넓은 부호가 없는 정수 형식을 사용하는게 좋다.

  ### 시프트 연산자
  - 정수 형식의 피연산자 각 비트의 값을 지정된 위치 수만큼 시프트한다.
  ``` 시프트 식 << 추가식     시프트식 >> 추가식```
  - 시프트 식 : 시프트할 값
  - 추가 식 : 값을 시프트할 비트수
  - e1 << e2
    - 비워진 비트는 0으로 채워짐
    - 시프트 식이 부호가 없는 형식이거나 부호가 있는 형식에서 음수가 아니면 결과값은 e1 = e1 * 2^e2 
    - 그렇지 않으면 정의되지 않은 동작
  - e1 >> e2
    - 시프트 식이 부호가 없는 형식이거나 부호가 있는 형식에서 음수가 아니면 결과값은 e1 = e1 / 2^e2
    - 시프트 식이 부호가 있는 형식이고 음수이면 결과값은 구현체에 정의된 값으로 산술시프트이거나 논리 시프트 중 하나이다
    - 산술 시프트는 비워진 비트를 1으로 채움
    - 논린 시프트는 비워진 비트를 0으로 채움
  - 피연산제에 대해서 정수 확장 수행, 결과 형식은 확장된 원쪽 피연산자의 형식
  - 피연산자의 비트 수가 음수이거나 피연산자의 너비보다 크거나 같은 경우는 정의되지 않은 동작 -> 시프트할 비트수는 항상 0보다 크거나 피연산자의 너비보다 작아야함
  - 2의 거듭제곱으로 곱하거나 나눌경우 시프트 연산 사용한다면 사용자가 조기 최적화를 하는것임 -> 컴파일러가 최적화할 시기를 결정하는게 가장 좋으므로 웬만하면 / * 사용
  ```C
  extern int si1, si2, sresult;
  extern unsigned int ui1, ui2, uresult;

  if ( (si2 < 0) || (si2 >= sizeof(int)*CHAR_BIT))
  {
    // 에러
  }
  else
  {
    sresult = si1 >> si2;
  }

  if ( ui2 >= sizeof(unsigned int)*CHAR_BIT)
  {
    // 에러
  }
  else
  {
    uresult = ui1 >> ui2;
  }
  ```
  ### 비트 AND 연산자
  > `&` 두 피연산자에 대한 비트 AND 결과를 반환

  ### 배타적 OR 연산자
  > `^` 두 피연산자에 대한 배타적 OR 결과를 반환

  ### 비트 포괄적 OR 연산자
  > `|` 두 피연산제에 대한 비트 포괄적 OR 결과를 반환

## 논리 연산자
> `&&` `||` 스칼라 형식의 두 개 이상의 식을 논리적으로 결합하는데 주로 사용

- `&&` : 두 피연산자가 모두 0이 아니면 1을 반환 그렇지 않으면 0을 반환
- `||` : 두 피연산자 중 하나가 0이 아니면 1을 반환 그렇지 않으면 0을 반환
- 피 연산자가 0과 1이외의 값을 가진다면 0과 같지 않음이라고 정의
- 피연산자는 스칼라 형식(정수, 부동소수점, 포인터)를 허용 연산결과는 int
- 왼쪽에서 오른쪽으로 평가를 보장
- 두번째 피연산자를 평가했다면 첫 번째 평가와 두 번째 피연산자 간에 시퀸스 포인트가 있음
- 논리 연산자 단락 평가 : 첫번째 피연산자를 평가해 결과를 추론할수 있다면 두 번째 피연산자를 평가하지 않는다.
```C
bool inN(int* ptr, int n)
{
  return ptr && *ptr == n; // ptr이 NULL이면 null포인터를 역참조 하지 않도록 두번째 && 피연산자를 평가하지 않는다.
}
```
```c
is_file_ready() || perpare_file() //is_file_ready()는 파일이 준비되면 true반환 -> 파일 준비를 할 필요가 없으므로 두 번째 || 피연산자의 평가되지 않는다 
// 파일이 준비 됐는지 결정하는 비용은 파일을 준비하는 비용보다 적다. -> 불필요한 컴퓨팅 방지
```
- 두번째 피연산자에 파생 작업이 있는지 주의해야한다.
```c
enum { max = 14};
int i = 17;

if((i => 0) && ( (i++) <= max))
{
  // 만약 i가 음수라면 i를 1증가시키려는 의도로 해석되면 && 두번째 피연산자의 경우 평가되지 않으므로 파생작업이 실행되지 않는다.
}
```

## 형 변환 연산자
> cast, type cast : 명시적으로 한 형식의 값을 다른 형식의 값으로 변환 : `(타입)`
- 명시적 형변환
- 포인터 형식 <-> 부동소수점 형식 변환 불가

## 조건부 연산자
> ` 조건 ? 식1 : 식2 ` 세 개의 피연산자 사용
- 조건이 참이면 식1, 거짓이면 식2의 값을 반환
- 첫번째 피연산자인 조건을 평가하고 참이면 두번째 피연산자인 식1를 평가하고 그렇지않고 거짓이면 세번째 피연산자인 식2를 평가한다.
- 첫번째 피연산자의 평가와 두번째와 세번째 피연산자를 평가하기 전에 시퀸스 포인트가 있다.
- is-else 제어 흐름과 비슷하지만 함수처럼 값을 반환 한다.
- 결과는 두번째와 세번째 피연산자를 기반으로 공통 형식으로 변환

## _Alignof 연산자
> `_Alignof(type)` : 특정 타입의 메모리 정렬 요구 조건을 정수 상수로 반환
- 피연산자를 평가하지 않는다.
- <stdalign.h>에 제공된 편의 매크로 alignof를 통해 사용됨
- 정적 어설션과 런타임 어설션에 유용
```c
#include <stdio.h>

int main() {
    printf("Alignment of char    : %zu\n", _Alignof(char));    // 보통 1
    printf("Alignment of int     : %zu\n", _Alignof(int));     // 보통 4
    printf("Alignment of double  : %zu\n", _Alignof(double));  // 보통 8
    printf("Alignment of long long: %zu\n", _Alignof(long long)); // 시스템에 따라 다름
    return 0;
}
```
- 구조체 멤버의 정렬 확인
- `alignas`, `aligned_alloc` 같은 메모리 정렬 관련 기능과 함께 사용
- 하드웨어 최적화를 위해 필요한 경우가 있음

```c
struct MyStruct {
    char c; // 1바이트 정렬
    int i;  // 4바이트 정렬
};

printf("Alignment of MyStruct: %zu\n", _Alignof(struct MyStruct));  // 4
```
※ 구조체 내부에 있는 멤버들 중 **가장 큰 정렬 요구 조건**을 따라갑니다.

- _Alignas
```c
_Alignas(n) 타입 변수이름;
```

or

```c
_Alignas(타입) 변수이름;  // 이 타입의 정렬 기준을 따르겠다는 뜻
```

```c
#include <stdio.h>
#include <stdalign.h>

int main() {
    _Alignas(16) int x;   // x는 16바이트 경계에 정렬됨

    printf("Address of x: %p\n", (void*)&x);
    return 0;
}
```
- `x`는 **메모리 상에서 16의 배수 주소에 위치**
- SIMD 명령어처럼 **특정 정렬이 요구되는 하드웨어 최적화** 상황에서 필요



```c
struct AlignedStruct {
    char c;
    _Alignas(8) int i;   // i는 8바이트 경계에 정렬됨
};
```
- 여기서 `int i`는 원래 정렬 4바이트면 충분하지만, **8바이트 정렬을 강제.**


```c
typedef _Alignas(16) struct {
    int a;
    float b;
} AlignedData;
```
- `AlignedData` 타입 자체가 **16바이트 정렬**되어야 함


## 관계형 연산자

> **관계형 연산자(Relational Operators)**는**두 값을 비교**해서 참(`true`) 또는 거짓(`false`)의 **논리값**을 반환하는 **이항 연산자**

  ### 관계형 연산자 목록

  | 연산자 | 의미               | 예시 (`a = 5`, `b = 10`) | 결과   |
  |--------|--------------------|---------------------------|--------|
  | `==`   | 같다 (equal)        | `a == b`                  | false (0) |
  | `!=`   | 같지 않다 (not equal) | `a != b`                  | true (1)  |
  | `>`    | 크다 (greater than) | `a > b`                   | false (0) |
  | `<`    | 작다 (less than)    | `a < b`                   | true (1)  |
  | `>=`   | 크거나 같다         | `a >= b`                  | false (0) |
  | `<=`   | 작거나 같다         | `a <= b`                  | true (1)  |

  ### 특징 요약

  - **결과 값은 `int`형**입니다.  
    - 참이면 `1`, 거짓이면 `0`이 반환됩니다.
  - **피연산자는 산술형(정수, 실수 등)**이어야 하며, **문자형도 비교 가능**합니다.
  - 논리 연산자(`&&`, `||`, `!`)와 조합하여 조건식을 만들 수 있습니다.

  ### 주의할 점
  1. 부동소수점 비교 시 오차 주의
  ```c
  float a = 0.1f * 3;
  if (a == 0.3f)  // 예상과 다르게 false일 수 있음
  ```
  2. 포인터 비교 : 두 포인터를 비교할 때 결과는 포인터가 가리키는 개체의 주소 공간에서의 상대적이 위치에 따라 달라짐, 같은 포인터를 가리키면 두 포인터 같음
  ```c
  int i, j;
  bool b1 = &i < &j;  // 정의되지 않은 동작, 부등식의 경우 
  bool b2 = &i == &j; // false 등식의 경우 사용 가능
  ```
## 복합 할당 연산자
> **복합 할당 연산자(Compound Assignment Operators)**

> E1 op =  E2 형태로 E1 = E1 op (E2) 같으며 E1은 한번만 평가됨 

  ### 종류와 예시

  | 연산자 | 의미                | 예시 (`a = 5`) | 결과       | 풀어쓴 식   |
  |--------|---------------------|----------------|------------|-------------|
  | `+=`   | 덧셈 후 대입         | `a += 3;`      | `a = 8`    | `a = a + 3;` |
  | `-=`   | 뺄셈 후 대입         | `a -= 2;`      | `a = 3`    | `a = a - 2;` |
  | `*=`   | 곱셈 후 대입         | `a *= 4;`      | `a = 20`   | `a = a * 4;` |
  | `/=`   | 나눗셈 후 대입       | `a /= 5;`      | `a = 1`    | `a = a / 5;` |
  | `%=`   | 나머지 후 대입       | `a %= 3;`      | `a = 2`    | `a = a % 3;` |
  | `&=`   | 비트 AND 후 대입     | `a &= 0x0F;`   | `a = a & 0x0F` | |
  | `|=`   | 비트 OR 후 대입      | `a |= 0x01;`   | `a = a | 0x01` | |
  | `^=`   | 비트 XOR 후 대입     | `a ^= 0xFF;`   | `a = a ^ 0xFF` | |
  | `<<=`  | 왼쪽 시프트 후 대입  | `a <<= 2;`     | `a = a << 2` | |
  | `>>=`  | 오른쪽 시프트 후 대입| `a >>= 1;`     | `a = a >> 1` | |




## 쉼표 연산자
> 쉼표는 연산자와 리스트에서 항목을 구분하기 위해 사용됨
- 왼쪽 피연산자는 void식으로 평가
- 왼쪽 피연산자의 평가와 오른쪽 피연산자의 평가 사이에 시퀸스 포인트 있음
- 결과는 오른쪽 피연산자의 형식과 값을 가진다.

## 포인터 산술
- 포인터에 정수 형식의 식을 더하거나 빼면 포인터 피연산자 형식의 값을 반환
- 포인터 피연산자가 배열의 요소를 가리킬 경우 결과는 원래 요소에서 요소의 오프셋을 가리킨다.
- 포인터가 배열 경계의 밖을 가리키면 정의되지 않은 동작 발생
```c
int arr[100];
int *arrp1 = &arr[40];
int *arrp2 = arrp1 + 20;
printf("%td\n", arrp2-arrp1); // 포인터간의 차는 " 몇 개의 요소차이인지를 나타냄" 20,  %td는 ptrdiff_t 형식 포인터 차이 출력시 표준 방식
```