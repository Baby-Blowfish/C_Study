# 프로그램 구조

시스템 구성 : 소스 파일, 헤더 파일, 라이브러리, 이미지, 소리, 구성 파일 등등...
작은 논리 구성 요소로 프로그램을 구조화 하는 방법 배우기

## 구성 요소화의 원칙
프로그램을 공유 경계 또는 인터페이스를 통해 구성 요소로 구조화
구성 요소 기반 소프트웨어 엔지니어링 원칙

  ### 🔷 응집도 (Cohesion)
  > **하나의 모듈 내부 요소들끼리 얼마나 밀접하게 관련되어 있는가?**  
  > → **"한 가지 일"에 집중하는 정도**

  - 모듈/헤더/클래스 내부의 함수나 데이터들이 **같은 목적**을 위해 모여 있으면 응집도가 높다
  - 서로 관계없는 기능이 섞여 있으면 응집도가 낮다


  #### 응집도 낮은 헤더 (관련 없는 기능 묶음)

  ```c
  // bad_utils.h
  int get_string_length(const char *str);
  double compute_tangent(double angle);
  void spawn_thread(void (*fn)(void*));
  ```
  - 문자열 처리, 수학 함수, 스레드 생성이 **의미 없이 함께 있음**
  - 이 헤더는 어떤 역할을 하는지 모호하고 유지보수하기 어렵다


  #### 응집도 높은 헤더 (목적이 명확한 기능 모음)

  ```c
  // string_utils.h
  int get_string_length(const char *str);
  char* string_concat(const char *a, const char *b);
  int find_substring(const char *haystack, const char *needle);
  ```
  - 모두 **문자열 처리**와 관련된 기능만 있음
  - 사용자 입장에서는 "문자열 작업을 하고 싶다 → 이 헤더만 포함하면 됨"
  - **하나의 주제에 집중되어 있으므로 응집도가 높음**



  ### 🔷 결합도 (Coupling)

  > **하나의 모듈/인터페이스가 다른 모듈/인터페이스에 얼마나 의존적인가?**  
  > → **"얼마나 다른 것들과 얽혀 있는가"**

  - 결합도가 낮을수록 **독립적**이며, 변경이 일어나도 영향이 적다
  - 결합도가 높을수록 **변경이 연쇄적**으로 번져나가 유지보수가 힘들어진다

  #### 결합도 높은 구조

  ```c
  // a.h
  typedef struct {
      int x, y;
  } Position;

  // b.h
  #include "a.h"
  void move(Position *p, int dx, int dy);
  ```
  - `b.h`는 반드시 `a.h`에 **의존**
  - `a.h`의 구조체가 바뀌면 `b.h`도 같이 수정돼야 함
  - 더 나아가 이걸 사용하는 모든 코드도 영향을 받음 → 결합도 **높음**


  #### 결합도 낮추기

  ```c
  // a.h
  typedef struct Position Position;

  // b.h
  void move(Position *p, int dx, int dy);
  ```

  - `Position`을 **불완전 타입(forwad declaration)**으로만 노출
  - 내부 구현을 캡슐화하면 결합도를 줄일 수 있음
  - 구조체 변경에도 외부 인터페이스는 영향 없음

  
  ### **불완전 타입(forward declaration)을 활용한 구조체 캡슐화** 
  **결합도를 줄이고 구현을 은닉**하는 대표적인 


  #### 구조체를 불완전 타입으로 forward declaration 하여 결합도 낮추기

  ```c
  typedef struct Position Position;
  ```
  - 이 선언은 `Position`이라는 **이름만 알려주고**, 내부 멤버는 알려주지 않음
  - 즉, "이런 타입이 존재한다"는 **선언만** 하고, **정의는 감춤**

  이것을 **불완전 타입 (incomplete type)** 또는 **전방 선언 (forward declaration)**이라고 부름



  #### 📁 `a.h`: 구조체 이름만 공개 (인터페이스)
  ```c
  #ifndef A_H
  #define A_H

  typedef struct Position Position;  // 이름만 알려줌

  #endif
  ```

  #### 📁 `b.h`: 구조체 포인터를 사용하는 함수 선언
  ```c
  #ifndef B_H
  #define B_H

  #include "a.h"

  void move(Position *p, int dx, int dy);

  #endif
  ```

  #### 📁 `a.c`: 구조체의 실제 정의와 구현
  ```c
  #include "a.h"

  struct Position {
      int x;
      int y;
  };

  Position* create_position(int x, int y) {
      Position *p = malloc(sizeof(Position));
      p->x = x;
      p->y = y;
      return p;
  }
  ```


  #### 3. ✅ 이 방식이 결합도를 줄이는 이유

  | 측면 | 설명 |
  |------|------|
  | **정보 은닉** | 구조체 내부 필드를 외부에 숨길 수 있음 (캡슐화) |
  | **독립성 증가** | 구조체가 바뀌어도 외부 코드는 전혀 변경될 필요 없음 |
  | **의존성 제거** | 구조체를 사용하는 코드가 필드에 직접 접근 불가 → getter/setter를 통해 제한적 접근 가능 |
  | **컴파일 속도 향상** | 헤더 파일 변경 시 영향을 받는 컴파일 단위 줄어듦 |

  ---

  #### 4. ❌ 결합도 높은 잘못된 예

  ```c
  // a.h
  typedef struct {
      int x;
      int y;
  } Position;

  // b.h
  #include "a.h"
  void move(Position *p, int dx, int dy);
  ```

  - 구조체 정의가 **직접 노출되어 있음**
  - `x`, `y`를 직접 사용하는 코드가 많아지면 → 구조 변경 시 **전체 코드에 영향을 줌**
  - 즉, **구현 세부사항이 외부로 새어 나가며 결합도가 높아짐**

