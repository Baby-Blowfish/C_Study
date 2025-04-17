
## 📁 구성 설명

| 파일 | 설명 |
|------|------|
| `mymath.h` | add, square 함수의 선언 (공개 인터페이스) |
| `mymath.c` | 함수의 실제 구현 |
| `main.c` | 라이브러리를 사용하는 사용자 프로그램 |
| `Makefile` | static & shared 라이브러리 빌드 및 실행파일 생성

---

## 🛠 사용법

```bash
make static      # 정적 라이브러리로 빌드
./main_static    # 실행

make shared      # 동적 라이브러리로 빌드
./main_shared    # 실행

make clean       # 생성된 파일 정리
```

---

## 🧠 이 구조의 핵심 요점

| 개념 | 적용 |
|------|------|
| 인터페이스 분리 | `mymath.h`에만 선언, `mymath.c`에는 구현 |
| 정적 링크 | `libmymath.a` 생성 후 실행파일에 통합 |
| 동적 링크 | `libmymath.so` 생성 후 런타임에 로딩 (rpath 설정됨) |

## 링크