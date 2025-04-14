# C 프로그래밍 학습: 산술형식

## 정수 산술 형식


### 정수

정수형식 : 유한 범위의 정수를 표현
- 부호있는 정수 형식 : 양의 정수, 0, 음의정수
- 부호없는 정수 형식 : 양의 정수, 0

정수범위 : 구현체에 따라 달라짐

정수 개체의 값 : 개체에 할당된 스토리지의 비트에 특정 인코딩으로 표현




### 패딩과 정밀도

패딩(Padding)
- 하드웨어 최적화
- cpu에서 데이터를 16비트 단위로 처리한다면 13비트 정수 처리시 3비트는 비워두고 건너는게 빠름(하드웨어 쿼크)
- 패딩 비트 : 값을 표현하지 않는 여분의 비트
- char, signed char, unsigned char를 제외한 모든 정수 형식에 패딩비트가 포함될 수 있음

너비(Width) : N
- 형식의 값을 표현하기 위해 사용되는 비트 수, 패딩을 제외, 부호 포함
- ``` singed int ``` 16비트로 저장시
  - 1비트는 부호 비트
  - 3비트는 패딩 비트
  - 12비트는 진짜 값
  - 너비 = 1(부호) + 12(값) = 13비트

정밀도(Precision)
- 부호와 패딩 비트 모두를 제외한 값을 표현하기 위해 사용되는 비트 수
- 위의 예시에서 정밀도 = 12비트



### 정수 선언
```c
unsigned int ui;   // unsigned 필요
unsigned u;        // int 생략 가능
unsigned long long ull2;  // int 생략 가능
unsigned char uc; // unsigned 필요
```
- 부호 있는 정수 형식 선언시 signed 키워드 생략 가능
- 일반 char와 signed char를 구별하기 위해 signed char는 예외
- long long int 등  int 생략 가능

```c
int i;
long long int sll;
long long sll2;
signed char sc;
```



### 부호 없는 정수
`unsigned int`, `unsigned short`, `unsigned char` 등은 **음수를 표현하지 않는 정수형 타입**

- 오직 **0 이상의 값만 표현**
- 예:
  - `unsigned char` (8비트): 0 ~ 255
  - `unsigned int` (32비트): 0 ~ 4,294,967,295

- 부호가 없기 때문에, 모든 비트를 **값을 표현하는 데** 사용
- `signed`와 `unsigned`끼리 연산하면 **예상치 못한 결과**
  예: `if (-1 < 1U)`는 false (왜냐면 -1이 unsigned로 변환되면 엄청 큰 수가 됨)


| 타입                      | 최소 크기 (바이트) | 비트 수 (최소) | 최대값 (`<limits.h>`)        | 표현식                                 |
|---------------------------|--------------------|----------------|-------------------------------|-----------------------------------------|
| `unsigned char`           | 1                  | 8              | `UCHAR_MAX` = 255             | 2⁸ − 1                                  |
| `unsigned short`          | 2                  | 16             | `USHRT_MAX` = 65,535          | 2¹⁶ − 1                                 |
| `unsigned int`            | 4                  | 16 (최소) <br>32 (보통) | `UINT_MAX` = 4,294,967,295    | 2³² − 1 (x86 일반 환경)                 |
| `unsigned long`           | 4 (x86) <br> 8 (x64) | 32 또는 64     | `ULONG_MAX` = 4,294,967,295 (x86) <br> 18,446,744,073,709,551,615 (x64) | 2³² − 1 또는 2⁶⁴ − 1                    |
| `unsigned long long`      | 8                  | 64             | `ULLONG_MAX` = 18,446,744,073,709,551,615 | 2⁶⁴ − 1                        |



