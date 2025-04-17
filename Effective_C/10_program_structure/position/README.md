# Position Management System (위치 관리 시스템)

이 프로젝트는 C언어에서 제네릭 프로그래밍을 활용한 2D 위치 관리 시스템을 구현한 예제입니다.

This project demonstrates a 2D position management system implemented using generic programming in C.

## 주요 기능 (Features)

- 정수형(int)과 실수형(float) 좌표 지원
- _Generic을 활용한 타입별 자동 함수 선택
- 메모리 안전성을 고려한 동적 할당 및 해제
- 캡슐화된 구조체 설계

## 사용 예시 (Usage Example)

```c
// 정수형 위치 생성 및 조작
Position_int* p1 = create_position(10, 20);    // 자동으로 int 버전 선택
move_position(p1, 1, 2);                       // 위치 이동
print_position(p1);                            // 위치 출력
destroy_position(p1);                          // 메모리 해제

// 실수형 위치 생성 및 조작
Position_float* p2 = create_position(1.5f, 2.5f);  // 자동으로 float 버전 선택
move_position(p2, 0.5f, 0.5f);                     // 위치 이동
print_position(p2);                                // 위치 출력
destroy_position(p2);                              // 메모리 해제
```

## API 함수 (API Functions)

### 생성 및 소멸 (Creation and Destruction)
- `create_position(x, y)`: 새로운 위치 객체 생성
- `destroy_position(p)`: 위치 객체 메모리 해제

### 조작 및 출력 (Manipulation and Output)
- `move_position(p, dx, dy)`: 상대적 위치 이동
- `print_position(p)`: 현재 위치 출력

## 컴파일 방법 (Compilation)

```bash
gcc -o pos main.c position.c
```

## 구현 특징 (Implementation Details)

- 내부 구조체 정의를 숨기고 불완전 타입으로 선언하여 캡슐화
- _Generic 매크로를 사용하여 타입에 따른 함수 자동 선택
- NULL 포인터 검사를 통한 안전한 메모리 처리
- 각 타입별 전용 함수 구현으로 타입 안전성 보장 