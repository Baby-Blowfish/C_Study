# C 프로그래밍 학습: 객체, 함수, 데이터 형식

## 파일 구성

### 1. `format.c`
C 언어의 다양한 데이터 타입과 형식을 다룹니다:
- 불리언 타입 (`_Bool`, `bool`)
- 문자 타입 (`char`, `signed char`, `unsigned char`)
- 숫자 타입 (정수형과 부동소수점)
- 열거형 타입
- void 타입
- 함수 타입
- 파생 타입 (포인터, 배열, 구조체)

### 2. `alignment.c`
메모리 정렬과 구조체 패딩 개념을 설명합니다:
- 구조체 정렬 요구사항
- 구조체 내 메모리 패딩
- `#pragma pack` 사용법
- 정렬 속성
- 패킹된 구조체 예제
- 정렬 제어의 일반적인 사용 사례

### 3. `switch.c`
변수 범위, 저장 기간, 함수 매개변수를 탐구합니다:
- 정적 vs 자동 저장 기간
- 전역 vs 지역 범위
- 매개변수 전달 메커니즘
- 함수 매개변수와 인자
- 정적 변수
- 변수 초기화
- 메모리 수명 관리

## 주요 학습 개념

### 저장 기간
- 정적 저장 기간
- 자동 저장 기간
- 스레드 저장 기간
- 할당 저장 기간

### 변수 분류
1. 저장 기간에 따른 분류:
   - 정적 변수
   - 자동 변수

2. 범위에 따른 분류:
   - 전역 변수
   - 지역 변수

### 메모리 정렬
- 구조체 패딩
- 정렬 요구사항
- 성능에 미치는 영향
- 정렬 제어의 일반적인 사용 사례

### 함수 매개변수
- 매개변수 전달 방식
- 값에 의한 호출
- 참조에 의한 호출 (포인터 사용)
- 매개변수 범위

## 사용 방법

각 소스 파일에는 개념에 대한 자세한 주석과 실제 예제가 포함되어 있습니다. 예제를 컴파일하고 실행하는 방법:

```bash
gcc -o 프로그램명 소스파일.c
./프로그램명
```

예시:
```bash
gcc -o alignment alignment.c
./alignment
```



**"쓰레드는 힙은 공유할 수 있지만, 스택은 공유할 수 없다"**

---

### 1. 힙(Heap)은 공유 가능
- **힙 메모리**는 `malloc()`, `new` 같은 함수로 **동적 할당**해서 사용하는 영역이야.
- **프로세스의 모든 쓰레드들은 힙 메모리를 공유**해.  
  → 어떤 쓰레드가 `malloc()`으로 메모리를 할당하거나 값을 바꿔도 다른 쓰레드가 그걸 **같이 볼 수 있어**.
  
**예시**
```c
// 공통 힙 메모리
int *shared = malloc(sizeof(int));
*shared = 10;  // 쓰레드 A가 10 저장
// 쓰레드 B도 shared를 보면 10이라고 나옴
```
**→ 힙은 같은 주소 공간을 공유하기 때문이야.**

---

### 2. 스택(Stack)은 공유 불가능
- **스택 메모리**는 **함수 호출**, **지역 변수** 등을 저장하는 곳이야.
- **각 쓰레드는 자기만의 스택을 따로 갖고 있어.**
  → 쓰레드마다 **함수 호출 기록**, **지역 변수** 등이 **개별적**이야.
  
**즉,**
- A 쓰레드의 스택에 있는 지역 변수는
- B 쓰레드가 **절대 직접 접근하거나 볼 수 없어.**

**예시**
```c
void *thread_func(void *arg)
{
    int local_var = 100;  // 이 local_var은 이 쓰레드의 스택에만 존재
    ...
}
```
**→ 여기 `local_var`는 이 쓰레드만 사용할 수 있고, 다른 쓰레드는 건드릴 수 없어.**

---

### 왜 이렇게 되어 있을까?
| 구분 | 이유 |
|:---|:---|
| 힙 공유 | 쓰레드끼리 데이터를 주고받거나 협력해서 작업하려고 |
| 스택 분리 | 함수 호출 중첩(콜스택 관리), 지역 변수 보호, 쓰레드 독립성 보장을 위해 |

**만약 스택을 공유하면?**
- 함수 호출이 꼬이거나, 지역 변수 값이 엉켜서 프로그램이 미친 듯이 오작동할 거야.
- 그래서 운영체제(OS)가 **스택은 쓰레드마다 따로** 만들어 주는 거야.


### 예제 제목
**"쓰레드 힙 메모리 공유 vs 스택 메모리 독립성 차이 실습"**

### 코드 파일 이름
`thread_memory_example.c`

---

### 코드

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int *shared_heap_var; // 힙에 있는 공유 변수

void *thread_func(void *arg)
{
    int local_stack_var = *(int *)arg; // 스택에 있는 지역 변수 (각자 따로)
    
    printf("[쓰레드 %ld] 힙 변수(shared_heap_var): %d\n", pthread_self(), *shared_heap_var);
    printf("[쓰레드 %ld] 스택 변수(local_stack_var): %d\n", pthread_self(), local_stack_var);

    // 힙과 스택 값을 변경해보기
    *shared_heap_var += 1;         // 힙은 공유되니까 다른 쓰레드에도 영향
    local_stack_var += 1;           // 스택은 복사본이라 다른 쓰레드에는 영향 없음

    printf("[쓰레드 %ld] 수정 후 힙 변수(shared_heap_var): %d\n", pthread_self(), *shared_heap_var);
    printf("[쓰레드 %ld] 수정 후 스택 변수(local_stack_var): %d\n", pthread_self(), local_stack_var);

    return NULL;
}