### 랩어라운드(wraparound)
- 부호 없는 정수 형식에서 표현하기에 너무 작거나(0보다 작은) 너무 큰(2^n-1) 값이 산술 연산의 결과 나올 때 발생
- 부호 없는 정수는 이진수로 저장되며, 비트 수는 고정입니다.
- unsigned char에서 255 + 1 → 256인데, 8비트로는 표현 불가 → 하위 8비트만 남기면 00000000 → 0 (랩어라운드)
- 정의된 동작임, 하지만 부호있는 정수에선는 정의되지 않는 동작임
- 순환 버퍼 인덱스 관리, 타이머 오버플로우 감지, 시퀸스 번호 비교에 사용됨
```c
#include <limits.h>
unsigned int ui = UINT_MAX;
ui++;
printf("ui = %d\n", ui);  // ui = 0
ui--;
printf("ui = %d\n", ui);  // ui = 4,294,967,295
```

```c
for(unsigned int i = n; i >= 0; --i)  // 랩어라운드로 정수 표현은 절때 0보다 작을 수 없다, 루프에서 벗어나지 못함
```

```c
extern unsigned int ui, sum;
if(sum + ui > UINT_MAX) // 오버 플로우를 체크하려다가 오버플로우한 값을 비교하고 있음 절대 too_big()이 동작하지 않음
  too_big();
else
  sum = sum + ui;
```
```c
extern unsigned int ui, sum;
if(ui > UINT_MAX - sum)   // 오버플로우 발생 전 비교(정상)
  too_big();
else
  sum = sum + ui;
```

```c
// GCC, Clang에서 지원하는 오버플로우 감지 내장 함수
// bool _builtin_add_overflow(type a, type b, type *result);
// bool _builtin_sub_overflow(type a, type b, type *result);
// bool _builtin_mul_overflow(type a, type b, type *result);
// a,b : 더할 두 정수
// result : 결과를 저장할 변수의 포인터
// 반환값 : true 오버플로우, false 정상

#include <stdio.h>
#include <stdbool.h>

int main() {
    unsigned int a = 4000000000;
    unsigned int b = 500000000;

    unsigned int result;
    if (__builtin_add_overflow(a, b, &result)) {
        printf("오버플로우 발생!\n");
    } else {
        printf("덧셈 결과: %u\n", result);
    }

    return 0;
}
```
```c
extern unsigned int i, j;
if(i - j < 0)   // 오버플로우 이후에 오버플로우 검사
  negative();
else
  i = i - j;
```
```c
extern unsigned int i, j;
if(i > j)   // 먼저 오버플로우 검사(정상)
  negative();
else
  i = i - j;
```



### 부호 있는 정수
#### 표현
- 부호와 크기(sign-magnitude)
  - MSB를 부호 비트로 사용 (0: 양수, 1: 음수)
  - ```0000 0101``` = 5, ```1000 0101``` = -5
  - 연산이 복잡함
  - +0, -0 존재