## 코드 재사용 (Code Reuse)

> **한 번 구현한 코드를 프로그램 여러 곳에서 반복 사용**함으로써  
> 중복을 줄이고, 유지보수성을 높이는 개발 방식


| 항목 | 설명 |
|------|------|
| **중복 제거** | 같은 논리가 두 번 이상 나타나면 함수로 추출 |
| **최소 재사용 단위** | **함수** (`function`) |
| **재사용의 조건** | 해당 로직이 **범용적**, **중복적**, **독립적**이면 추출 가치가 있음 |
| **좋은 함수란** | **다른 함수와 중복되지 않는 하나의 역할(SRP)** 수행 |



  ### 일반성과 특이성의 균형

  | 구분 | 설명 |
  |------|------|
  | **너무 일반적** | 너무 많은 매개변수, 의미 없는 추상화 → 오히려 사용 어렵고 불명확 |
  | **너무 특수함** | 단 한 군데에서만 쓰임 → 재사용 가치 낮음 |
  | ✅ **균형 있는 설계** | “자주 쓰이는 구조를, 적당히 유연하게” 추상화


| 원칙 | 설명 |
|------|------|
| 📌 DRY 원칙 | Don’t Repeat Yourself – 같은 코드는 함수로 |
| 📌 SRP | 하나의 함수는 하나의 책임만 |
| 📌 재사용 가능한 단위 | 함수 → 모듈 → 라이브러리로 점진적 확장 |
| 📌 인터페이스 설계 | 너무 유연하면 복잡, 너무 특수하면 재사용성 없음 → 적절한 균형 필요 |



## 데이터 추상화
추상화의 public 인터페이스와 구현 세부 사항을 명확하게 구별해 재사용할 수 있는 모든 소프트웨어 구성 요소
데이터 추상화 사용자가 필요로 하는 데이터 형식 정의와 함수 선언 상수 정의가 포함되며 헤더파일에 위치
private 구현과 public 인터페이스 분리하면 구성 요소에 따라 달라지는 코들르 변경하지 않고 구현 세부 사항을 변경 할 수 있다