int main()
{
    pthread_t t1, t2;
    int arg1 = 100, arg2 = 200;

    // 힙 메모리 할당
    shared_heap_var = (int *)malloc(sizeof(int));
    if (shared_heap_var == NULL)
    {
        perror("malloc");
        exit(1);
    }
    *shared_heap_var = 1; // 초기값 1로 설정

    // 쓰레드 생성
    pthread_create(&t1, NULL, thread_func, (void *)&arg1);
    pthread_create(&t2, NULL, thread_func, (void *)&arg2);

    // 쓰레드 종료 대기
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // 최종 결과
    printf("[메인 쓰레드] 최종 힙 변수(shared_heap_var): %d\n", *shared_heap_var);

    free(shared_heap_var);
    return 0;
}
```

---

### 실행 결과 예시

```
[쓰레드 12345] 힙 변수(shared_heap_var): 1
[쓰레드 12345] 스택 변수(local_stack_var): 100
[쓰레드 67890] 힙 변수(shared_heap_var): 1
[쓰레드 67890] 스택 변수(local_stack_var): 200
[쓰레드 12345] 수정 후 힙 변수(shared_heap_var): 2
[쓰레드 12345] 수정 후 스택 변수(local_stack_var): 101
[쓰레드 67890] 수정 후 힙 변수(shared_heap_var): 3
[쓰레드 67890] 수정 후 스택 변수(local_stack_var): 201
[메인 쓰레드] 최종 힙 변수(shared_heap_var): 3
```

(※ 쓰레드가 순서대로 실행되지 않기 때문에 순서는 다를 수 있어.)

---

### 여기서 포인트!

| 구분 | 설명 |
|:---|:---|
| 힙 변수(shared_heap_var) | 두 쓰레드가 **같은 주소**를 바라보고 값을 변경 → 최종 값이 합쳐져서 변함 |
| 스택 변수(local_stack_var) | 각각 쓰레드가 **자기만의 복사본**을 만들어서 독립적으로 변경됨 → 서로 영향 없음 |

---


**"쓰레드 생성할 때 인수를 넘겨줄 때" 지역변수 주소 vs 전역변수 주소 vs 동적할당한 변수 주소 차이**

---

# ✅ 기본 구조
```c
pthread_create(&thread_id, NULL, thread_func, (void *)arg);
```
- 마지막 인수 `(void *)arg`로 **어떤 메모리 주소**를 넘겨줘.
- 그럼 쓰레드가 시작할 때, 그 주소를 받아서 사용해.

문제는,
**그 'arg'가 어디에 있는 메모리냐에 따라**  
**안전성**과 **수명**이 완전히 달라진다는 거야.

---

# ✅ 1. 지역변수 주소를 넘기는 경우

```c
void create_thread() {
    int local_var = 123;
    pthread_create(&tid, NULL, thread_func, (void *)&local_var);
}
```
- `local_var`는 `create_thread()` 함수의 **스택**에 존재.
- 함수가 리턴하면 **local_var는 사라지고**, **쓰레드는 댕글링 포인터**를 가지게 돼.
- ❗ 매우 위험:  
  **"함수 끝나고 메모리가 해제된 지역변수를 참조"** → **미정의 동작(undefined behavior)** 발생.

> 결론: 지역변수 주소를 넘기는 것은 매우 위험하고 절대 금지해야 한다.

---

# ✅ 2. 전역변수 주소를 넘기는 경우

```c
int global_var;

void create_thread() {
    global_var = 123;
    pthread_create(&tid, NULL, thread_func, (void *)&global_var);
}
```
- `global_var`는 프로그램이 끝날 때까지 살아있어.
- 따라서 쓰레드가 그 주소를 받아 사용해도 안전해.
- 단점은?
  - 여러 쓰레드가 **같은 전역변수를 동시에 수정**하면 **경쟁 상태(Race condition)** 발생할 수 있어.
  - 동기화(mutex 등) 필요.

> 결론: 전역변수는 메모리 안전성은 괜찮지만, **멀티스레드에서는 동시 접근 주의**해야 한다.

---

# ✅ 3. 동적할당한 변수 주소를 넘기는 경우

```c
void create_thread() {
    int *heap_var = malloc(sizeof(int));
    *heap_var = 123;
    pthread_create(&tid, NULL, thread_func, (void *)heap_var);
}
```
- `heap_var`는 **힙에 있으므로** 함수가 끝나도 살아있어.
- 쓰레드가 안전하게 그 메모리 주소를 사용할 수 있다.
- 다만,
  - 쓰레드가 사용을 끝낸 후에는 반드시 **free()로 해제**해야 메모리 누수(memory leak)가 없다.

> 결론: 동적할당은 메모리 안전성이 높고 유연하지만, **명시적인 free 필요**.

---

# ✅ 4. 차이를 한눈에 정리

| 구분 | 안전성 | 주의사항 |
|:---|:---|:---|
| 지역변수 주소 | ❌ 매우 위험 | 함수 종료 후 메모리 해제됨 (댕글링 포인터 발생) |
| 전역변수 주소 | ⭕ 안전 (수명은 OK) | 여러 쓰레드 동시 접근 시 동기화 필요 |
| 동적할당 변수 주소 | ⭕ 안전 (수명은 OK) | 사용 후 반드시 free() 필요 (메모리 누수 주의) |

---

# ✅ 5. 실제로는 어떻게 해야 하나?

**실무에서는 보통 이렇게 해:**
- **malloc()** 으로 동적할당해서 넘겨준다. (필요하면 구조체로 여러 값 묶어서)
- 쓰레드가 끝날 때 free() 한다.

또는  
- **pthread_create() 전에 복사본**을 만들어서 넘긴다.
- 예를 들어, **지역변수 복사본을 힙에 만들어서 넘긴다**.

---

# ✅ 6. 심화 예제: 안전한 방법 vs 위험한 방법

**(1) 잘못된 예시 (지역변수 주소 넘기기)**

```c
void *thread_func(void *arg) {
    int *p = (int *)arg;
    printf("%d\n", *p); // 위험: p가 가리키는 주소는 이미 유효하지 않을 수 있음
    return NULL;
}

void create_thread() {
    int local_var = 123;
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, (void *)&local_var);
    pthread_join(tid, NULL);
}
```
**문제점:**  
`create_thread()` 함수가 리턴하면 `local_var`는 무효한 메모리!

---

**(2) 안전한 예시 (동적할당 후 넘기기)**

```c
void *thread_func(void *arg) {
    int *p = (int *)arg;
    printf("%d\n", *p);
    free(p); // 사용 끝났으면 메모리 해제
    return NULL;
}

void create_thread() {
    int *heap_var = malloc(sizeof(int));
    *heap_var = 123;
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, (void *)heap_var);
    pthread_join(tid, NULL);
}
```
**포인트:**  
- 쓰레드에서 `free()` 해서 메모리 누수 방지.
- 안전하고 추천하는 방식.

---

# ✅ 7. 최종 요약 한 문장

> **"지역변수 주소를 넘기지 말고, 동적할당해서 넘기거나, 전역변수를 넘길 땐 동시접근에 주의하자."**

---


**"구조체로 여러 값 묶어서 쓰레드에 인수 넘기기 + free 자동화(pthread_cleanup_push)"**  

---

# ✅ 1. 구조체로 여러 값 넘기기

때로는 단순 int 하나 넘기는 게 아니라  
**여러 데이터를 한 번에** 쓰레드로 넘기고 싶을 때가 많아.

이럴 때는?  
**구조체를 만들고, 그 구조체를 힙에 할당해서 넘기면 돼.**

---

## 예제 1: 구조체를 사용해서 여러 값 넘기기

**코드 파일명**  
`thread_arg_struct_example.c`

---

### 코드

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int id;
    char message[64];
} ThreadArg;

void *thread_func(void *arg) {
    ThreadArg *targ = (ThreadArg *)arg;
    
    printf("[쓰레드 %d] 메시지: %s\n", targ->id, targ->message);

    free(targ); // 쓰레드에서 free() 해주기
    return NULL;
}

int main() {
    pthread_t tid;
    ThreadArg *arg = malloc(sizeof(ThreadArg));
    if (!arg) {
        perror("malloc");
        exit(1);
    }

    arg->id = 1;
    snprintf(arg->message, sizeof(arg->message), "안녕하세요, 스레드입니다!");

    pthread_create(&tid, NULL, thread_func, (void *)arg);
    pthread_join(tid, NULL);

    return 0;
}
```

---

## 결과

```
[쓰레드 1] 메시지: 안녕하세요, 스레드입니다!
```

---

## 설명
- `ThreadArg` 구조체 안에 `id`, `message` 같이 **여러 데이터를 하나로 묶었어.**
- `malloc`으로 구조체 하나를 힙에 할당해서 넘겼어.
- 쓰레드에서 다 쓰고 나면 `free()`로 메모리를 해제했어.

---

# ✅ 2. pthread_cleanup_push()로 free 자동화