- 1의 보수(ones' complement)
  - 음수를 표현할 때 비트를 반전해서 사용
  - 양수는 그대로
  - 음수는 각 비트를 반전(not)해서 표현
  - ```0000 0101``` = 5, ```1111 1010``` = -5
  - +0, -0 존재
  - 덧셈시 캐리 복원이 필요함
- 2의 보수(two's complement)
  - 양수는 그대로 저장
  - 음수는 1의 보수 +1해서 표현
  - ```0000 0101``` = 5, ```1111 1011``` = -5
  - 0은 유일 ```0000 0000```
  - 덧셈/뺼셈이 동일 회로로 가능


#### 표현 가능한 값의 개수
- **기준 환경**: 일반적인 x86/x86_64 환경 (GCC, Clang, LP64 모델)
- **표현 방식**: `2의 보수` 방식 (현대 컴퓨터에서 표준)
- `n`비트일 때 표현 범위는:
  - 총 개수 = 2^n
  - 양수 개수 = `2ⁿ⁻¹ - 1`
  - 0
  - 음수 개수 = `2ⁿ⁻¹`


#### 부호 있는 정수형 범위 표 (`<limits.h>` 기준)

| 타입                   | 바이트 수 | 비트 수 | 최소값 (`*_MIN`)       | 최대값 (`*_MAX`)       | 표현 범위                      |
|------------------------|------------|----------|--------------------------|--------------------------|--------------------------------|
| `signed char`          | 1          | 8        | `-128`                  | `127`                   | `-2⁷` ~ `2⁷ - 1`             |
| `short` / `signed short` | 2          | 16       | `-32,768`               | `32,767`                | `-2¹⁵` ~ `2¹⁵ - 1`           |
| `int` / `signed int`   | 4          | 32       | `-2,147,483,648`        | `2,147,483,647`         | `-2³¹` ~ `2³¹ - 1`           |
| `long` / `signed long` | 4 (x86)    | 32       | `-2,147,483,648`        | `2,147,483,647`         | `-2³¹` ~ `2³¹ - 1`           |
|                        | 8 (x64)    | 64       | `-9,223,372,036,854,775,808` | `9,223,372,036,854,775,807` | `-2⁶³` ~ `2⁶³ - 1`   |
| `long long` / `signed long long` | 8 | 64 | `-9,223,372,036,854,775,808` | `9,223,372,036,854,775,807` | `-2⁶³` ~ `2⁶³ - 1`   |

- 시각적 예 (8비트 signed)

```
[ 음수영역 ]
10000000 (-128)  ~  11111111 (-1)

[양수 영역]
00000000 (0)      ~  01111111 (127)
```



### 오버플로우(overflow)
- 부호가 있는 정수 연산 결과가 결과 형식으로 표현할 수 없을 때 발생
- 정의 되지 않은 동작

```c
#define Abs(i) ((i) < 0 ? -(i): i)
signed int si = -25;
signed int abs_si = Abs(si)
printf("%d\n",abs_si);

signed int sim = INT_MIN;
signed int abs_sim = Abs(sim) // 음수 쪽이 양수보다 1크기 때문 즉 -INT_MIN은 표현 불가 -> 오버플로우 발생(정의되지 않은 동작)
printf("%d\n",abs_sim);
```
- 재네릭 형식 : 함수와 유사한 매크로, 모든 형식의 인수를 입력 받을 수 있다.
- 래핑 : 값이 최대치를 넘으면 다시 최솟값부터 순환
- 트랩 : 실행 중 예외를 발생시켜 프로그램을 중단
- 정의되지 않은 동작 발생시 래핑 또는 트랩을 컴파일러가 발생시킴

```c
#define AbsM(i, flag) ((i) >= 0 ? (i) : ((i) == (flag) ? (flag) : -(i)))  // 형식 종속 플래그
signed int si = -25;
signed int abs_si = AbsM(si, INT_MIN);

if(abs_si == INT_MIN)
  goto recover;
else
  printf("%d\n", abs_si);
```


### 정수 상수
- 정수 상수(integer constant), 정수 리터럴(integer literal)은 특정 정수값을 적용하기 위해 사용하는 상수
- 10진수 : 0이 아닌 숫자로 시작
- 8진수 : 0으로 시작 후 0부터 7사이의 숫자가 뒤에 오는 경우
- 16진수 : 0x, 0X로 시작후 10진수와 a~f 문자로 된 경우
- 상수에 접미사를 부텨 상수의 형식을 지정할 수 있음(U, L, LL)
- 접미사를 사용하지 않을 경우 정수 상수가 필요한 타입과 일치 하지 않는다면 암시적으로 변환됨
```c
unsigned int ui = 71U;
signed long int sli  = 1230498092349L;
unsigned long long int ui = 019834109238401ULL;
```


## 부동 소수점

- floating_point, 실수를 표현, 과학적 표기법을 사용, 숫자를 밑수와 지수로 인코딩
- c 표준에서 구현체가 특정 모델을 사용해야한다고 명시하진 않지만 구현체가 지원해야 하는 모델을 명시함

### 부동 소수점 형식
- float
  - 단정밀도(single-precision) 계산 사용
  - IEEE 754 : float(32bit)
    - 부호 : 1bit -> 양수(0), 음수(1)
    - 지수 : 8bit -> bias 적용된 지수
    - 가수 : 23bit -> 소수점 이하 (normalized시 암시적 1 생략됨)
  - 양의 최대값 ```3.4 × 10³⁸```
  - 양의 최소 정규값 ```1.18 × 10⁻³⁸```
  - 정밀도 7자리 십진수 정확도
  - 과학적 실수 표기법
    - 123.45 = 1.2345 × 10^2
    - 0.00032 = 3.2 × 10^-4
  - 지수 표기법
    - Bias(편향) : 음수와 양수 지수를 부호 없는 양의 정수(unsigned int) 하나로 표현하기 위한 인코딩 기법, 지수부를 표현할때 부호비트가 있는 2의보수를 선택하면 하드웨어 연산이 복잡하고 느려지기 때문에
      - bias : 2^(n-1) - 1, float의 경우 bias = 127
      - E : 메모리에 저장된 지수 비트 값 (0 ~ 255, 8비트)
      - e : 실제 지수 값, 즉 2^e에서의 e
      - E = e + bias;
      - e = E - bias;
      - 예제
        - 지수 : -3 -> -3 + 127 = 124 -> 지수부 저장 = 01111100
        - 지수 :  0 ->  0 + 127 = 127 -> 지수부 저장 = 01111111
        - 지수 : 127->127 + 127 = 254 -> 지수부 저장 = 11111110
    지수 비트 
      - E == 0 : 비정규화 수( subnormal 또는 +-0), 정규화가 불가능한 아주 작은 값, 가수 앞에 암시적 1.이 붙지 않음, 실제 지수 e = -126
        - M == 0000..000 : 0.0 또는 -0.0
        - M != 0 : 아주 작은 비정규 수
      - E == 1 ~ 254 : 정규화 수 (normalized), 가수 앞에 암시적 1이 붙음
      - E == 255 : 특수값(무한 또는 NaN), 실수라고 간주하지 않음
        - M == 0 : +-무한대
        - M != 0 : NaN(Not a Number), 0.0/0.0, sqrt(-1)
  - 숫자: -6.26(float)
    - 부호(Sign) = 1 (음수니까)
    - 이진수로 변환 : 6.25 = 110.01 (2진수)
    - 과학적 표기로 바꾸기 : 1.1001 × 2^2
      - 1.은 float에서 저장하지 않는다. 암시적으로 항상 있다고 가정
      - 부호: 1
      - 지수: 2 (이걸 +127 해서 저장 → 129 → 10000001)
      - 가수: 10010000000000000000000 (23비트에 맞춰서)
      - 1(부호 1비트) 10000001(지수 8비트) 10010000000000000000000(가수 23비트) 

- double
  - 배정밀도(double-precision), 1개 부호비트, 11개의 지수 비트, 52개의 유효비트
  - 양의 최대값 1.8 × 10³⁰⁸

- long double
  - 확장정밀도
  - 양의 최대값 대략 1e+4932이상

### 부동 소수점 산술
- floating point arithmetic
- 숫자의 크기가 유계(bounded), 유한 정밀도(finite precision)
  - 표현 가능한 숫자의 범위는 유한, 표현가능한 정밀도 또한 유한함
- 덧셈과 곱셈 연산은 결합성이 성립되지 않으며, 분배법칙도 적용되지 않음
  - ```(a + b) + c``` =! ```a + (b + c)```
  - ```a*(b + c)``` =! ```a*b + a*c```
  - 연산 시 오차 누적이 다르게 일어남
  - 반올림이 연산 순서에 따라 달라짐
- 일반적인 십진수 상수는 이진 부동 소수점 숫자로 정확하게 표현할 수 없다. CERT C 규칙
  - 0.1, 0.2, 1.3 등 2진수로 무한 소수가 되어 정확히 표현 안됨
  - 컴파일 타임에 소수 리터럴은 내부적으로 근사치로 변환

#### ⚠️ 4. **CERT C 규칙 관련 사항**

| ID | 규칙 / 권고 | 요약 설명 |
|----|-------------|------------|
| **FLP30-C** | 부동소수점 비교 시 오차 감안 | `if (x == y)` 대신 오차 범위 고려 |
| **FLP32-C** | 정수와 부동소수점 간의 변환에 주의 | 정밀도 손실, 오버플로우 주의 |
| **FLP34-C** | 표현 가능한 값 범위 내에서만 연산 수행 | underflow/overflow 방지 |p
| **FLP37-C** | 부동소수점 연산 순서에 따라 값이 달라질 수 있음 | 연산 순서를 명확히 하라 |
| **FLP13-C** | NaN이나 무한대에 대한 체크 필요 | 특수 값으로 인한 예외처리 필요 |

### 부동 소수점 값
- 유효 비트와 암시적 1 : 부동 소수점 값에서 가장 앞의 비트는 항상 1이므로 저장 시 생략되고 계산 시에는 암시적으로 1로 간주
- 0의 표현 : 지수와 유효 숫자가 모두 0이면 부호 비트에 따라 -0, +0 존재, 수학적의미는 같으나 연산에서 다르게 동작( 1/+0 = +무한, 1/-0 = -무한)
- 비정규화된 숫자 : 표현할수 있는 가장 작은 정규화된 값보다 작은 숫자, 맨 앞 비트가 1이 아닌 0으로 간주, 암시적 1이 없음, 작지만 정확히 0은 아님
- 비 정규 수는 정규 수보다 표현 가능한 정밀도가 낮음 : 암시적 1이 없기 때문에 정확히 표현할 수 있는 유효숫자범위가 좁음.
- 특수값 
  - Infinity (∞): 양 또는 음의 무한대 (+∞, -∞)
  - NaN (Not a Number): 실수가 아닌 값 (예: 0.0 / 0.0, sqrt(-1))
    - Quiet NaN (qNaN): 대부분 연산에서 예외 발생 없이 전파됨
    - Signaling NaN (sNaN): 연산 시 즉시 예외(floating-point exception) 
- 무한대와 NaN의 연산
    - 1 / +0 = +∞, 1 / -0 = -∞
    - 0 / 0 또는 ∞ - ∞ 등은 NaN
    - NaN은 자기 자신과도 같지 않음 → NaN != NaN → 비교는 isnan() 함수 사용 
  ```c
  // 주어진 실수의 부동소수점 종류를 문자열로 반환
  #include <math.h>
  int fpclassify(real-floating x);
  const char *show_classification(double x)
  {
    switch(fpclassify(x))
    {
        case FP_INFINTE: return "Inf"가가
        case FP_NAN:    return "NaN";
        case FP_NORMAL: return "normal";
        case FP_SUBNORMAL:  return "subnormal";
        case FP_ZERO: return "zero";
        defalut:  return "unknown";
    }
  }
  int main() {
      double a = 0.0;
      double b = 1.0 / a;  // +∞
      double c = sqrt(-1); // NaN
      double d = 1.23;
      double e = 1e-320;   // subnormal if small enough

      printf("a: %s\n", show_classification(a));
      printf("b: %s\n", show_classification(b));
      printf("c: %s\n", show_classification(c));
      printf("d: %s\n", show_classification(d));
      printf("e: %s\n", show_classification(e));

      return 0;
  }
  ```

### 부동 소수점 상수
- floating-point-constant
- 부호가 있는 실수를 표현하는 십진수나 16진수
- ex
  ```c
  15.75
  1.575E1
  1575e-2
  ```
- 형식을 갖는다. 접미사가 없으면 double, f나 F 문자가 접미사로 붙으면 float, l이나 L이 붙으면 long double 형식
  ```c
  10.0  //  double
  10.0F //  float
  10.0l //  long double
  ```

## 산술 변환
- 형 변환(cast) : 어떤 산술 형식에서 다른 산술 형식으로 변환
- 명시적 형변환
  ```c
  int si = 5;
  short ss = 8; // 1
  long sl = (long)si; // 2
  unsigned short us = (unsigned short)(ss + sl);
  ```
  - 1 : 같은 부호의 작은 정수 형식에서 더 큰 정수 형식으로 형 변환은 안전함을 보장
  - 2 : 정밀도가 낮은 부호 없는 형식으로 변환되면 변환 결과는 원래 값과 다를 수 있다.

- 암시적 형변환
  - 2 : ss + si에서 필요에 땨라 식에서 자동으로 이루어짐

### 정수 변환 순위(integer conversion rank)
- 계산을 위한 공통 형식을 결정하는데 사용되는 정수 형식에 대한 표준 순위 순서
- 서로 다른 정수형 타입 간의 연산 (`int + short`, `unsigned int + long`, 등)
- 정수 승격(integer promotion)
- 연산 결과의 타입 결정

  | 순위 | 타입                      | 설명 |
  |------|---------------------------|------|
  | 1    | `_Bool`                  | 가장 낮은 순위 |
  | 2    | `signed char` <br> `unsigned char` <br> `char` (implementation-defined) | |
  | 3    | `short` <br> `unsigned short`       | |
  | 4    | `int` <br> `unsigned int`           | 기준 타입 |
  | 5    | `long` <br> `unsigned long`         | |
  | 6    | `long long` <br> `unsigned long long` | 가장 넓은 정수 타입 |
  | —    | `enum`                             | 그 정의에 따라 순위 부여됨 |
  | —    | `bit-field`                        | bit-field는 특별 규칙 적용 |


- 핵심 규칙 1: 정수 승격 (Integer Promotion)
  - `char`, `signed char`, `unsigned char`, `short`, `unsigned short`는 연산 전에 **`int`로 승격**됩니다.
  ```c
  unsigned char a = 100;
  short b = 30000;
  int result = a + b;  // 둘 다 int로 승격되어 연산
  ```

- 핵심 규칙 2: 일반 정수 변환 (Usual Arithmetic Conversions)
  1. 먼저 작은 타입들은 `int` 또는 `unsigned int`로 **정수 승격**.
  2. 그 다음 서로 다른 타입이면 **정수 변환 순위에 따라 더 높은 쪽으로 변환**.
  3. 부호(signed/unsigned)가 다르면 다음 규칙을 적용:
  - 부호가 다를 때 규칙
    - **unsigned 타입의 순위가 signed보다 크거나 같으면** → signed → unsigned로 변환  
      (예: `unsigned int` + `int` → `unsigned int`로 연산)

    - **signed 타입이 표현할 수 있는 모든 값을 unsigned도 표현 가능하면** → 그대로 signed 유지  
      (예: `int` + `unsigned short` → 둘 다 `int`로 변환됨)

    - **그 외는 둘 다 unsigned로 변환**

  ```c
  char a = 10;
  short b = 20;
  int c = a + b; // 둘 다 int로 승격됨
  ```

  ```c
  unsigned int a = 4000000000; // 큰 양의 수
  int b = -10;
  auto result = a + b; // b는 unsigned로 변환됨 → result도 unsigned
  ```

  ```c
  long a;
  unsigned int b;
  auto result = a + b;
  // int → long 순위 비교 → long이 더 크므로,
  // 만약 long이 signed인데 b의 값이 너무 크면 둘 다 unsigned long으로 승격됨
  ```


### 일반 산술 변환 (Usual Arithmetic Conversions)
> 서로 다른 타입의 두 피연산자 간 산술 연산을 수행할 때,  
> **두 피연산자를 동일한 타입으로 변환**한 후 연산을 수행하는 규칙

적용되는 연산자 예시:
- 이항 산술 연산자: `+`, `-`, `*`, `/`, `%`
- 관계 연산자: `<`, `>`, `<=`, `>=`
- 등가 연산자: `==`, `!=`
- 조건 연산자: `a ? b : c` 에서 `b`와 `c` 타입 일치


Step 1: 정수 승격 (Integer Promotions)
- `char`, `short`, `_Bool` 등은 **먼저 `int` 또는 `unsigned int`로 승격**
```c
unsigned char a = 100;
short b = 1000;
a + b → 둘 다 int로 승격됨
```

Step 2: 공통 타입 결정 (Usual Arithmetic Conversions)

정수 승격 후에도 **타입이 다르면**, 다음 규칙을 따릅니다:
1. 두 피연산자가 같은 타입이면 → 그대로 연산
2. 다르면 **정수 변환 순위**에 따라 더 넓은 쪽으로 변환
3. **부호가 다르면** 다음 조건을 확인:

| 경우 | 처리 방식 |
|------|-----------|
| unsigned 타입이 더 높은 순위 → signed를 unsigned로 변환 |
| signed 타입이 unsigned 타입의 모든 값을 표현 가능 → unsigned를 signed로 변환 |
| 둘 다 아니면 → 둘 다 unsigned로 변환됨 |


예 1: `int + unsigned int`
- `unsigned int`가 더 넓지 않지만, `int`가 음수라면 표현 못함 → **int → unsigned int로 변환**

예 2: `long + unsigned int`
- `long`이 더 높은 순위 → long이 unsigned int의 최대값보다 작으면 long 유지
- 하지만 표현 범위가 안 맞으면 → 둘 다 `unsigned long`으로 변환


- 조건 연산자 `? :`
```c
(condition) ? expr1 : expr2
```
- 이때 `expr1`, `expr2`가 서로 다른 타입이면 → **공통 타입으로 변환 후** 결과값 계산
- 동일한 규칙이 적용됨 (정수 승격 → 산술 변환)
예:
```c
int a = 5;
unsigned int b = 10;

auto result = (a > 0) ? a : b; // → a도 unsigned int로 변환됨
```

### 안전한 변환
- 정수변환
  - 같은 부호의 더 큰 형식으로 변환하는 것은 항상 안전, 확인할 필요 없다.
  ```c
  #include <errono.h>
  #include <limits.h>
  errno_t do_stuff(signed long value)
  {
    if((value < (SCHAR_MIN) || (value > SCHAR_MAX))
    {
      return ERANGE;
    } // 인수의 정수 형식에 저장된 값이 결과 정수 형식으로 표현할수 있는 값의 범위 안에 있는지 확인

    signed char sc = (singed char) value; 

  }
  ```
- 정수를 부동 소수점으로 변환
  - 표현 가능 범위와 정밀도에 주의
  - 범위 확인 후 float 변환
  - 큰 정수는 float말고 double로 변환

  ```c
  #include <stdio.h>
  #include <limits.h>
  #include <float.h>

  int main() {
      int value = 123456789;

      if (value >= -16777216 && value <= 16777216) {
          float f = (float)value;
          printf("정확하게 변환됨: %.0f\n", f);
      } else {
          printf("경고: float로 변환 시 정밀도 손실 위험 있음!\n");

          double d = (double)value; // double은 훨씬 안전
          printf("double로는 안전하게 변환됨: %.0f\n", d);
      }

      return 0;
  }
  ```

- 부동 소수점을 정수로 변환
  - 소수점 이하는 버림
  - 표현 가능 범위가 넘으면 정의되지 않은 동작 (오버플로우)
  - NaN, Inf를 변환하면 정의되지 않은 동작
  - 특수값 검사, 표현가능범위 초과 여부 확인
  ```c
  #include <stdio.h>
  #include <math.h>
  #include <limits.h>
  #include <float.h>

  int main() {
      float f = 123456.78f;

      if (isnan(f)) {
          printf("변환 불가: NaN\n");
      } else if (isinf(f)) {
          printf("변환 불가: Infinity\n");
      } else if (f > INT_MAX || f < INT_MIN) {
          printf("변환 불가: int 범위 초과\n");
      } else {
          int i = (int)f;
          printf("정수 변환 성공: %d\n", i);
      }

      return 0;
  }
  ```