헤더파일에는 구성 요소에 대한 함수 선언과 형식 정의가 있음
string.h 문자열 관리 기능을 public 인터페이스로 제공
threads.h 스레딩을 위한 유틸리티 함수 제공
헤더파일에 필요한 헤더를 명시적으로 포함하거나 헤더 파일 사용자가 헤더를 먼저 포함하도록 요구하는 경우
사용자가 헤더 파일을 사용할 때 추가 작업 없이도 필요한 모든 종속성을 해결 코드 작성 간편 유지보수 용이 
내부 구현 세부 정보가 외부로 드러나지 않도록

소스 파일은 헤더파일이 선언한 기능이나 주어진 프로그램에 팔요한 모든 작업을 수행하는데 사용되는 프로그램 논리 구현
network.c 네트워크 통신 논리 구현
하나의 헤더 파일을 사용해 두 소스 파일 간에 구현 세부 정보를 구현할 수 있지만 헤더 파일은 구현 세부 사항이 노출되지 않도록 public 인터페이스와는 다른 위치에 있어야한다

컬렉션은 데이터 요소의 그룹을 나타냄
데이터 요소 컬렉션은 평면 배열이나 이진트리 유향 그래프 또는 다른 구조로 표현
컬렉션 데이터 추상화의 인터페이스르 기본 데이터 구조 구현과 분리하면 컬렉션 인테페이스에 의존한느 코드를 변경하지 않고도 구현을 변경할 수 있음

아주 잘 정리하셨어요.  
지금 말씀하신 건 C 언어에서의 **데이터 추상화(Data Abstraction)**와 **인터페이스와 구현 분리 설계 원칙**에 대한 핵심 내용입니다.  
다만 텍스트가 조금 밀도 있게 쓰였기 때문에, 여기서 **핵심 원리와 설계 구조**, 그리고 **실제 적용 예시**를 기준으로 재정리해드릴게요.



> 사용자는 **데이터가 어떻게 구성되고 작동하는지 모르더라도**,  
> 제공된 **인터페이스(API)**를 통해 그 데이터를 사용할 수 있어야 한다.

즉,

- **무엇을 할 수 있는가?** (인터페이스)
- **어떻게 동작하는가?** (구현)

이 둘을 **철저히 분리**하는 게 핵심입니다.


  ### 추상화 구조의 일반적인 형태 (C 언어 기준)

  ```c
  // 헤더파일 (interface.h)
  #ifndef INTERFACE_H
  #define INTERFACE_H

  typedef struct MyType MyType;

  MyType* mytype_create(void);
  void mytype_set(MyType*, int value);
  int mytype_get(const MyType*);
  void mytype_destroy(MyType*);

  #endif
  ```

  ```c
  // 구현파일 (interface.c)
  #include "interface.h"

  struct MyType {
      int value;  // 내부 구현은 외부에 노출되지 않음
  };

  MyType* mytype_create(void) {
      MyType* p = malloc(sizeof(MyType));
      p->value = 0;
      return p;
  }

  void mytype_set(MyType* p, int v) { p->value = v; }
  int  mytype_get(const MyType* p) { return p->value; }
  void mytype_destroy(MyType* p)   { free(p); }
  ```



  ### 구조적 원칙 

  | 항목 | 설명 |
  |------|------|
  | **헤더파일** | 사용자에게 필요한 **타입 정의, 함수 선언만 제공** |
  | **구현파일** | 실제 데이터 구조체 정의 및 함수 구현 |
  | **사용자는 구조체 멤버를 전혀 몰라도 사용 가능** | → 정보 은닉 (Encapsulation) 실현 |
  | **수정 범위 최소화** | 구조체 내부를 바꿔도 API는 그대로 → 사용자 코드 변경 없음 |



  ### 라이브러리 예시 (`string.h`, `threads.h`)

  - `string.h`: 문자열 조작 함수 선언만 있음 (`strlen`, `strcpy`, `strcmp`, ...)
  - `threads.h`: C11 스레딩 API 인터페이스 (`thrd_create`, `mtx_lock` 등)
  - 내부 구현은 **플랫폼, 라이브러리마다 완전히 다름**
    → **인터페이스만 표준화되어 있음**


  ### 좋은 추상화가 주는 이점

  | 이점 | 설명 |
  |------|------|
  | 🔄 구현 교체 가능 | 배열 → 링크드리스트로 바꾸더라도 사용자 코드는 변경 없음 |
  | 🧼 코드 명확화 | 사용자는 함수 이름만 보고 어떻게 써야 할지 알 수 있음 |
  | 🛠 유지보수 용이 | 내부 구조 변경이 사용자 코드에 영향 X |
  | ✅ 모듈화 | 기능별 코드 분리가 명확해지고, 테스트도 쉬움 |