**문제점**
- 만약 쓰레드 안에서 **에러로 조기 리턴**하거나,
- **cancel** 같은 걸로 **강제 종료**되면  
  → `free()`를 까먹고 메모리 누수(memory leak)될 수 있어.

**해결책**  
➔ `pthread_cleanup_push()`를 사용하면 된다!

`pthread_cleanup_push()`는  
> "쓰레드가 종료될 때 반드시 호출되는 정리(cleanup) 함수"를 등록하는 거야.

---

## 예제 2: pthread_cleanup_push()로 free 자동화

**코드 파일명**  
`thread_arg_struct_cleanup_example.c`

---

### 코드

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int id;
    char message[64];
} ThreadArg;

void cleanup(void *arg) {
    printf("[정리함수] 메모리 해제합니다.\n");
    free(arg);
}

void *thread_func(void *arg) {
    ThreadArg *targ = (ThreadArg *)arg;

    // 정리(cleanup) 함수 등록
    pthread_cleanup_push(cleanup, targ);

    printf("[쓰레드 %d] 메시지: %s\n", targ->id, targ->message);

    // 여기서 에러 발생해도 free가 자동으로 호출됨
    // pthread_exit(NULL); // 이렇게 조기 종료해도 cleanup 실행됨

    pthread_cleanup_pop(1); // 1: 등록된 cleanup 호출함

    return NULL;
}

int main() {
    pthread_t tid;
    ThreadArg *arg = malloc(sizeof(ThreadArg));
    if (!arg) {
        perror("malloc");
        exit(1);
    }

    arg->id = 2;
    snprintf(arg->message, sizeof(arg->message), "Cleanup 테스트입니다!");

    pthread_create(&tid, NULL, thread_func, (void *)arg);
    pthread_join(tid, NULL);

    return 0;
}
```

---

## 결과

```
[쓰레드 2] 메시지: Cleanup 테스트입니다!
[정리함수] 메모리 해제합니다.
```

---

## 설명
- `pthread_cleanup_push(cleanup, targ)` : **정리할 함수와 인수 등록**
- `pthread_cleanup_pop(1)` : **등록된 cleanup 호출**
- 만약 쓰레드가 에러로 중간에 종료돼도, 무조건 `cleanup()`이 호출돼서 메모리 누수 방지 가능.

---

# ✅ 3. 최종 요약

| 항목 | 설명 |
|:---|:---|
| 구조체 넘기기 | 여러 데이터를 하나로 묶어서 쓰레드로 전달할 수 있음 |
| free() 직접 호출 | 기본 방법. 하지만 예외 상황 누수 위험 존재 |
| pthread_cleanup_push() 사용 | 쓰레드 종료 시 자동으로 자원 해제. 안전하고 실무에서도 많이 사용 |

---

# ✅ 추가 심화로 갈 수 있는 주제

- `pthread_cleanup_push()`가 스택처럼 작동하는 이유
- `pthread_setcancelstate`, `pthread_setcanceltype`를 통한 쓰레드 취소 제어
- 쓰레드 풀(thread pool)에서 구조체 재활용하는 방법
- malloc/free 대신 pool allocator 사용하기 (성능 최적화)

---


# ✅ pthread_cleanup_push()

**너가 따로 pthread_cleanup_push()를 "만드는" 게 아니라,**  
코드에서 그냥 **써서 등록하면**  
→ pthread가 내부적으로 관리해주는 거야.

---

# ✅ pthread_cleanup_push() / pthread_cleanup_pop() 기본 형태

```c
void pthread_cleanup_push(void (*routine)(void *), void *arg);
void pthread_cleanup_pop(int execute);
```

- `pthread_cleanup_push(cleanup함수, 인수);`
  - 스레드가 종료될 때 호출할 **정리(cleanup) 함수**를 등록한다.
- `pthread_cleanup_pop(1);`
  - 스택처럼 등록된 cleanup을 **실행(1)** 하거나 **버림(0)**.

**하지만 주의할 점은!**  
이 둘은 **함수 호출이 아니라, 매크로**야.

즉,  
`pthread_cleanup_push()`와 `pthread_cleanup_pop()`은  
**C언어 문법상 항상 짝을 맞춰야 하고, 같은 블록 안에 있어야 해.**

---

# ✅ pthread_cleanup_push()의 매크로 구조 (참고용)

리눅스 시스템 소스(glibc pthread.h) 안을 보면 대략 이렇게 되어 있어:

```c
#define pthread_cleanup_push(routine, arg) \
  { \
    __pthread_cleanup_push((routine), (arg));

#define pthread_cleanup_pop(execute) \
    __pthread_cleanup_pop((execute)); \
  }
```

- 내부적으로는 숨겨진 함수 `__pthread_cleanup_push`, `__pthread_cleanup_pop`를 호출해.
- 그리고 `{ }`로 묶여있기 때문에 문법상 둘이 **항상 쌍으로 써야 한다**.

---

# ✅ 실제 코드 흐름 예시 다시 정리

```c
void cleanup(void *arg) {
    free(arg);
}

void *thread_func(void *arg) {
    pthread_cleanup_push(cleanup, arg); // 정리할 함수 등록

    // ... 작업 ...

    pthread_cleanup_pop(1); // 1: 등록된 cleanup 호출 (free 호출됨)

    return NULL;
}
```

---

# ✅ 중요한 주의사항 2개

1. **pthread_cleanup_push() 와 pthread_cleanup_pop()는 반드시 짝지어야 한다.**
   - 짝이 안 맞으면 컴파일 에러.
2. **코드 블록(scope)이 끝날 때 pthread_cleanup_pop()을 호출해야 한다.**
   - `{}` 내부에서 push-pop이 같이 있어야 한다.

**예시**

```c
void *thread_func(void *arg) {
    pthread_cleanup_push(cleanup, arg); // OK: push

    if (something_wrong) {
        pthread_exit(NULL); // 이때도 cleanup 호출됨
    }

    pthread_cleanup_pop(1); // OK: pop
}
```

**(❌ 이런 건 안 됨)**

```c
void *thread_func(void *arg) {
    pthread_cleanup_push(cleanup, arg); 
    // 중간에 return; // 이렇게 pthread_cleanup_pop() 없이 나가면 안 됨
}
```

---

# ✅ 최종 요약

| 항목 | 설명 |
|:---|:---|
| pthread_cleanup_push() | **함수를 등록**하는 매크로. 스레드가 종료되거나 cancel될 때 호출. |
| pthread_cleanup_pop() | 등록한 cleanup 함수를 **실행하거나 버리는 매크로**. 반드시 짝이 맞아야 함. |
| 직접 구현 필요? | ❌ 필요없음. 리눅스 pthread에 이미 포함돼 있음. 그냥 사용하면 됨. |
| 주의사항 | 항상 `{ pthread_cleanup_push(); ... pthread_cleanup_pop(); }` 한 블록 안에 써야 함. |

---



> **쓰레드를 강제로 종료시키더라도, 메모리를 누수 없이 자동 정리하는 것**!

---

# ✅ 1. 흐름 요약

- 메인 쓰레드가 워커(worker) 쓰레드를 **`pthread_cancel()`** 로 강제 종료 시킨다.
- 워커 쓰레드는 중간에 죽더라도, **`pthread_cleanup_push()`로 등록한 cleanup 함수가 호출**되어서 자원 해제가 된다.
- 누수 없이 깔끔하게 종료.

---

# ✅ 2. 예제 설계

**파일 이름**  
`thread_cancel_cleanup_example.c`

---

### 코드

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 자원 구조체
typedef struct {
    int id;
    char message[64];
} Task;

// cleanup 함수 (강제 종료시 호출)
void task_cleanup(void *arg) {
    Task *task = (Task *)arg;
    printf("[cleanup] 작업 ID %d: 메모리 해제\n", task->id);
    free(task);
}

// 워커 쓰레드 함수
void *worker_thread(void *arg) {
    Task *task = (Task *)arg;

    // cleanup 함수 등록
    pthread_cleanup_push(task_cleanup, task);

    printf("[워커 쓰레드] 작업 시작: ID=%d, 메시지=%s\n", task->id, task->message);

    // 아주 오래 걸리는 작업을 흉내 (sleep)
    for (int i = 0; i < 10; ++i) {
        printf("[워커 쓰레드] ID=%d 작업중... %d\n", task->id, i);
        sleep(1);
    }

    printf("[워커 쓰레드] 정상 종료: ID=%d\n", task->id);

    pthread_cleanup_pop(1); // cleanup 호출
    return NULL;
}

int main() {
    pthread_t tid;
    Task *task = malloc(sizeof(Task));
    if (!task) {
        perror("malloc");
        exit(1);
    }

    task->id = 42;
    snprintf(task->message, sizeof(task->message), "긴 작업입니다");

    pthread_create(&tid, NULL, worker_thread, (void *)task);

    sleep(3); // 워커가 열심히 일하는 중 기다림

    printf("[메인 쓰레드] 워커를 강제 종료합니다!\n");
    pthread_cancel(tid); // 워커 스레드 강제 종료 요청

    pthread_join(tid, NULL); // 워커 종료 대기

    printf("[메인 쓰레드] 프로그램 정상 종료\n");
    return 0;
}
```

