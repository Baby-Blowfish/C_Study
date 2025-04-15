# 동적으로 할당된 메모리
> 런타임에 힙에서 동적으로 할당된 메모리

> 할당, 정적, 자동 스토리지 기간

> 할당 및 해제, 오류 방지 전략

## 스토리지 기간

> 개체는 RAM, ROM, 레지스터 등의 스토리지를 차지함

- `자동 스토리지 기간` : 개체는 블록 내부나 함수의 매개변수로 선언, 개체의 수명은 개체를 선언한 블록이 실행 될때부터 끝날 때 까지, 블록이 재귀적으로 들어가면 매번 새 개체가 만들어지고 각 개체는 고유한 스토리지를 갖는다.

- `정적 스토리지 기간` : 파일 범위 안에서 선언된 개체, 프로그램이 실행되는 동안 유지, 프로그램이 실행되기 전에 초기화

> 여기서는 `할당 스토리지 기간`에 대해서 설명한다.

  ### 힙과 메모리 관리자
  `할당 스토리지 기간` : 동적으로 할됭된 메모리, 수명은 할당부터 해제될 때까지, 동적으로 할당된 메모리는 메모리 관리자에 의해 메모리 블록인 힙(heap)에 할당
  - 메모리 관리자 : 표준 메모리 관리 함수의 구현해 힙을 관리하는 라이브러리

  ### 동적으로 할당된 메모리를 사용하는 경우
  - 런타임 전에 프로그램의 정확한 스토리지 요구 사항을 알 수 없는 경우 사용
  - 메모리 관라지가 런타임 힙에서 적절한 크기의 메모리 블록을 찾은 다음 호출자가 필요로 하지 않을 때 이 블록을 명시적으로 해제해야하므로 정적 할당보다 효율적이지 않다.
  ### 힙과 메모리 관리자
  `할당 스토리지 기간` : 동적으로 할됭된 메모리, 수명은 할당부터 해제될 때까지, 동적으로 할당된 메모리는 메모리 관리자에 의해 메모리 블록인 힙(heap)에 할당
  - 메모리 관리자 : 표준 메모리 관리 함수의 구현해 힙을 관리하는 라이브러리

  ### 힙과 메모리 관리자
  `할당 스토리지 기간` : 동적으로 할됭된 메모리, 수명은 할당부터 해제될 때까지, 동적으로 할당된 메모리는 메모리 관리자에 의해 메모리 블록인 힙(heap)에 할당
  - 메모리 관리자 : 힙 메모리를 관리하는 역할을 수행하는 내부 라이브러리 또는 시스템 컴포넌트

    - C에서 제공하는 표준 메모리 관리 함수:

      malloc(size) : 지정된 크기의 메모리 블록을 힙에서 할당

      calloc(n, size) : 0으로 초기화된 n개의 메모리 블록 할당

      realloc(ptr, size) : 기존 메모리 블록 크기 변경

      free(ptr) : 이전에 할당된 메모리 블록 해제

    이 함수들의 내부 구현은 운영체제의 **시스템 콜(mmap, brk)**과 연동되며, **힙 풀(heap pool)**에서 빈 공간을 찾고 적절히 재사용/병합/분할

  - 메모리 누수 (Memory Leak)
    > **더 이상 필요하지 않은 메모리**가 해제되지 않고 남아 있는 현상.  
    > 즉, **`malloc()` 등으로 할당은 되었지만, `free()`를 하지 않아서 메모리 관리자에게 반환되지 않은 상태**
    - 누수가 반복되면 힙에 사용 가능한 메모리가 점점 줄어들고
    - 결국 **메모리 고갈 → 프로그램이 더 이상 메모리 요청을 처리하지 못함**
    - 특히 서버, 임베디드, 반복 실행되는 루프에서는 **심각한 버그**가 될 수 있음

  - 조각 모음 (Defragmentation)
    > **메모리 할당/해제 과정에서 생긴 "작은 빈틈(조각)"들을 모아서 큰 블록으로 만드는 작업**
    ```text
    [ 200B 사용 ][ 50B 자유 ][ 300B 사용 ][ 70B 자유 ][ 100B 사용 ]
    ```
    - 위 구조에서 총 120B의 자유 공간이 있지만,  
      **인접하지 않아서 100B 이상 연속 할당 불가**할 수 있음.
    - 조각난 상태에서는 **충분한 총 메모리가 있어도**  
      큰 블록을 위한 **연속된 공간이 없어 할당 실패**할 수 있음
    - 그래서 일부 고급 메모리 관리자는 **인접한 빈 공간을 병합**해서  
      큰 공간을 확보하려고 함 → **조각 모음(Defragmentation)**
    - 조각 모음 수행 예시
      ```text
      Before:
      [ 100B 사용 ][ 50B 자유 ][ 150B 자유 ][ 200B 사용 ]

      After Defragmentation:
      [ 100B 사용 ][ 200B 자유 ][ 200B 사용 ]
      ```