## 불투명 형식
데이터 추상화는 정보를 숨기는 불투명 데이터 형식과 함께 사용해야 효과적
불투면 데이터 형식 : 순방향 선언 구조체형식과 같은 불완전 형식을 사용해 표현하는 데이터 형식 
불안전한 데이터 형식 : 식별자를 설명하지만 내부구조 정보가 부족한 형식
내부 전용 데이터 구조를 숨기면 데이터 추상화를 사용하는 프로그래머는 변경될 수 있는 구현 세부 사항에 맞춰 코드를 작성할 수 없음
불완전한 형식은 노출되지만 잘 정의된 형식은 구현체를 통해서만 접근 가능



## ✅ 불투명 형식 (Opaque Type)

  > “**내부가 보이지 않는 구조체 타입**을 헤더에서 선언만 하고,  
  > 그 내부 구현은 `.c` 파일에만 존재하도록 분리하는 방식”


  ### 왜 이걸 쓰는가?

  | 목적 | 설명 |
  |------|------|
  | **구현 은닉** | 구조체 내부가 바뀌더라도 사용자 코드는 영향을 받지 않게 |
  | **API 설계 명확화** | 사용자에게 필요한 함수만 노출, 내부 구조는 감춤 |
  | **결합도 ↓** | 사용자는 내부 필드에 접근 불가 → 변경 전파 없음 |
  | **응집도 ↑** | 내부 구현과 인터페이스가 명확히 분리됨 |


  ### Opaque Type 구조 요약

  ```c
  // 헤더 파일 (.h)
  typedef struct MyType MyType;  // 선언만! (구조체 본체는 안 보임)

  MyType* mytype_create();
  void    mytype_set(MyType*, int);
  int     mytype_get(const MyType*);
  void    mytype_destroy(MyType*);
  ```

  ```c
  // 소스 파일 (.c)
  struct MyType {
      int value;  // 내부 필드 - 외부에서는 절대 접근 못함
  };

  MyType* mytype_create() {
      MyType* obj = malloc(sizeof(MyType));
      obj->value = 0;
      return obj;
  }
  ```


  ### 사용자 시점

  ```c
  #include "mytype.h"

  MyType* obj = mytype_create();
  mytype_set(obj, 42);
  int val = mytype_get(obj);  // 내부 필드를 직접 접근 못함
  ```

  > `obj->value = 999;` 이런 코드는 **불가능**  
  → 구조체 내부를 몰라도 `mytype_get()`을 통해서만 접근 가능


  ### 컬렉션 예시

  ```c
  // collection.h
  #ifndef COLLECTION_H
  #define COLLECTION_H

  typedef struct Collection Collection;

  Collection* collection_create(void);
  void        collection_add(Collection*, int value);
  int         collection_get(const Collection*, int index);
  void        collection_destroy(Collection*);

  #endif
  ```

  ```c
  // collection_array.c
  #include "collection.h"

  struct Collection {
      int* data;
      int  capacity;
      int  size;
  };

  Collection* collection_create() {
      Collection* c = malloc(sizeof(Collection));
      c->data = malloc(sizeof(int) * 10);
      c->capacity = 10;
      c->size = 0;
      return c;
  }
  ```


  ### 키워드 정리

  | 용어 | 의미 |
  |------|------|
  | **불투명 형식** | `typedef struct X X;`처럼 선언만 있고 구조는 감춰진 형식 |
  | **불완전 형식** | 내부가 정의되지 않은 구조체 (forward-declared struct) |
  | **투명 형식** | 헤더에 구조체 전체가 노출된 경우 (`typedef struct {...} X;`) |
  | **정보 은닉 (Encapsulation)** | 내부 구현이 외부에 노출되지 않도록 보호 |

  