---

# ✅ 3. 예상 실행 결과

```
[워커 쓰레드] 작업 시작: ID=42, 메시지=긴 작업입니다
[워커 쓰레드] ID=42 작업중... 0
[워커 쓰레드] ID=42 작업중... 1
[워커 쓰레드] ID=42 작업중... 2
[메인 쓰레드] 워커를 강제 종료합니다!
[cleanup] 작업 ID 42: 메모리 해제
[메인 쓰레드] 프로그램 정상 종료
```

---

# ✅ 4. 흐름 상세 설명

1. 메인 쓰레드가 `pthread_cancel()`로 워커 스레드를 종료시키려고 한다.
2. 워커 스레드가 `sleep()` 중이더라도, 취소 요청을 받으면, **현재 등록된 `pthread_cleanup_push()` 스택**을 따라 cleanup 함수가 호출된다.
3. `task_cleanup()`이 호출되어 `malloc`된 메모리를 **free()** 한다.
4. 메모리 누수 없이 깔끔하게 프로그램이 종료된다.

---

# ✅ 5. 심화 개념: `pthread_cancel`이 성공하려면?

- 스레드는 기본적으로 **취소 가능 상태**(cancelable state)여야 한다.
- `sleep()`, `pthread_cond_wait()`, `read()`, `write()` 같은 **blocking syscall** 중에는 취소 요청을 감지할 수 있어.

추가로 수동으로 취소 지점을 만들고 싶으면  
`pthread_testcancel();` 함수를 호출할 수 있어.  
(→ 이건 커스텀 취소 지점 만드는 고급 기법)

---

# ✅ 6. 최종 요약

| 항목 | 설명 |
|:---|:---|
| `pthread_cancel()` | 스레드에게 종료 요청을 보낸다 |
| `pthread_cleanup_push()` | 종료될 때 실행할 정리(cleanup) 함수 등록 |
| `sleep()` 같은 함수 안에서 | 취소 요청을 받아들이고 cleanup 함수 호출 |
| 결과 | 메모리 누수 없이 깨끗하게 자원 해제 가능 |

---




"**구조체 안에 포인터가 여러 개 있을 때 정리 순서를 자동화하는 방법**"  


---

# ✅ 문제 상황

- 구조체 안에 포인터가 여러 개 있다.
- 이 포인터들은 각각 동적할당되어 있다.
- 쓰레드가 끝나면 **이 포인터들도 다 free 해야 하고**, **구조체 자체도 free 해야 한다.**

**문제는**  
- 매번 수동으로 free()를 다 하려면 헷갈리고,  
- 중간에 하나라도 빠지면 메모리 누수(memory leak)가 생긴다.

**그래서**  
➔ **정리(cleanup)를 자동화하는 구조**를 만드는 게 중요하다.

---

# ✅ 1. 예제 문제 상황

```c
typedef struct {
    int id;
    char *name;
    char *description;
} Task;
```

- `name` 도 `malloc()`
- `description` 도 `malloc()`
- 그리고 마지막에 `Task` 구조체 자체도 `malloc()` 되어 있음.

---

# ✅ 2. 잘못된(귀찮은) 수동 정리 방법

```c
void free_task(Task *task) {
    free(task->name);
    free(task->description);
    free(task);
}
```

**문제점**
- 포인터가 하나 추가될 때마다 `free()` 코드도 추가해야 함.
- 까먹으면 바로 메모리 누수.

---

# ✅ 3. 정리 순서를 자동화하는 기본 방법

**패턴을 만드는 거야.**

**핵심은:**
- **항상 포인터는 NULL로 초기화하고,**
- **free할 때 NULL체크하고 해제하고, 다시 NULL로 만든다.**

---

## 🎯 좋은 free_task 함수 만들기

```c
void safe_free(void **ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL; // 더블 프리 방지
    }
}

void free_task(Task *task) {
    if (task) {
        safe_free((void **)&task->name);
        safe_free((void **)&task->description);
        safe_free((void **)&task);
    }
}
```

---

## 🎯 safe_free 함수 설명

| 동작 | 설명 |
|:---|:---|
| `ptr && *ptr` | 포인터가 NULL이 아니고, 가리키는 것도 NULL이 아닐 때만 free |
| `free(*ptr)` | 가리키는 메모리를 해제 |
| `*ptr = NULL` | 더블 프리 방지 |

---

# ✅ 4. 쓰레드 안에서 사용 예제

**파일 이름**  
`thread_struct_multiple_free.c`

---

### 전체 코드

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    int id;
    char *name;
    char *description;
} Task;

void safe_free(void **ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}

void free_task(Task *task) {
    if (task) {
        safe_free((void **)&task->name);
        safe_free((void **)&task->description);
        safe_free((void **)&task);
    }
}

void task_cleanup(void *arg) {
    free_task((Task *)arg);
}

void *worker_thread(void *arg) {
    Task *task = (Task *)arg;

    pthread_cleanup_push(task_cleanup, task);

    printf("[쓰레드] 작업 시작: id=%d, name=%s, description=%s\n", task->id, task->name, task->description);

    // 일하는 척
    sleep(1);

    printf("[쓰레드] 작업 완료: id=%d\n", task->id);

    pthread_cleanup_pop(1); // cleanup 호출

    return NULL;
}