## 메모리 관리 함수

  | 함수명           | 설명 |
  |------------------|------|
  | `malloc()`       | 원하는 바이트 수만큼 메모리를 **할당** |
  | `calloc()`       | 0으로 **초기화된 메모리 블록**을 할당 |
  | `realloc()`      | 기존 메모리의 크기를 **변경(재할당)** |
  | `reallocarray()` | `realloc()`의 안전 버전 (오버플로우 방지) |
  | `aligned_alloc()`| **지정한 정렬 단위**로 메모리 할당 |
  | `free()`         | `malloc()` 등으로 할당된 메모리를 **해제** |


  ### `void *malloc(size_t size)`

  - `size` 바이트만큼의 메모리 블록을 **힙에서 할당**
  - 반환된 포인터는 `void*`이므로 적절한 형으로 **캐스팅**하여 사용
  - **초기화되지 않음 → 쓰기 전에 반드시 초기화 필요**
  - 이식성을 위해 개체의 크기를 계산시 sizeof 연산자 사용
  - 반환값 : NULL 포인터 or 할당된 공간에 대한 포인터

  🔹 예:
  ```c
  typedef struct
  {
    char c[10];
    int i;
    double d;
  }widget터터

  widget *arr = malloc(sizeof(widget)); // 형식이 명확하게 정해짐, 역참조나 멤버 접근 가능, 암시적 형변환

  if(arr == NULL){
    // 할당 오류 처리
  }
  ```

  ### 형식을 선언하지 않고 메모리 할당
  ```c
  void *p1 = malloc(sizeof(widget);  // 형식 없는 저장소(raw storage), 역참조나 멤버 접근 불가->형변환 후 사용해야함, p1은 최소 8바이트 정렬된 포인터
  char *p2 = malloc(sizeof(widget));  // 형식 없는 저장소(raw storage), 유효한 형식 개체 아님, 됨됨이트 배열처럼 사용은 가능
  // p1->i 접근 안됨, p1[1]은 가능
  
  widget w = {"abc", 9, 3.2};
  memcpy(p1, &w, sizeof(widget)); // 개체 복사 -> 형식 부여, p1은 이때 유효한 형식을 가짐
  printf("p.i = %d\n", p -> i);
  ```
  - 할당된 저장소는 개체가 복사되기 전까지는 유효한 형식을 갖지 않음, 어떤 형식의 개체가 복사되면, 그 저장소는 이제 그 형식의 유효한 개체를 갖게됨
  - 최대 정렬 단위를 만족하도록 정렬된 포인터를 반환 -> 어떤 타입이든 복사해서 넣어도 정렬 위반이 발생 x

  ### 포인터를 선언된 개체의 형식으로 캐스팅하기  
  ```c
  widget *p = (widget *)malloc(sizeof(widget));
  ```
  - c에서 캐스팅 할 필요 없음, c++에서 필수
 

  ```c
  widget *p = (widget *)malloc(sizeof(widgett));  // ← 오타!
  ```

  - `widgett`라는 타입이 **없는데도 컴파일은 통과**
  - → `sizeof(widgett)`는 0이 되고, `malloc(0)` 수행됨 → **런타임 버그 발생 가능**


  ```c
  widget *p = malloc(sizeof(widgett));  // ❌ 컴파일 에러 발생 → 오타를 잡아줌
  ```
  - **형변환을 생략하면 컴파일러가 타입 체크를 해줍니다.**
  - CERT C에서 캐스팅 요구 하지 않음


  ### 초기화되지 않은 메모리 읽기(Uninitialized Memory Read, UMR)

  > 프로그램이 **초기화되지 않은 변수나 메모리 영역**을 읽으려고 할 때 발생하는 오류.  

  > 이 값은 **쓰레기 값(garbage value)**이며, 예측 불가능한 동작을 일으킵니다.

  > **정의되지 않은 동작(undefined behavior)**
  ```c
  #include <stdlib.h>
  #include <stdio.h>

  int main() {
      int *arr = malloc(5 * sizeof(int));
      printf("%d\n", arr[2]);  // ❌ 초기화되지 않은 힙 메모리 읽기
      free(arr);
      return 0;
  }
  ```
  - `malloc()`은 **초기화하지 않고** 그냥 메모리 블록만 확보함
  - **`arr[2]`에는 쓰레기 값이 들어 있음**
  - 정의되지 않은 동작
  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  int main(void)
  {
    char *str = (char *)(malloc(16));

    if(str)
    {
      strncpy(str, "123456789abcdef", 15);
      printf("str = %s\n",str);
      free(str);
      return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
  }
  ```
  - str[15]가 0으로 초기화 될거라고 생각하지만 그렇지 않음
  - str[15]는 null일수도 쓰레기 값일수도 있음 -> printf에서 정의 되지 않은 동작 발생

  ### `void *aligned_alloc(size_t alignment, size_t size)`

  - **정렬된 메모리**를 요청할 때 사용 (ex. 16, 32, 64바이트 경계)
  - `alignment`은 **2의 거듭제곱**이어야 하며, `size`는 `alignment`의 **배수**여야 함
  - SIMD (SSE, AVX), DMA 등에 유용
  - 구현체 지원하는 유효한 맞춤이 아닌 경우 null 포인터 반환

  🔹 예:
  ```c
  #include <stdlib.h>
  float *vec = aligned_alloc(32, 8 * sizeof(float)); // 32바이트 정렬된 32B 메모리
  ```

  ### `void *calloc(size_t nmemb, size_t size)`

  - `nmemb` 개의 원소를 각각 `size` 바이트로 할당
  - 모든 바이트를 **0으로 초기화**
  - `malloc()` + `memset()`을 결합한 효과
  🔹 예:
  ```c
  int *arr = calloc(10, sizeof(int));  // 10개 int 0으로 초기화
  ```

  ### `void *realloc(void *ptr, size_t new_size)`

  - 기존 메모리 블록을 `new_size` 크기로 **재할당**
  - 동작
    - 기존 포인터 `ptr`의 메모리 크기를 늘리거나 줄임
    - 새로운 메모리 블록을 할당 한 후 기존 데이터를 복사하고 원래 블록을 해제
    - 반환값은 새 블록의 포인터
    - NULL 반환 시 재할당 실패, 원래 포인터는 유지됨 따라서 free를 명시적으로 해줘야함
    - `realloc(NULL, size)` → `malloc(size)`와 동일할당
    - 새 스토리지가 더 크다면 추가 스토리지는 초기화되지 않은 상태로 남김
  - new_size = 0 일 경우 정의 되지 않은 동작
  ```c
  p = realloc(p, nsize);  // ❌ realloc 실패 시 p는 NULL로 덮여짐 → 기존 메모리 잃어버림
  ```
  - 올바른 방법
  ```c
  void *p2; // 임시 포인터 사용
  void *p = malloc(100);

  if((nsize == 0) || (p2 = realloc(p, nsize)) == NULL)  // NULL 반환값이 덮히지 않도록 p2로 대입, nsize == 0의 정의되지 않은 동작 테스트 
  {
    free(p);
    return NULL;
  }
  p = p2; // 새로 재 할당된 메모리의 포인터를 대입
  ```

  ### `void *reallocarray(void *ptr, size_t nmemb, size_t size)`

  - `realloc()`에서  `nmemb * size` 연산에서 size_t의 **오버플로우를 발생시** 정의되지 않는 동작 발생
  - num*size의 값이 오버플로우가 될 경우 NULL 포인터를 반환 
  - 주로 **보안이 중요한 코드에서 사용**됨 (예: OpenBSD)

  🔹 예:
  ```c
  int *arr = reallocarray(NULL, 1000, sizeof(int)); // == calloc(1000, sizeof(int))과 유사
  ```

  ### `void free(void *ptr)`
  - `malloc()`, `calloc()`, `realloc()` 등으로 **할당한 메모리 해제**
  - 인자로 전달된 포인터는 이후 **사용 금지**
  - `NULL`을 전달하면 아무 동작도 하지 않음

  ### dangling pointer 방지
  - 이미 해제된 메모리에 대한 포인터
  ```c
  free(arr);
  arr = NULL;  // Dangling pointer 방지
  ```

  ### double-free 취약점 방지
  > 같은 포인터에 대한 두번 이상의 free()호출 -> 정의되지 않는 동작
  ```c
  void *p = malloc(100);
  free(p);
  free(p);  // ❌ 두 번째 해제 → double free
  ```
  - 이미 해제된 메모리를 다시 해제하려고 하면, **힙 관리자(메모리 관리자)의 내부 구조가 손상**

  힙 구조가 손상됨
  - 많은 메모리 관리자는 free된 블록을 **freelist** 또는 **bin**에 넣어 관리
  - 두 번 넣으면 **링크가 꼬이거나**, **원래 위치에 다른 코드가 쓸 수 있는 포인터가 들어감**
  - 이를 악용해 **메모리 덮어쓰기, 임의 코드 실행** 가능
  - 공격자가 특정한 `free()` 시점을 조작하여,  **원래 프로그램 로직을 벗어난 메모리를 할당받게 할 수 있음**
  - 이후 **함수 포인터, GOT, vtable** 같은 민감한 메모리 구조를 덮어쓸 수 있음

  | 방법                      | 설명 |
  |---------------------------|------|
  | `free()` 후 포인터를 NULL로 초기화 | `free(p); p = NULL;` 하면 double free 방지 |
  | 메모리 상태 추적 도구 사용     | `valgrind`, `asan` 등으로 double free 탐지 |
  | 스마트 포인터(C++) 사용        | `unique_ptr` 등은 자동으로 한 번만 해제 |
  | 커스텀 메모리 풀 사용           | 사용자 정의 할당기에서 이중 해제 감지 가능 |

  ```c
  void *p = malloc(100);
  // ...
  free(p);
  p = NULL;  // ✅ 이후 실수로 다시 free(p) 해도 아무 일 없음
  ```

## 유연한 배열 멤버

- **유연한 배열 멤버(Flexible Array Member, FAM)**를 포함한 구조체를 **동적으로 할당하고 복사하는 방법**

  ### ✅ 유연한 배열 멤버란?

  C99부터 도입된 기능으로,  
  구조체 마지막 멤버를 크기 없는 배열로 선언하면  
  **동적으로 유연한 크기의 데이터를 붙일 수 있게 됩니다.**

  ```c
  typedef struct {
      size_t len;
      char data[];  // 유연한 배열 멤버 (FAM)
  } Buffer;
  ```

  - `data[]`는 크기가 정해지지 않았지만,
  - `malloc()`으로 전체 구조체 크기 + 필요한 배열 크기만큼 **한꺼번에 할당**할 수 있습니다.



  ### 1. 동적 할당 방법

  ```c
  size_t len = 100;
  Buffer *buf = malloc(sizeof(Buffer) + len * sizeof(char));
  buf->len = len;
  memcpy(buf->data, "hello", 6);
  ```

  - `sizeof(Buffer)`는 `len` 필드까지만 포함  
  - `data[]`는 `malloc`으로 추가 공간을 확보해야 사용 가능


  ### 2. 복사하기

  복사하려면 **전체 구조체 크기 + 배열 크기**를 알아야 합니다:

  ```c
  size_t size = sizeof(Buffer) + buf->len * sizeof(char);
  Buffer *copy = malloc(size);
  memcpy(copy, buf, size);
  ```

  - `memcpy()`는 구조체 필드와 배열 전체를 **메모리 통째로 복사**
  - `copy->len`과 `copy->data`도 동일하게 유지됨

  ### 예제 전체 코드

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  typedef struct {
      size_t len;
      char data[];
  } Buffer;

  int main() {
      const char *msg = "Hello, FAM!";
      size_t len = strlen(msg) + 1;

      // 1. 동적 할당
      Buffer *buf = malloc(sizeof(Buffer) + len);
      buf->len = len;
      memcpy(buf->data, msg, len);

      // 2. 복사
      size_t total_size = sizeof(Buffer) + buf->len;
      Buffer *copy = malloc(total_size);
      memcpy(copy, buf, total_size);

      // 확인
      printf("복사본: %s\n", copy->data);

      // 해제
      free(buf);
      free(copy);
      return 0;
  }
  ```


## 가변 길이 배열
**가변 길이 배열 (VLA: Variable Length Array)** 

> 🔹 배열의 크기를 **컴파일 타임이 아닌 런타임**에 정할 수 있는 배열  
> 🔹 C99부터 도입된 **스택 기반 동적 배열**  
> 🔹 선언 시 `malloc()`처럼 명시적 할당 없이  
>    **변수로 배열 크기를 지정**할 수 있음

  ### ✅ 예제

  ```c
  #include <stdio.h>

  void foo(int n) {
      int arr[n];  // ← VLA: 길이가 n인 배열, 크기는 런타임에 결정됨

      for (int i = 0; i < n; i++)
          arr[i] = i * 10;

      for (int i = 0; i < n; i++)
          printf("%d ", arr[i]);
      printf("\n");
  }

  int main() {
      foo(5);   // 출력: 0 10 20 30 40
      return 0;
  }
  ```

  ### ✅ 주요 특징

  | 항목 | 설명 |
  |------|------|
  | 메모리 위치 | **스택(stack)** |
  | 수명 | 배열이 선언된 **블록(scope)** 안에서만 |
  | 크기 결정 | **런타임**에 정해짐 |
  | 타입 | 배열 자체 (포인터 아님!) |
  | 접근 방식 | `arr[i]` — 일반 배열처럼 |
  | 해제 필요 | ❌ 필요 없음 (자동 해제됨) |


  ### ✅ VLA vs `malloc()` vs 정적 배열

  | 항목 | VLA (`int arr[n]`) | malloc (`int *arr = malloc(...)`) | 정적 배열 (`int arr[10]`) |
  |------|---------------------|------------------------------------|----------------------------|
  | 메모리 | 스택 | 힙 | 스택 |
  | 길이 결정 | 런타임 | 런타임 | 컴파일 타임 |
  | 해제 필요 | ❌ | ✅ `free()` | ❌ |
  | 포인터 여부 | ❌ (진짜 배열) | ✅ | ❌ |
  | 속도 | 매우 빠름 | 느림 | 매우 빠름 |


  ### ✅ 제한 사항

  | 주의할 점 | 설명 |
  |-----------|------|
  | 스택 오버플로우 위험 | 너무 큰 크기 할당 시 위험 (`int arr[1000000];`)  
  | 크기가 0이면? | GCC 등 일부는 허용, 표준은 미정의 동작  
  | sizeof 연산 | 컴파일 타임 상수가 아니므로 `sizeof(arr)`는 상수 아님  
  | 초기화 불가능 | `int arr[n] = {1,2,3};` ❌ 오류


  ### ✅ 예제: `sizeof`에서 주의
  - 런타임에 평가
  ```c
  void bar(int n) {
      int arr[n];
      printf("%lu\n", sizeof(arr)); // 런타임 결과 → n * sizeof(int)
  }
  ```

  ### ✅ 함수 인자로 VLA 받기

  ```c
  #include <stdio.h>

  void print_matrix(int rows, int cols, int matrix[rows][cols]) {
      for (int i = 0; i < rows; i++) {
          for (int j = 0; j < cols; j++) {
              printf("%3d ", matrix[i][j]);
          }
          printf("\n");
      }
  }

  int main() {
      int r = 3, c = 4;
      int mat[r][c];  // VLA

      // 값 초기화
      for (int i = 0, val = 1; i < r; i++)
          for (int j = 0; j < c; j++)
              mat[i][j] = val++;

      print_matrix(r, c, mat);  // ✅ OK
      return 0;
  }
  ```

  ```c
  matrix:
  +----+----+----+----+
  |  1 |  2 |  3 |  4 |   ← matrix[0]
  +----+----+----+----+
  |  5 |  6 |  7 |  8 |   ← matrix[1]
  +----+----+----+----+
  |  9 | 10 | 11 | 12 |   ← matrix[2]
  +----+----+----+----+

  matrix == &matrix[0]
  matrix[i][j] == *(*(matrix + i) + j)
  ```

  ## ✅ 5. sizeof로 확인

  ```c
  void test(int rows, int cols, int matrix[rows][cols]) {
      printf("sizeof(matrix) = %lu\n", sizeof(matrix));        // 포인터 → 8 (64bit)
      printf("sizeof(matrix[0]) = %lu\n", sizeof(matrix[0]));  // 한 행 → cols * 4
      printf("sizeof(matrix[0][0]) = %lu\n", sizeof(matrix[0][0])); // int → 4
  }
  ```

  ❌ `void foo(int arr[][])` → **컴파일 에러**  
  → **두 번째 이후 차원의 크기는 반드시 명시해야 함**

  ✅ `void foo(int rows, int cols, int arr[][cols])`  
  ✅ `void foo(int (*arr)[cols])`


 