## 실행 파일 (Executable)

> 컴파일러가 만든 `.o`(object file)들을 **링커가 하나로 합쳐서 만든 최종 파일**

| 단계 | 설명 |
|------|------|
| 컴파일 | `.c` → `.o` (기계어) |
| 링크   | `.o` + 라이브러리 → 실행파일 (`a.out`, `main.exe` 등) |


- 실행 파일 종류

| 종류 | 설명 |
|------|------|
| 일반 실행 파일 | 사용자가 직접 실행 (`./program`) |
| 라이브러리 | 다른 프로그램에 **기능을 제공**하기 위한 컴포넌트 |
| 드라이버 / 펌웨어 | 하드웨어 제어용, OS나 장치와 연동됨 |



  ### 라이브러리 (Library)

  > 독립적으로 실행되지 않지만, 다른 코드에서 불러 쓸 수 있는 **재사용 가능한 코드 묶음**

  라이브러리는 일반적으로:

  - `.h` 헤더 (인터페이스)
  - `.c` or `.o` 소스 (구현)



  ### 정적 라이브러리 (Static Library)

  | 확장자 | `.a` (Linux), `.lib` (Windows) |
  | 특징 | 컴파일 시 라이브러리 코드가 **실행파일에 포함됨** |

  장점:
  - 배포 시 `.a` 파일 없어도 실행 가능
  - 의존성 없음

  단점:
  - 실행파일이 커짐
  - 라이브러리 수정 시 재컴파일 필요

  사용 예:
  ```bash
  gcc main.c -L. -lmylib_static -o main
  ```



  ### 동적 라이브러리 (Shared / Dynamic Library)

  | 확장자 | `.so` (Linux), `.dll` (Windows) |
  | 특징 | 실행 시에 시스템이 `.so` 파일을 **메모리에 로드해서 사용**

  ### 장점:
  - 메모리 사용량 감소 (여러 프로그램이 공유)
  - 라이브러리 업데이트 가능 (재배포 없이 버전 교체 가능)

  ### 단점:
  - 실행 시 `.so` 파일이 필요함
  - 버전 충돌 시 문제 가능

  ### 사용 예:
  ```bash
  gcc main.c -L. -lmylib_shared -o main
  export LD_LIBRARY_PATH=.
  ./main
  ```

정적 vs 동적 라이브러리 비교

| 항목 | 정적 라이브러리 (`.a`) | 동적 라이브러리 (`.so`) |
|------|-------------------------|---------------------------|
| 실행파일 크기 | 커짐 | 작음 |
| 성능 | 로딩 빠름 | 로딩 약간 느림 |
| 업데이트 | 실행파일 재빌드 필요 | 라이브러리만 교체 가능 |
| 의존성 | 없음 | `.so` 필요 |
| 메모리 사용 | 프로세스별 별도 | 여러 프로세스 공유 가능 |



  ### 예제 상황
  ```c
  // mymath.h
  #ifndef MYMATH_H
  #define MYMATH_H

  int add(int a, int b);
  int square(int a);

  #endif
  ```

  ```c
  // mymath.c
  #include "mymath.h"

  int add(int a, int b) { return a + b; }
  int square(int a)     { return a * a; }
  ```

  ### 컴파일해서 라이브러리 생성

  ```bash
  # 정적 라이브러리 생성
  gcc -c mymath.c
  ar rcs libmymath.a mymath.o

  # 동적 라이브러리 생성
  gcc -fPIC -c mymath.c
  gcc -shared -o libmymath.so mymath.o
  ```