int main() {
    pthread_t tid;
    Task *task = malloc(sizeof(Task));
    if (!task) {
        perror("malloc");
        exit(1);
    }

    task->id = 100;
    task->name = malloc(32);
    task->description = malloc(64);

    if (!task->name || !task->description) {
        perror("malloc");
        free_task(task);
        exit(1);
    }

    strcpy(task->name, "스레드 작업");
    strcpy(task->description, "여러 포인터를 가진 구조체 테스트");

    pthread_create(&tid, NULL, worker_thread, (void *)task);
    pthread_join(tid, NULL);

    printf("[메인] 프로그램 정상 종료\n");
    return 0;
}
```

---

# ✅ 5. 결과

```
[쓰레드] 작업 시작: id=100, name=스레드 작업, description=여러 포인터를 가진 구조체 테스트
[쓰레드] 작업 완료: id=100
[메인] 프로그램 정상 종료
```

(그리고 메모리 누수 없음. 👍)

---

# ✅ 6. 최종 구조 요약

| 항목 | 설명 |
|:---|:---|
| safe_free() | NULL 체크 + free + NULL 세팅 |
| free_task() | 구조체 안 모든 포인터와 자기 자신 free |
| pthread_cleanup_push() | 스레드가 강제 종료되더라도 안전하게 cleanup 호출 |
| 자동화된 정리 | 포인터가 추가돼도 free_task만 수정하면 됨 |

---

# ✅ 한 문장 요약

> **"구조체 안에 포인터가 여러 개 있으면 safe_free()를 만들어서 free 순서를 표준화하고 pthread_cleanup_push()로 자동화하자!"**

---

**"중첩 구조체까지 재귀적으로 안전하게 free하는 방법"**

---

# ✅ 1. 문제 상황

- **구조체 안에 또 다른 구조체**가 들어있다.
- 그리고 그 **안쪽 구조체에도 포인터가 있을 수 있다**.
- 이걸 free할 때 **깊이 따라가서 하나씩 전부 정리**해줘야 한다.

**(→ 이걸 "deep free"라고 부른다)**

---

# ✅ 2. 예제 상황

**중첩된 구조체 정의**

```c
typedef struct {
    char *street;
    char *city;
} Address;

typedef struct {
    int id;
    char *name;
    Address *address; // 중첩 구조체 (포인터)
} Person;
```

- `Person`은 `Address *`를 갖고 있고,
- `Address`도 `street`, `city`를 동적할당 받는다.

---

# ✅ 3. 잘못된(부분) free 예시

```c
void free_person(Person *p) {
    free(p->name);
    free(p); // ❌ address 안에 있는 메모리는 아직 살아있음 (메모리 누수!)
}
```

**문제점**  
- `p->address->street`, `p->address->city` 메모리는 해제되지 않아서 **메모리 누수(memory leak)**가 발생한다.

---

# ✅ 4. 올바른 재귀적 free 방법

**구조체 안에 또 구조체가 있으면,  
그 구조체를 free하는 전용 함수를 따로 만들고, 호출해주자.**

---

## 🎯 안전한 free 함수 작성

```c
void safe_free(void **ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}

void free_address(Address *addr) {
    if (addr) {
        safe_free((void **)&addr->street);
        safe_free((void **)&addr->city);
        safe_free((void **)&addr);
    }
}

void free_person(Person *p) {
    if (p) {
        safe_free((void **)&p->name);
        free_address(p->address); // 재귀적으로 내부 구조체도 해제
        safe_free((void **)&p);
    }
}
```

---

# ✅ 5. 전체 실습 예제

**파일 이름**  
`recursive_struct_free.c`

---

### 코드

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    char *street;
    char *city;
} Address;

typedef struct {
    int id;
    char *name;
    Address *address;
} Person;

void safe_free(void **ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}

void free_address(Address *addr) {
    if (addr) {
        safe_free((void **)&addr->street);
        safe_free((void **)&addr->city);
        safe_free((void **)&addr);
    }
}

void free_person(Person *p) {
    if (p) {
        safe_free((void **)&p->name);
        free_address(p->address);
        safe_free((void **)&p);
    }
}

void person_cleanup(void *arg) {
    free_person((Person *)arg);
}

void *worker_thread(void *arg) {
    Person *person = (Person *)arg;

    pthread_cleanup_push(person_cleanup, person);

    printf("[쓰레드] 이름: %s, 주소: %s, %s\n",
           person->name,
           person->address->street,
           person->address->city);

    sleep(1); // 일하는 척

    pthread_cleanup_pop(1); // cleanup 호출

    return NULL;
}

int main() {
    pthread_t tid;
    Person *p = malloc(sizeof(Person));
    if (!p) {
        perror("malloc");
        exit(1);
    }

    p->id = 1;
    p->name = malloc(32);
    p->address = malloc(sizeof(Address));

    if (!p->name || !p->address) {
        perror("malloc");
        free_person(p);
        exit(1);
    }

    p->address->street = malloc(64);
    p->address->city = malloc(32);

    if (!p->address->street || !p->address->city) {
        perror("malloc");
        free_person(p);
        exit(1);
    }

    strcpy(p->name, "김효진");
    strcpy(p->address->street, "서울특별시 금천구 가산동");
    strcpy(p->address->city, "서울");

    pthread_create(&tid, NULL, worker_thread, (void *)p);
    pthread_join(tid, NULL);

    printf("[메인] 프로그램 정상 종료\n");
    return 0;
}
```

---

# ✅ 6. 결과

```
[쓰레드] 이름: 김효진, 주소: 서울특별시 금천구 가산동, 서울
[메인] 프로그램 정상 종료
```

(메모리 누수 없음!)

---

# ✅ 7. 최종 요약

| 포인트 | 설명 |
|:---|:---|
| 구조체 안에 구조체가 있으면 | 그 구조체를 위한 별도 free 함수도 만들어야 한다 |
| safe_free() | 모든 포인터는 free하고 NULL로 세팅 |
| 재귀적 free | 구조체 → 내부 포인터 → 내부 구조체 → 내부 구조체의 포인터... 순서대로 |

---

# ✅ 한 문장 요약

> **"구조체 안에 또 다른 구조체가 있다면, 각각의 free 함수를 만들어서 재귀적으로 안전하게 메모리를 해제한다."**

---


**"메모리 풀(Memory Pool)"** 


---

# ✅ 메모리 풀(Memory Pool) 이란?

**정의**
> **메모리 풀**은,  
> **필요할 때마다 malloc()/free()를 반복하는 대신**,  
> **큰 덩어리 메모리를 미리 한번 malloc 해두고**  
> 그 안에서 **조금씩 잘라서 빌려주고, 반납받는** 시스템이다.

---

# ✅ 왜 메모리 풀이 필요할까?

| 기존 방식 (`malloc/free`) | 메모리 풀 |
|:---|:---|
| 매번 malloc() → 커널에 요청 | 한 번 크게 malloc |
| 매번 free() → 커널에 반납 | 내부에서 빌리고 반납만 함 (fast) |
| 요청마다 힙이 쪼개지고 단편화(fragmentation) 생김 | 단편화 없음 |
| 속도가 느려질 수 있음 | 매우 빠름 |
| 멀티쓰레드에서는 lock contention 발생 위험 | 미리 관리하면 줄일 수 있음 |

---

# ✅ 메모리 풀을 쉽게 비유하면

**비유 1: 호텔 객실**

- `malloc()` = 방을 매번 새로 짓고 부수는 것.
- **Memory Pool** = 호텔을 미리 지어두고 손님이 왔다 갔다 할 때 방만 배정.

**비유 2: 주차장**

