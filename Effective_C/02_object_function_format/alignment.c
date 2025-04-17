#include <stdio.h>
struct S{
  int i;
  double d;
  char c;
};

#pragma pack(push,1) 
struct T{ // 1바이트 단위로 정렬 (패딩 없음)
  int i;
  double d;
  char c;
};
#pragma pack(pop)



int main(void)
{
  unsigned char bad_buff[sizeof(struct S)];         // 정렬 보장 x, 정의되지 않은 동작
  _Alignas(struct S) unsigned char good_buff[sizeof(struct S)]; // 정렬 보장, C11 표준

  struct S *bad_ptr = (struct S *)bad_buff;
  struct S *good_ptr = (struct S *)good_buff;

  printf("bad_ptr: %p\n", bad_ptr); // 정렬 보장 x, 정의되지 않은 동간간
  printf("good_ptr: %p\n", good_ptr); // double 타입 시작 주소가 8바이트 경계에 정렬됨
  printf("sizeof(struct S): %zu\n", sizeof(struct S)); // 24
  printf("sizeof(struct T): %zu\n", sizeof(struct T)); // 16

  return 0;
}

/*

==============================================
맞춤
==============================================

맞춤(alignment) : 데이터 타입이 멤리에 저장될때 요구되는 주소 정렬 기준
맞춤 요구 사항(alignment requirement) : 특정 데이터 형식이 메모리에 저장될 때 해당 형식의 시작 주소가 반드시 특정 기준에 맞아야 하는 것

C11 표준 : _Alignas 키워드 사용, 동적 할당시 aligned_alloc 함수 사용
  _Alignas(struct S) unsigned char good_buff[sizeof(struct S)];
  strcut S *ptr = aligned_alloc(alignof(struct S), sizeof(struct S));

GCC 확장 : __attribute__((aligned(n))) 사용
  unsigned char buf[sizeof(struct S)] _attribute__((aligned(8)));

---

## ✅ `__attribute__((aligned))` — 사용하는 대표적인 상황

### 🔸 1. **SIMD 명령어 / 벡터 연산 최적화**

```c
struct __attribute__((aligned(16))) Vec4 {
    float x, y, z, w;
};
```

- AVX, SSE 명령어는 **16바이트 정렬 필수**
- 정렬이 안 맞으면 → **SIGBUS** 또는 **성능 폭망**
- GPU, 영상처리, 물리엔진 등에서 많이 사용

---

### 🔸 2. **DMA, MMIO 버퍼 주소 정렬**

> 디바이스 드라이버에서 DMA 전송 시  
> 버퍼 주소가 32/64/128바이트 정렬돼야 하는 경우

```c
uint8_t __attribute__((aligned(64))) dma_buffer[4096];
```

- 장치가 비정렬 주소를 못 읽는 경우
- 특히 **ARM, FPGA, GPU, NIC 카드**에서 필수

---

### 🔸 3. **캐시 라인 정렬**

```c
#define CACHE_LINE 64

struct __attribute__((aligned(CACHE_LINE))) TaskQueue {
    char data[64];
};
```

- 캐시 충돌 피하기 위해 **캐시 라인 크기 단위로 정렬**
- 락 없는 큐나 멀티스레드 성능 튜닝에서 중요

---







==============================================
구조체 패딩
==============================================

구조체 패딩(padding) : 구조체 멤버들을 정렬기준에 맞추기 위해 삽입되는 빈 바이트 공간

#pragma pack(push,n) : 패딩 크기 지정
#pragma pack(pop) : 패딩 크기 복귀

GCC 확장 : __attribute__((packed)) 사용
  struct _attribute__((packed)) S
  {
    int i;
    double d;
    char c;
  };


## ✅ `__attribute__((packed))` — 사용하는 대표적인 상황

### 🔸 1. **바이너리 통신 프로토콜 구조체 정의**

> 예: 센서, IoT, 디바이스 드라이버, 네트워크 패킷

```c
struct __attribute__((packed)) SensorPacket {
    uint8_t header;
    uint16_t temperature;
    uint8_t checksum;
};
```

- 이 구조체가 그대로 시리얼, TCP 등으로 전송됨
- **바이트 단위 포맷이 외부와 딱 맞아야 함**
- 패딩 들어가면 **통신 해석 오류 발생** → 절대 안 됨

### ✅ 예시: 시리얼로 받은 데이터 그대로 `struct`에 `memcpy()`  
→ 패딩이 있으면 해석 뻑남  
→ `packed`로 **패딩 제거 필수**

---

### 🔸 2. **파일 포맷 구조 정의 (BMP, WAV 등)**

```c
struct __attribute__((packed)) BMPHeader {
    char signature[2];
    uint32_t file_size;
    uint32_t reserved;
    uint32_t data_offset;
};
```

- 바이너리 파일을 메모리에 `fread()`로 읽어올 때 **정확한 포맷 일치** 필요
- `packed` 없으면 `sizeof(struct BMPHeader)`가 달라지고 → 파싱 오류


d

*/