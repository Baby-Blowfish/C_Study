# ✅ 설계 목표

- `collection.h`에는 **인터페이스만 노출**
- 내부 구현은 `collection_array.c`, `collection_list.c`, `collection_hash.c`로 분리
- 사용자는 **어떤 자료구조를 쓰는지 몰라도** 동일한 함수로 사용 가능

---

## 📁 구조 설계

```
collection/
├── collection.h               ← 공용 인터페이스
├── collection_array.c         ← 배열 기반 구현
├── collection_list.c          ← 연결 리스트 기반 구현
├── collection_hash.c          ← 해시 테이블 기반 구현
├── main.c                     ← 사용 예제
```


## 🧠 구조 요약

| 요소 | 역할 |
|------|------|
| `collection.h` | 공용 인터페이스 제공 (불투명 포인터 사용) |
| `collection_*.c` | 내부 구현 (배열, 리스트, 해시) 별도 제공 |
| `main.c` | 구현체가 뭔지 몰라도 사용 가능 |  

---

## 🔁 구현 교체 방법

```bash
# 배열 기반
gcc -o test main.c collection_array.c

# 리스트 기반
gcc -o test main.c collection_list.c

# 해시 테이블 기반
gcc -o test main.c collection_hash.c
```

---

## ✅ 장점 (데이터 추상화 효과)

| 항목 | 효과 |
|------|------|
| 구현 독립성 | 사용자 코드 변경 없이 내부 자료구조 변경 가능 |
| 유지보수 용이 | 구조체 바꿔도 인터페이스 유지 |
| 응집도 ↑ | 구현은 .c에, 선언은 .h에 분리 |
| 결합도 ↓ | 내부 구조 전혀 노출 없음 (불투명 포인터 사용) |