- 매번 땅을 사서 차 대는 게 아니고
- 미리 주차장을 만들어 놓고 칸만 빌려주는 것.

---

# ✅ 기본 동작 흐름

```
[처음 시작할 때] → 메모리 블록 크게 하나 malloc()
[요청이 오면] → 미리 나눠놓은 조각 하나를 빌려줌
[요청이 끝나면] → 조각을 반납
[종료할 때] → 전체 블록 한번에 free()
```

---

# ✅ 메모리 풀 구조 예시

### 1. 단순 구조
(고정 크기 객체만)

```c
struct MemoryPool {
    void *pool_start;    // 메모리 블록 시작 주소
    size_t chunk_size;   // 하나 조각 크기
    int total_chunks;    // 전체 조각 개수
    int *used;           // 조각 사용 여부 배열 (0: free, 1: used)
};
```

- `pool_start` : 큰 메모리 블록
- `chunk_size` : 한 조각 크기
- `used[i]` : 조각 i가 사용 중인지 아닌지

---

### 2. free list 방식 구조 (고급)

```c
struct Chunk {
    struct Chunk *next; // 다음 free chunk
};
```

- 빈 조각들을 **연결 리스트(linked list)** 로 관리
- 할당/반납이 훨씬 빠름 (`malloc`보다 10배 이상 빠를 수 있음)

---

# ✅ 메모리 풀 어디서 쓸까?

| 분야 | 메모리 풀 사용 이유 |
|:---|:---|
| 서버 (HTTP 서버, 게임 서버) | 초당 수천~수만 개 객체를 생성/삭제해야 해서 |
| 실시간 시스템 (로봇, 항공) | 메모리 요청 속도가 예측 가능해야 해서 |
| 게임 엔진 | 많은 오브젝트를 빠르게 관리해야 해서 |
| 네트워크 통신 | 패킷 버퍼(pool) 관리 |

---

# ✅ 한 문장 요약

> **"메모리 풀은 메모리를 미리 크게 준비해두고, 빌려주고 반납하는 방식으로, malloc/free보다 훨씬 빠르고 안정적인 메모리 관리 기술이다."**

---

# ✅ 정리

| 구분 | 메모리 풀 | malloc/free |
|:---|:---|
| 메모리 요청 속도 | 매우 빠름 | 상대적으로 느림 |
| 메모리 파편화 | 없음 | 있음 |
| 예측 가능성 | 매우 좋음 | 없음 |
| 구현 복잡성 | 조금 복잡함 | 매우 간단 |

---

좋아.  
지금부터 진짜 고급으로,  
**"free list 기반 고급 메모리 풀"** 을  
**서버급 수준**으로 차근차근 같이 만들어보자.

**(코드 + 설계 흐름 + 내부 메커니즘까지 전부 설명할게)**

---

# ✅ 1. 목표

- 고정 크기(fixed-size) 블록들을 관리하는 고성능 메모리 풀
- 메모리를 **free list(연결 리스트)** 로 관리
- **malloc/free 없이** 풀 안에서 할당/반납
- **메모리 파편화 없음**
- **할당/반납 속도 O(1)** (거의 제로 코스트)

---

# ✅ 2. 기본 설계 아이디어

## 메모리 풀 구조

```c
struct MemoryPool {
    void *pool_start;          // 풀 전체 시작 주소
    struct FreeChunk *free_list; // 현재 사용 가능한 블록들의 연결 리스트
    size_t chunk_size;         // 블록 하나 크기
    size_t total_chunks;       // 총 블록 개수
};
```

## 블록(Chunk) 구조

```c
struct FreeChunk {
    struct FreeChunk *next;  // 다음 사용 가능한 블록
};
```

- 풀은 전체를 큰 메모리 하나로 할당
- 블록마다 다음 free 블록을 가리키게 해서 연결 리스트 구성

---

# ✅ 3. 그림으로 동작 이해

초기 상태:
```
+--------+    +--------+    +--------+    +--------+
| Chunk0 | -> | Chunk1 | -> | Chunk2 | -> | NULL   |
+--------+    +--------+    +--------+    +--------+
```
(모든 블록이 free 상태)

---

할당 (alloc) 할 때:
- free_list에서 맨 앞 Chunk 꺼냄
- free_list를 다음 Chunk로 이동

---

반납 (free) 할 때:
- 반환하는 Chunk를 free_list 맨 앞으로 넣음
- 다시 연결 리스트에 복귀

---

# ✅ 4. 코드 작성

**파일 이름**  
`memory_pool_freelist.c`

---

### 전체 코드

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FreeChunk {
    struct FreeChunk *next;
} FreeChunk;

typedef struct {
    void *pool_start;
    FreeChunk *free_list;
    size_t chunk_size;
    size_t total_chunks;
} MemoryPool;

// 메모리 풀 초기화
MemoryPool *memory_pool_create(size_t chunk_size, size_t total_chunks) {
    MemoryPool *pool = malloc(sizeof(MemoryPool));
    if (!pool) return NULL;

    pool->chunk_size = (chunk_size > sizeof(FreeChunk *)) ? chunk_size : sizeof(FreeChunk *);
    pool->total_chunks = total_chunks;
    pool->pool_start = malloc(pool->chunk_size * total_chunks);
    if (!pool->pool_start) {
        free(pool);
        return NULL;
    }

    // 초기 free list 설정
    pool->free_list = (FreeChunk *)pool->pool_start;
    FreeChunk *current = pool->free_list;

    for (size_t i = 1; i < total_chunks; ++i) {
        current->next = (FreeChunk *)((char *)pool->pool_start + i * pool->chunk_size);
        current = current->next;
    }
    current->next = NULL; // 마지막 노드는 NULL

    return pool;
}

// 메모리 풀에서 하나 할당
void *memory_pool_alloc(MemoryPool *pool) {
    if (!pool->free_list) {
        return NULL; // 풀에 남은 블록 없음
    }
    FreeChunk *chunk = pool->free_list;
    pool->free_list = chunk->next;
    return (void *)chunk;
}

// 메모리 풀에 하나 반납
void memory_pool_free(MemoryPool *pool, void *ptr) {
    if (!ptr) return;
    FreeChunk *chunk = (FreeChunk *)ptr;
    chunk->next = pool->free_list;
    pool->free_list = chunk;
}

// 메모리 풀 삭제
void memory_pool_destroy(MemoryPool *pool) {
    if (pool) {
        free(pool->pool_start);
        free(pool);
    }
}
```

---

# ✅ 5. 사용 예제

```c
typedef struct {
    int id;
    char name[32];
} MyStruct;