| 핵심 개념 | 설명 |
|-----------|------|
| **실행 파일** | 컴파일된 `.o` 코드들이 링크되어 만들어진 최종 결과물 |
| **라이브러리** | 재사용 가능한 기능을 제공하는 비실행 파일 |
| **정적 라이브러리** | 실행파일에 통합됨 (`.a`) |
| **동적 라이브러리** | 런타임에 로딩됨 (`.so`) |
| **헤더파일** | public 인터페이스 선언, 구현은 없음 |


## 링크(Linkage)란?

> "**같은 이름의 식별자들이 서로 같은 엔티티를 참조하는가?**"를 결정하는 컴파일러의 판단 기준입니다.


링크 vs 스코프 vs 저장 클래스

| 개념 | 설명 |
|------|------|
| **스코프(Scope)** | 이 이름을 **어디에서 접근 가능한가?** |
| **링크(Linkage)** | 이 이름이 **다른 파일에 있는 이름과 동일한가?** |
| **저장 클래스(Storage Class)** | 이 이름이 **언제까지 메모리에 유지되는가?** (예: static duration)



링크 종류 

| 종류 | 설명 | 예시 |
|------|------|------|
| **없음 (no linkage)** | 함수 매개변수, 지역 변수 등 | `int x;` (함수 안) |
| **내부 링크 (internal linkage)** | 파일 내에서만 접근 가능 | `static int x;` |
| **외부 링크 (external linkage)** | 다른 파일에서도 접근 가능 | `extern int x;`, `int x = 1;` (파일 전역) |



함수와 변수의 링크 비교

```c
// foo.c
static int x = 5;       // 내부 링크
int y = 10;             // 외부 링크
void foo(void) {}       // 암시적 외부 링크
static void helper() {} // 내부 링크
```

```c
// bar.c
extern int y;       // 외부 링크 → foo.c의 y 참조
extern void foo();  // 외부 링크 → foo.c의 foo 참조
extern int x;       // ❌ 오류: x는 foo.c 내부 링크 → 외부에서 접근 불가
```


함수의 매개변수는 링크가 없다 

```c
void foo(int i) {
    // i는 링크 없음 (다른 어떤 선언과도 연결되지 않음)
}
```


static과 extern 정리

| 선언 위치 | `static` 의미 | `extern` 의미 |
|-----------|----------------|----------------|
| 전역 (파일 범위) | 내부 링크 | 외부 링크 |
| 함수 내부 (지역 변수) | 정적 저장 (링크 없음) | 참조 선언 (링크 없음) |



  ### public / private 인터페이스 구분

  - **Public 인터페이스**는 다른 파일에서도 사용할 수 있어야 함 → 외부 링크
  - **Private 구현**은 해당 `.c` 파일에서만 쓰이도록 해야 함 → 내부 링크


  `mylib.h` (Public Interface)
  ```c
  #ifndef MYLIB_H
  #define MYLIB_H

  int public_add(int a, int b); // public → 외부 링크 (명시 or 암시)

  #endif
  ```

  `mylib.c` (구현)
  ```c
  #include "mylib.h"

  int public_add(int a, int b) {
      return a + private_square(b);
  }

  static int private_square(int x) {  // 내부 링크 → 외부에서 접근 불가
      return x * x;
  }
  ```

  > - `public_add()`는 외부에서 사용 가능
  > - `private_square()`는 이 파일에서만 접근 가능 (캡슐화)

  ### 링크 충돌

  ```c
  // foo.c
  static int value = 1;

  // bar.c
  static int value = 2;
  ```

  - 이건 괜찮음 → 두 `value`는 **내부 링크이므로 서로 다른 변수**
  - 하지만 둘 다 `int value = 1;`로 선언하면? → **외부 링크 충돌** 발생 (정의 중복)


  ### 컴파일러 처리 흐름 

  1. 각 `.c` 파일은 **개별적으로 컴파일**
  2. `static`으로 선언된 내부링크 식별자는 **그 파일 안에서만 유효**
  3. `extern` 또는 암시적 외부 링크 식별자는 **링커가 연결해 줌**
  4. 링크 충돌 시 → `multiple definition` 오류 발생


