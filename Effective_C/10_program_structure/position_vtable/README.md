**Opaque Handle + 함수 포인터 테이블(vtable)** 기반 다형성 구조

# 🧩 전체 구조 요약

```
PositionHandle*
  ├── data: void* → 실제 데이터 구조체 (int용 또는 float용)
  └── vtable: 함수 포인터 테이블df
                ├── move()
                ├── print()
                └── destroy()
```

사용자는 `PositionHandle*`만 알고, 내부에 어떤 타입이 있는지는 몰라요.  
**C에서 객체지향의 다형성(polymorphism)을 구현한 구조**입니다.

---

# ✅ 핵심 설계 목표

| 목표 | 설명 |
|------|------|
| 타입 은닉 (정보 은닉) | `struct Position_int`, `struct Position_float`는 내부에만 존재 |
| Opaque Handle | 사용자에겐 `void*` 데이터 포인터만 전달 |
| 다형성 | `move()`, `print()`, `destroy()`는 vtable을 통해 실행됨 |
| 타입별 분기 제거 | 외부에서는 타입 분기 조건이 전혀 없음 (`if (int)` 같은 거 없음)

---

## ✅ 1. `position.h` 설명

```c
typedef void* Position;
```

- 실제 데이터가 무엇인지 모르게 처리하기 위한 **추상 포인터 타입**
- 내부 구조는 알 수 없고 포인터만 주고받음

---

```c
typedef struct {
    void (*move)(Position, void* dx, void* dy);
    void (*print)(const Position);
    void (*destroy)(Position);
} PositionVTable;
```

- **가상 함수 테이블 (vtable)** 구조
- 각 포인터는 `int`, `float`에 따라 다른 구현 함수로 연결됨

---

```c
typedef struct {
    void* data;
    const PositionVTable* vtable;
} PositionHandle;
```

- 외부에서 사용하는 **공용 핸들**
- `data`는 실제 데이터의 포인터 (`Position_int*` or `Position_float*`)
- `vtable`은 해당 데이터 타입 전용 함수 테이블

---

```c
static inline void move_position(PositionHandle* p, void* dx, void* dy) {
    p->vtable->move(p->data, dx, dy);
}
```

- 사용자는 `move_position()` 하나만 호출
- 내부에서 `p->vtable->move()`를 통해 타입에 맞는 함수 자동 호출

같은 방식으로 `print_position()`, `destroy_position()`도 동작합니다.

---

## ✅ 2. `position_int.c` 설명

```c
typedef struct {
    int x, y;
} PositionInt;
```

- `int` 전용 구조체. 외부에 **노출되지 않음**

---

```c
static void move_int(Position p, void* dx, void* dy) {
    PositionInt* pi = (PositionInt*)p;
    pi->x += *(int*)dx;
    pi->y += *(int*)dy;
}
```

- `void*`인 `dx`, `dy`를 **int 포인터로 변환하여** 더함
- `Position` 역시 `void*`이므로 `PositionInt*`로 캐스팅

---

```c
static const PositionVTable int_vtable = {
    .move = move_int,
    .print = print_int,
    .destroy = destroy_int
};
```

- int용 함수 포인터 테이블 (vtable)
- 생성 시 `PositionHandle`에 이걸 붙여줌

---

```c
PositionHandle* create_position_int(int x, int y) {
    PositionInt* pi = malloc(sizeof(PositionInt));
    pi->x = x; pi->y = y;

    PositionHandle* handle = malloc(sizeof(PositionHandle));
    handle->data = pi;
    handle->vtable = &int_vtable;

    return handle;
}
```

- 구조체를 힙에 만들고,
- 핸들에 넣어서 리턴

---

## ✅ 3. `main.c` 설명

```c
int dx = 1, dy = 2;
float fx = 0.5f, fy = 1.5f;

PositionHandle* p1 = create_position_int(10, 20);
move_position(p1, &dx, &dy);    // int용 move 호출됨
print_position(p1);             // int용 print 호출됨
destroy_position(p1);           // 메모리 해제
```

- `PositionHandle*`만 사용하므로, 타입 분기 조건이 **외부에 없음**
- 내부는 알아서 vtable로 호출됨

---

## ✅ 최종 그림으로 이해하기

```
┌────────────────────┐
│  PositionHandle*   │
│ ┌──────────────┐   │
│ │ data (void*) │──▶ PositionInt { x=10, y=20 }
│ └──────────────┘   │
│ ┌──────────────┐   │
│ │ vtable       │──▶ move_int()
│ │              │    print_int()
│ │              │    destroy_int()
└────────────────────┘
```