int main() {
    MemoryPool *pool = memory_pool_create(sizeof(MyStruct), 100);
    if (!pool) {
        perror("memory_pool_create");
        return 1;
    }

    // 5개 구조체 할당
    MyStruct *a = (MyStruct *)memory_pool_alloc(pool);
    MyStruct *b = (MyStruct *)memory_pool_alloc(pool);
    MyStruct *c = (MyStruct *)memory_pool_alloc(pool);
    MyStruct *d = (MyStruct *)memory_pool_alloc(pool);
    MyStruct *e = (MyStruct *)memory_pool_alloc(pool);

    strcpy(a->name, "구조체 A");
    strcpy(b->name, "구조체 B");

    printf("A: %s\n", a->name);
    printf("B: %s\n", b->name);

    // 반납
    memory_pool_free(pool, b);
    memory_pool_free(pool, a);

    // 메모리 풀 삭제
    memory_pool_destroy(pool);
    return 0;
}
```

---

# ✅ 6. 성능/특징

| 항목 | 내용 |
|:---|:---|
| 메모리 할당/반납 속도 | O(1) 초고속 |
| 단편화(fragmentation) | 없음 |
| 메모리 낭비 | 약간 있음 (chunk size 올림 처리) |
| 커널 syscall 없음 | malloc/free 거의 없음 (처음 한 번만) |
| 실시간성 | 매우 좋음 (RTOS, 서버에 적합) |

---

# ✅ 7. 심화 개선 포인트

- 풀 부족 시 자동 확장 (realloc or 추가 풀 생성)
- 다중 사이즈 풀 (small/medium/large chunk 따로 관리)
- thread-safe 버전 (mutex나 lock-free 큐 사용)
- memory pool statistics (할당/반납 개수 모니터링)

---

# ✅ 한 문장 요약

> **"free list 기반 메모리 풀은 초고속 메모리 할당/반납을 가능하게 해서 서버, 실시간 시스템에 최적화된 구조이다."**

---

좋아,  
지금부터 진짜 **"Thread-safe Memory Pool"** (멀티쓰레드용 메모리 풀)  
**서버/게임 엔진급**으로 완성도 높게 같이 만들어볼게.

---

# ✅ 1. 목표

> "여러 쓰레드가 동시에 메모리 풀에서 alloc/free 해도,  
>  충돌 없이 안정적으로 동작하는 메모리 풀"을 만든다.

---

# ✅ 2. 문제점: 기존 메모리 풀은 thread-safe가 아니다

- 기존 메모리 풀은 `free_list`를 그냥 조작했어.
- 그런데 만약 여러 쓰레드가 동시에 `memory_pool_alloc()` / `memory_pool_free()`를 호출하면?
  - **free_list 포인터가 충돌해서 터진다(segfault 등).**

---

# ✅ 3. 해결 방법

## 기본 해결책: **mutex**로 보호하기

- `memory_pool_alloc()`, `memory_pool_free()`를 호출할 때마다
- **mutex를 lock/unlock**해서 동기화하면 된다.

(처음에는 간단하게 mutex 버전부터 만들고, 나중에 lock-free로 갈 수도 있어)

---

# ✅ 4. 전체 설계 구조

기존 구조 + mutex 추가

```c
typedef struct {
    void *pool_start;        // 풀 전체 시작
    struct FreeChunk *free_list; // 사용 가능한 블록 목록
    size_t chunk_size;       // 블록 하나 크기
    size_t total_chunks;     // 블록 수
    pthread_mutex_t lock;    // 🔥 동기화용 mutex 추가
} MemoryPool;
```

---

# ✅ 5. 코드 작성

**파일 이름**  
`thread_safe_memory_pool.c`

---

### 전체 코드

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct FreeChunk {
    struct FreeChunk *next;
} FreeChunk;

typedef struct {
    void *pool_start;
    FreeChunk *free_list;
    size_t chunk_size;
    size_t total_chunks;
    pthread_mutex_t lock; // 🔥
} MemoryPool;

// 메모리 풀 초기화
MemoryPool *memory_pool_create(size_t chunk_size, size_t total_chunks) {
    MemoryPool *pool = malloc(sizeof(MemoryPool));
    if (!pool) return NULL;

    pool->chunk_size = (chunk_size > sizeof(FreeChunk *)) ? chunk_size : sizeof(FreeChunk *);
    pool->total_chunks = total_chunks;
    pool->pool_start = malloc(pool->chunk_size * total_chunks);
    if (!pool->pool_start) {
        free(pool);
        return NULL;
    }

    pthread_mutex_init(&pool->lock, NULL); // 🔥 mutex 초기화

    pool->free_list = (FreeChunk *)pool->pool_start;
    FreeChunk *current = pool->free_list;

    for (size_t i = 1; i < total_chunks; ++i) {
        current->next = (FreeChunk *)((char *)pool->pool_start + i * pool->chunk_size);
        current = current->next;
    }
    current->next = NULL;

    return pool;
}

// 메모리 풀에서 하나 할당 (thread-safe)
void *memory_pool_alloc(MemoryPool *pool) {
    pthread_mutex_lock(&pool->lock); // 🔥 락 걸기

    if (!pool->free_list) {
        pthread_mutex_unlock(&pool->lock);
        return NULL;
    }
    FreeChunk *chunk = pool->free_list;
    pool->free_list = chunk->next;

    pthread_mutex_unlock(&pool->lock); // 🔥 락 풀기
    return (void *)chunk;
}

// 메모리 풀에 하나 반납 (thread-safe)
void memory_pool_free(MemoryPool *pool, void *ptr) {
    if (!ptr) return;

    pthread_mutex_lock(&pool->lock); // 🔥 락 걸기

    FreeChunk *chunk = (FreeChunk *)ptr;
    chunk->next = pool->free_list;
    pool->free_list = chunk;

    pthread_mutex_unlock(&pool->lock); // 🔥 락 풀기
}

// 메모리 풀 삭제
void memory_pool_destroy(MemoryPool *pool) {
    if (pool) {
        pthread_mutex_destroy(&pool->lock); // 🔥 mutex 해제
        free(pool->pool_start);
        free(pool);
    }
}
```

---

# ✅ 6. 사용 예제

**멀티쓰레드 환경에서 테스트하기**

```c
typedef struct {
    int id;
    char name[32];
} MyStruct;

void *thread_func(void *arg) {
    MemoryPool *pool = (MemoryPool *)arg;
    for (int i = 0; i < 1000; ++i) {
        MyStruct *obj = (MyStruct *)memory_pool_alloc(pool);
        if (obj) {
            obj->id = i;
            snprintf(obj->name, sizeof(obj->name), "객체 %d", i);
            memory_pool_free(pool, obj);
        }
    }
    return NULL;
}

int main() {
    const int NUM_THREADS = 4;
    pthread_t threads[NUM_THREADS];

    MemoryPool *pool = memory_pool_create(sizeof(MyStruct), 10000);

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, thread_func, (void *)pool);
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    memory_pool_destroy(pool);
    printf("[메인] 메모리 풀 사용 완료.\n");
    return 0;
}
```

---

# ✅ 7. 결과

- 여러 쓰레드가 동시에 메모리 할당/반납해도 문제 없음.
- segfault 없음, memory leak 없음.

---

# ✅ 8. 최종 구조 요약

| 항목 | 내용 |
|:---|:---|
| 할당/반납 | mutex lock 걸고 free_list 조작 |
| thread-safe | 모든 쓰레드가 동시에 접근해도 안전 |
| 성능 | malloc/free보다 훨씬 빠름 (lock 오버헤드는 조금 있음) |

---

# ✅ 한 문장 요약

> **"thread-safe memory pool은 mutex로 free list를 보호해서, 멀티쓰레드 환경에서도 빠르고 안전한 메모리 관리를 가능하게 한다."**

---


좋아,  
지금까지 우리가 설계한 걸 **깔끔하고 체계적으로 정리해서**,  
**실제 최종 버전 코드**를 바로 쓸 수 있도록  
**코드 + 동작 설명**까지 다시 완벽하게 만들어줄게.

---

# ✅ 최종 목표 요약

- **Thread-safe MemoryPool** 사용 (mutex)
- **전역 변수 없이** 메모리 풀 명시적으로 전달
- **Task 구조체** 안에 **포인터**와 **중첩 구조체(SubTask)** 존재
- **safe_free()**, **free_subtask()**, **free_task()** 재귀적 메모리 해제
- **pthread_cleanup_push()** 로 스레드 종료시 자원 자동 해제

---

# ✅ 1. 구조체 정의

```c
// 하위 작업 구조체
typedef struct {
    char *detail; // SubTask 세부 정보
} SubTask;

// 메인 작업 구조체
typedef struct {
    int id;
    char *name;    // Task 이름
    SubTask *subtask; // SubTask를 가리키는 포인터
} Task;
```

---

# ✅ 2. MemoryPool 구조체 및 함수 선언

```c
#include <pthread.h>

typedef struct FreeChunk {
    struct FreeChunk *next;
} FreeChunk;

typedef struct {
    void *pool_start;
    FreeChunk *free_list;
    size_t chunk_size;
    size_t total_chunks;
    pthread_mutex_t lock;
} MemoryPool;

// MemoryPool 관련 함수 선언
MemoryPool *memory_pool_create(size_t chunk_size, size_t total_chunks);
void *memory_pool_alloc(MemoryPool *pool);
void memory_pool_free(MemoryPool *pool, void *ptr);
void memory_pool_destroy(MemoryPool *pool);
```

---

# ✅ 3. MemoryPool 함수 구현

### memory_pool_create()

```c
MemoryPool *memory_pool_create(size_t chunk_size, size_t total_chunks) {
    MemoryPool *pool = malloc(sizeof(MemoryPool));
    if (!pool) return NULL;

    pool->chunk_size = (chunk_size > sizeof(FreeChunk *)) ? chunk_size : sizeof(FreeChunk *);
    pool->total_chunks = total_chunks;
    pool->pool_start = malloc(pool->chunk_size * total_chunks);
    if (!pool->pool_start) {
        free(pool);
        return NULL;
    }

    pthread_mutex_init(&pool->lock, NULL);

    // free_list 초기화
    FreeChunk *current = (FreeChunk *)pool->pool_start;
    for (size_t i = 1; i < total_chunks; ++i) {
        current->next = (FreeChunk *)((char *)pool->pool_start + i * pool->chunk_size);
        current = current->next;
    }
    current->next = NULL;

    pool->free_list = (FreeChunk *)pool->pool_start;
    return pool;
}
```

---

### memory_pool_alloc()

```c
void *memory_pool_alloc(MemoryPool *pool) {
    pthread_mutex_lock(&pool->lock);

    if (!pool->free_list) {
        pthread_mutex_unlock(&pool->lock);
        return NULL;
    }

    FreeChunk *chunk = pool->free_list;
    pool->free_list = chunk->next;

    pthread_mutex_unlock(&pool->lock);
    return (void *)chunk;
}
```

---

### memory_pool_free()

```c
void memory_pool_free(MemoryPool *pool, void *ptr) {
    if (!ptr) return;

    pthread_mutex_lock(&pool->lock);

    FreeChunk *chunk = (FreeChunk *)ptr;
    chunk->next = pool->free_list;
    pool->free_list = chunk;

    pthread_mutex_unlock(&pool->lock);
}
```

---

### memory_pool_destroy()

```c
void memory_pool_destroy(MemoryPool *pool) {
    if (pool) {
        pthread_mutex_destroy(&pool->lock);
        free(pool->pool_start);
        free(pool);
    }
}
```

---

# ✅ 4. 자원 해제 함수 (safe_free, free_subtask, free_task)

### safe_free()

```c
void safe_free(void **ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}
```

---

### free_subtask()

```c
void free_subtask(SubTask *sub) {
    if (sub) {
        safe_free((void **)&sub->detail);
        free(sub);
    }
}
```

---

### free_task()

```c
void free_task(Task *task) {
    if (task) {
        safe_free((void **)&task->name);
        free_subtask(task->subtask);
    }
}
```

---

# ✅ 5. 스레드 작업 함수

**task_cleanup() + thread_func()**

---

### task_cleanup()

```c
void task_cleanup(void *arg) {
    struct {
        MemoryPool *pool;
        Task *task;
    } *ctx = arg;

    free_task(ctx->task);
    memory_pool_free(ctx->pool, ctx->task);
    free(ctx);
}
```

---

### thread_func()

```c
void *thread_func(void *arg) {
    MemoryPool *pool = (MemoryPool *)arg;

    Task *task = (Task *)memory_pool_alloc(pool);
    if (!task) {
        perror("memory_pool_alloc");
        return NULL;
    }
    memset(task, 0, sizeof(Task)); // 초기화

    struct {
        MemoryPool *pool;
        Task *task;
    } *ctx = malloc(sizeof(*ctx));
    if (!ctx) {
        memory_pool_free(pool, task);
        perror("malloc");
        return NULL;
    }
    ctx->pool = pool;
    ctx->task = task;

    pthread_cleanup_push(task_cleanup, (void *)ctx);

    // 메모리 할당
    task->id = (int)pthread_self();
    task->name = strdup("메인 작업 이름");
    task->subtask = malloc(sizeof(SubTask));
    if (task->subtask) {
        memset(task->subtask, 0, sizeof(SubTask));
        task->subtask->detail = strdup("서브 작업 세부사항");
    }

    printf("[스레드 %lu] 작업: %s -> %s\n",
           (unsigned long)pthread_self(),
           task->name,
           task->subtask ? task->subtask->detail : "없음");

    sleep(1); // 작업 수행

    pthread_cleanup_pop(1); // cleanup 호출
    return NULL;
}
```

---

# ✅ 6. 메인 함수

```c
int main() {
    pthread_t tid;
    MemoryPool *pool = memory_pool_create(sizeof(Task), 100);
    if (!pool) {
        perror("memory_pool_create");
        return 1;
    }

    pthread_create(&tid, NULL, thread_func, (void *)pool);
    pthread_join(tid, NULL);

    memory_pool_destroy(pool);

    printf("[메인] 프로그램 정상 종료\n");
    return 0;
}
```

---

# ✅ 7. 흐름 요약

```
메인 시작
 └── MemoryPool 생성
 └── pthread_create()로 thread_func 호출
       └── MemoryPool에서 Task 할당
       └── name, subtask, subtask->detail 메모리 할당
       └── pthread_cleanup_push(task_cleanup)
            └── free_task(): 내부 포인터 해제
            └── memory_pool_free(Task 구조체 반환)
            └── context 메모리 free
 └── pthread_join()
 └── MemoryPool destroy
 └── 프로그램 정상 종료
```

---

# ✅ 최종 검토

| 항목 | 상태 |
|:---|:---|
| 전역변수 없음 | ✅ |
| MemoryPool thread-safe | ✅ |
| 구조체 내부 포인터 안전 해제 | ✅ |
| 중첩 구조체(SubTask) 안전 해제 | ✅ |
| 스레드 cancel 대응 | ✅ (pthread_cleanup_push) |
| 자원 누수 없음 | ✅ |

---

# ✅ 진짜 한 문장 최종 요약

> **"MemoryPool thread-safe, 구조체 안 중첩 구조체+포인터 재귀적 안전 해제, 스레드 종료시 자동 정리까지 완벽히 관리하는 서버급 메모리 관리 구조."**

---
