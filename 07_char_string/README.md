# 문자와 문자열

## 문자
> 문자를 처리하기 위해 특정 문자에 고유한 정수 값을 할당 `문자 인코딩` 사용

> 문자 인코딩 : 유니코드, ASCII, 확장 ASCII 등등

  ### ASCII (American Standard Code for Information Interchange)

  - 컴퓨터가 문자를 숫자로 저장하기 위해 만든 **표준 문자 인코딩**
  - 총 **128개(0~127)**의 문자 코드

    | 범위 | 의미                           | 예시 |
    |------|--------------------------------|------|
    | 0~31 | **제어 문자(Control codes)**   | `\n`, `\t`, `\b` 등 |
    | 32   | **공백(space)**               | `' '` |
    | 33~47 | 특수 문자                     | `'!'`, `'@'`, `'#'` |
    | 48~57 | **숫자**                     | `'0'`~`'9'` |
    | 65~90 | **대문자**                   | `'A'`~`'Z'` |
    | 97~122 | **소문자**                  | `'a'`~`'z'` |
    | 127  | DEL (삭제) 제어 문자          | - |


### 확장 ASCII (Extended ASCII)

  - 기본 ASCII는 7비트(0~127)만 표현 가능 → **1바이트(8비트) 전체 256개(0~255)** 표현하려고 확장한 것
  - **128~255**: 라틴 알파벳 변형, 그래픽 기호, 유럽 언어 문자, 기타 특수문자
  - 표준은 없고, 여러 **코드 페이지(Code page)** 또는 **문자 인코딩**이 있음

  ### 유니코드(UNICODE)

  유니코드는 전 세계의 모든 문자를 고유한 정수 값으로 표현하는 표준이다. 각 문자는 코드 포인트(Code Point)라고 불리는 숫자를 갖는다. 예를 들어:

  - 'A' → U+0041  
  - '가' → U+AC00  
  - '한' → U+D55C  
  - '中' → U+4E2D

  이 코드 포인트는 그 자체로는 저장이 안 되기 때문에, 파일이나 메모리에 저장하려면 인코딩 방식이 필요하다. 유니코드는 UTF-8, UTF-16, UTF-32 등의 인코딩 방식으로 표현된다.

  UTF-8은 유니코드를 바이트로 변환하는 가장 널리 쓰이는 방식이다. 가변 길이 인코딩으로, 문자마다 1~4바이트를 사용한다.

  - 1바이트: U+0000 ~ U+007F (ASCII)
  - 2바이트: U+0080 ~ U+07FF
  - 3바이트: U+0800 ~ U+FFFF (한글 포함)
  - 4바이트: U+10000 이상 (일부 문자, 특수 문자)


  한글 '한'(U+D55C)을 UTF-8로 저장하면 다음과 같은 3바이트로 인코딩된다:

  - UTF-8: `0xED 0x95 0x9C`

  아래는 C 코드로 이를 확인하는 예제다.

  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
      char *str = "한";
      printf("strlen: %lu\n", strlen(str));

      for (int i = 0; i < strlen(str); ++i) {
          printf("byte %d: 0x%X\n", i, (unsigned char)str[i]);
      }
      return 0;
  }
  ```

  출력:
  ```
  strlen: 3
  byte 0: 0xED
  byte 1: 0x95
  byte 2: 0x9C
  ```

  문자열 길이는 바이트 수 기준이며, 한글은 3바이트를 차지한다.


  UTF-8로 인코딩된 3바이트를 다시 유니코드 코드 포인트(U+D55C)로 복원하려면 다음과 같이 처리할 수 있다.

  ```c
  #include <stdio.h>

  int main() {
      unsigned char str[] = "한";
      int codepoint = 0;

      codepoint |= (str[0] & 0x0F) << 12;
      codepoint |= (str[1] & 0x3F) << 6;
      codepoint |= (str[2] & 0x3F);

      printf("유니코드 코드 포인트: U+%04X\n", codepoint);
      return 0;
  }
  ```

  출력:
  ```
  유니코드 코드 포인트: U+D55C
  ```

## 데이터 형식
> unadorned char : 표현범위 8비트인 문자를 표현하는 형식 -> `char`

> wide character : 표현범위 8이상인 문자를 표현하는 형식 -> `wchar_t`

  ### char
  - 구현체에 따라 부호가 없는 형식과 부호가 있는 형식으로 나뉜다.
  - char는 정수 형식이지만 문자 데이터에 char형식을 사용하고 정수 데이터에는 char형식을 사용하지 않는다
  - US_ASCII와 같은 7비트 문자 인코딩을 표현하는데 안전하게 사용가능 -> 최상위 비트가 항상 0이므로 부호 확장에 대해 오류가 없다.
  - 8비트 문자 인코딩인 확장 ASCII, UTF-8 등 표현하는데 사용가능하지만 char를 부호가 있는 8비트 형식으로 정의하는 구현에서 문제가 될 수 있다.

  - `isdigit()`의 함수 정의는 다음과 같다.

    ```c
    int isdigit(int c);
    ```

    표준에서는 `isdigit()`에 전달되는 인자 `c`는 반드시 **`unsigned char`로 변환 가능한 값이거나 EOF**여야 한다. 하지만 일반적인 `char`는 **부호 있는 1바이트 정수**다.
    - 왜 int를 인자로 받는가?
      char는 1바이트지만, 함수 호출 시 자동으로 정수 승격(integer promotion) 이 일어나기 때문에 인자는 int형으로 받아야 한다.
      그러나 char는 보통 signed 이고, 이 경우 값이 128 이상일 때 음수로 해석된다.

    - 잘못된 예
    ```c
    #include <stdio.h>
    #include <ctype.h>

    int main() {
        char c = 0xE9; // 233, 확장 ASCII 문자, signed char이면 -23
        if (isdigit(c))
            printf("Digit\n");
        else
            printf("Not Digit\n");
        return 0;
    }
    ```
    0xE9는 원래 확장 ASCII의 'é'지만, `isdigit()`은 내부적으로 배열 인덱스를 사용하거나, 범위 체크를 하는데, 음수가 들어오면 오류가 발생할 수 있다.
    이는 정의되지 않은 동작이다.


    - 해결 방법

    ```c
    #include <stdio.h>
    #include <ctype.h>

    int main() {
        char c = 0xE9;
        if (isdigit((unsigned char)c))
            printf("Digit\n");
        else
            printf("Not Digit\n");
        return 0;
    }
    ```

    항상 `isdigit()`에는 **(unsigned char)로 캐스팅한 값**을 넘겨야 안전하다.
  ---
  ### int

  - `fgetc`, `getc`, `getchar`, `ungetc`는 C에서 문자 단위로 입력을 처리하는 함수들이다. 
  - 모두 `<stdio.h>`에 정의되어 있고, 기본적으로 **`int`를 반환하며, EOF(-1)** 를 반환할 수 있다는 공통점이 있다.

  fgetc(FILE *stream)

  ```c
  int c = fgetc(stdin);
  ```

  - 지정한 스트림에서 **1바이트 문자**를 읽는다.
  - 반환값은 `unsigned char`로 읽힌 후 **`int`로 승격**된다.
  - 실패하거나 EOF에 도달하면 `EOF` 반환.
  - 내부적으로 버퍼를 사용한다.


  getc(FILE *stream)

  ```c
  int c = getc(stdin);
  ```

  - `fgetc`와 기능 동일. **매크로**로 정의된 경우가 많아서 약간 더 빠를 수 있음.
  - 매크로로 정의될 수 있으므로 **인자에 부작용 있는 표현식 사용하면 안 됨.**

  ```c
  getc(fp++)  // 위험 (매크로일 경우 fp가 두 번 증가할 수도 있음)
  ```


  getchar(void)

  ```c
  int c = getchar();
  ```

  - `getc(stdin)`과 동일.
  - 표준 입력에서 1바이트를 읽는다.


  ungetc(int c, FILE *stream)

  ```c
  int c = fgetc(stdin);
  ungetc(c, stdin);
  ```

  - 마지막으로 읽은 문자를 스트림에 다시 되돌린다.
  - 다음 입력 시 해당 문자가 다시 반환된다.
  - 반드시 `fgetc`, `getc`, `getchar` 같은 문자 입력 함수로 읽은 값을 넣어야 한다.
  - 여러 번 연속으로 호출할 수 있지만, 보장되는 크기는 1바이트 이상 정도만 명시됨.
  - `c`는 반드시 **`unsigned char`로 표현 가능한 값 또는 EOF** 여야 한다.


  > 모두 `int`를 반환하는 이유는 **문자 값(0~255) 외에 EOF(-1)을 구분하기 위해서**이다.

  > 문자 데이터를 처리할 땐 항상 반환값을 `char`로 바로 저장하지 말고, `int`로 받아서 `EOF` 여부를 먼저 확인한 후 처리하는 게 안전하다.
  ---
  ### wchar_t
  `wchar_t`는 "wide character"의 줄임말로, **다국어 문자**나 **비 ASCII 문자**를 처리하기 위해 사용되는 **넓은 문자 자료형**이다. 
  C 표준에서 정의되어 있으며, `<wchar.h>` 헤더에 관련 함수와 매크로가 포함되어 있다.

  ```c
  wchar_t wc = L'한';
  ```

  - `wchar_t`는 정수형 타입이며, 보통 2바이트 또는 4바이트 (플랫폼마다 다름)
    - Windows: 2바이트 (UTF-16 코드 유닛)
    - Linux/Unix: 4바이트 (UTF-32 코드 포인트)
  - 리터럴 앞에 `L`을 붙여야 `wchar_t` 문자로 인식됨
  - 일반 문자: `'A'`, `"ABC"` → `char`
  - 넓은 문자: `L'A'`, `L"ABC"` → `wchar_t`
  - 관련 함수 (헤더: `<wchar.h>`)

    | 함수             | 설명 |
    |------------------|------|
    | `wprintf()`      | 넓은 문자 출력 |
    | `wscanf()`       | 넓은 문자 입력 |
    | `wcscpy()`       | 문자열 복사 |
    | `wcscmp()`       | 문자열 비교 |
    | `wcslen()`       | 문자열 길이 계산 |
    | `fgetwc()`       | 파일에서 `wchar_t` 문자 1개 읽기 |
    | `fputwc()`       | 파일에 `wchar_t` 문자 1개 쓰기 |

  ```c
  #include <stdio.h>
  #include <wchar.h>
  #include <locale.h>

  int main() {
      setlocale(LC_ALL, "");  // 로케일 설정 (UTF-8 지원 위해 필요)

      wchar_t str[] = L"한글";
      wprintf(L"문자열: %ls\n", str);
      wprintf(L"길이: %lu\n", wcslen(str));

      return 0;
  }
  ```

  출력:
  ```
  문자열: 한글
  길이: 2
  ```
  - 반드시 `setlocale()`을 설정해야 터미널에서 유니코드 출력이 정상 작동한다.
  - `wchar_t`는 유니코드 전체 문자를 항상 1개로 표현할 수 있는 건 아니다. (특히 UTF-16 기반 시스템에서는 surrogate pair가 필요)
  - `wchar_t`는 플랫폼 간 호환성이 떨어지기 때문에, 현대 시스템에서는 `char` + `UTF-8`로 처리하거나, `char32_t`, `char16_t` 같은 C11의 `charN_t` 계열을 사용하는 경우도 많다.

  ---
  ### char16_t char32_t
  > `char16_t`, `char32_t`는 **C11 표준**에서 도입된 **고정 크기 유니코드 문자형**이다. 목적은 유니코드 문자를 더 명확하고 일관되게 다루는 것이다. 이들은 `<uchar.h>` 헤더에 정의되어 있다.

  char16_t
  - 크기: 2바이트 (16비트)
  - 문자 집합: UTF-16 코드 유닛
  - 한 문자를 2바이트로 표현 (BMP 문자만 1개, 보충 문자(SMP)는 surrogate pair 2개로 표현)
  - 보통 Windows의 내부 유니코드 표현과 동일 (UTF-16 기반)

  char32_t
  - 크기: 4바이트 (32비트)
  - 문자 집합: UTF-32 코드 포인트
  - 유니코드 한 문자를 항상 1개로 표현 가능
  - 리눅스에서 `wchar_t`가 4바이트일 경우와 동일한 표현

  리터럴 사용법
  - `u'A'` → `char16_t` 문자
  - `U'A'` → `char32_t` 문자
  - `u"한글"` → `const char16_t[]`
  - `U"한글"` → `const char32_t[]`


  ```c
  #include <stdio.h>
  #include <uchar.h>

  int main() {
      char16_t c16 = u'한';
      char32_t c32 = U'한';

      printf("char16_t 크기: %zu바이트\n", sizeof(c16));
      printf("char32_t 크기: %zu바이트\n", sizeof(c32));

      printf("char16_t 코드 유닛: 0x%X\n", c16);
      printf("char32_t 코드 포인트: 0x%X\n", c32);

      return 0;
  }
  ```

  출력 (UTF-16이 단일 유닛으로 표현 가능한 범위일 경우):

  ```
  char16_t 크기: 2바이트
  char32_t 크기: 4바이트
  char16_t 코드 유닛: AC00
  char32_t 코드 포인트: AC00
  ```
  표준 라이브러리에서 관련 함수가 제한적이므로, 문자열 처리는 직접 구현하거나 외부 라이브러리(예: ICU, utf8cpp 등) 사용하는 경우가 많다.

## 문자 상수
  **문자 상수**는 **하나의 문자 값을 가지는 상수 리터럴**로, `int` 타입이다. 작은따옴표 `' '`로 표현하며, 컴파일 시 **정수 값(ASCII 또는 유니코드 코드 포인트)**로 변환된다.

  ### 기본 형태

  ```c
  'A'      // ASCII 코드 65
  '0'      // ASCII 코드 48
  '\n'     // 아스키 10 (줄바꿈 문자)
  '\x41'   // 16진수로 표현된 'A'
  '\101'   // 8진수로 표현된 'A'
  ```

  모두 `int` 타입이며, 1바이트 `char`가 아님.

  ```c
  printf("%d\n", 'A');  // 65 출력
  ```

  ---

  ### 다국어 문자

  ```c
  L'가'      // wchar_t 타입 (UTF-16 또는 UTF-32)
  u'가'      // char16_t 타입 (UTF-16 코드 유닛)
  U'가'      // char32_t 타입 (UTF-32 코드 포인트)
  ```

  각 접두어에 따라 타입이 다르고, 저장 크기도 다르다.

  ---

  ### 문자 상수 vs 문자열 상수

  | 표현     | 의미                 | 타입                |
  |----------|----------------------|---------------------|
  | `'A'`    | 문자 상수 (하나의 문자)  | `int`               |
  | `"A"`    | 문자열 상수 (문자 배열) | `const char[2]`     |
  | `'가'`   | (문법 오류, 다문자 상수) | → 오류 또는 경고    |

  ---

  ### 다문자 상수 (multi-character constant)

  ```c
  'ab'      // 허용은 되지만 명확한 의미 없음. 구현 정의(컴파일러마다 다름).
  ```

  - 예: `'ab'` → GCC에서는 `('a' << 8) | 'b'`로 처리되어 정수 값 0x6162로 해석될 수 있음.
  - 사용하지 말 것.

## 이스케이프 시퀀스
  **이스케이프 시퀀스(escape sequence)**는 출력 불가능하거나 특수한 의미를 가지는 문자를 표현하기 위한 문자 조합이다. 백슬래시(`\`)로 시작하며, 컴파일러가 하나의 문자로 해석한다.

  ### 제어 문자 (표준 ASCII 제어 기능)

  | 이스케이프 | 의미           | ASCII 코드 |
  |------------|----------------|------------|
  | `\n`       | 줄바꿈         | 10         |
  | `\t`       | 수평 탭        | 9          |
  | `\b`       | 백스페이스     | 8          |
  | `\r`       | 캐리지 리턴    | 13         |
  | `\a`       | 경고음 (bell)  | 7          |
  | `\f`       | 폼 피드        | 12         |
  | `\v`       | 수직 탭        | 11         |
  | `\\`       | 백슬래시 자체  | 92         |
  | `\'`       | 작은따옴표     | 39         |
  | `\"`       | 큰따옴표       | 34         |
  | `\?`       | 물음표         | 63 (삼중 물음표 회피용) |


  ### 숫자 기반 이스케이프

  - `\ooo` : 8진수 문자 (최대 3자리)
  - `\xhh` : 16진수 문자 (자리 수 제한 없음, 공백 또는 비영숫자에서 종료)

  ```c
  '\101'    // 8진수 101 → 65 → 'A'
  '\x41'    // 16진수 41 → 65 → 'A'
  ```

  주의: `'\x41Z'`는 `0x41Z`가 아니라 `'A'` + `'Z'`로 이어짐. 첫 번째 숫자만 16진수로 해석된다.


  ### 예제

  ```c
  #include <stdio.h>

  int main() {
      printf("Hello\nWorld\t!\n");
      printf("문자 A의 ASCII 코드: %d\n", '\x41');
      printf("따옴표 출력: \' \" \n");
      return 0;
  }
  ```

  출력:

  ```
  Hello
  World	!
  문자 A의 ASCII 코드: 65
  따옴표 출력: ' "
  ```


## 문자열

C에서 문자열은 **`null 문자('\0')로 끝나는 문자 배열**이다.  기본 문자열 형식은 지원하지 않는다.
리터럴로는 큰따옴표 `" "`를 사용한다. 예:

```c
char str[] = "ABC";  // 실제 저장: {'A', 'B', 'C', '\0'}
```

- `"ABC"`는 문자열 상수이고, `char` 배열로 변환될 수 있다.
- 문자열의 끝은 항상 `'\0'`이 있어야 한다.  
  → 이게 없으면 함수들이 문자열의 끝을 찾지 못해 **오류 또는 오버런** 발생.

  ---
  ### 표현 범위가 좁은 문자열

  ```c
  char str[] = "가나다";
  ```

  - `char`는 1바이트, **UTF-8** 문자 인코딩을 저장할 수 있음
  - 하지만 다국어 문자(예: 한글, 한자 등)는 2~4바이트의 **가변 길이**로 표현됨
  - `"가"`는 UTF-8로 3바이트 → `"가나다"`는 9바이트 + `'\0'` = 총 10바이트 필요

  문제점:
  - **1바이트 단위 처리**로는 문자 개수 파악 불가  
  - **한 글자를 한 번에 처리하려면 추가 인코딩 처리 필요** (`mbstowcs`, `iconv` 등)


  ---
  ### 표현 범위가 넓은 문자열

  ```c
  wchar_t wstr[] = L"가나다";
  char16_t s16[] = u"가나다";
  char32_t s32[] = U"가나다";
  ```

  - `wchar_t`, `char16_t`, `char32_t`는 각각 유니코드 표현에 더 적합
  - **고정 길이** 또는 **명확한 단위 처리**가 가능해 문자열 개수 파악이 쉬움
  - 플랫폼별 차이:
    - `wchar_t`: Windows는 2바이트, Linux는 4바이트
    - `char16_t`: 항상 2바이트 (UTF-16)
    - `char32_t`: 항상 4바이트 (UTF-32)


  | 구분           | 타입         | 저장 크기     | 유니코드 대응 | 문자 개수 계산 | 사용 용도          |
  |----------------|--------------|----------------|----------------|------------------|---------------------|
  | 표현 좁음      | `char[]`     | 1바이트/문자   | UTF-8          | 어려움 (가변 길이) | 일반 문자열, ASCII |
  | 표현 넓음      | `wchar_t[]`  | 2~4바이트/문자 | UTF-16/UTF-32  | 가능             | 다국어, 유니코드    |
  | 표현 넓음      | `char16_t[]` | 2바이트/유닛   | UTF-16         | surrogate 존재 시 복잡 | UTF-16 문자열   |
  | 표현 넓음      | `char32_t[]` | 4바이트/문자   | UTF-32         | 명확             | 유니코드 정밀 처리   |
  
  ---
  ### 문자열 리터럴 (String Literal)

  **문자열 리터럴**은 소스 코드에서 `" "`로 묶어 작성한 상수 문자열이다.  
  컴파일 시 **읽기 전용 메모리 영역에 저장**되며, 자동으로 **`'\0'`(널 문자)**가 끝에 추가된다.

  ```c
  char *s = "hello";
  ```

  이 문장은 `"hello"`라는 문자열 리터럴이 읽기 전용 공간에 저장되고, `s`는 그 주소를 가리킨다.



  특징

    1. **종단 문자 포함**

    ```c
    char *s = "ABC";  // 실제 저장: 'A', 'B', 'C', '\0'
    ```

    2. **읽기 전용**

    ```c
    char *s = "hello";
    s[0] = 'H';  // 정의되지 않은 동작 (세그멘테이션 오류 가능)
    ```

    리터럴은 보통 `.rodata` 영역에 저장되므로 수정하면 런타임 오류 발생할 수 있음.


    3. **배열로 초기화 시 복사됨**

    ```c
    char s[] = "hello";  // 리터럴 값을 배열에 복사
    s[0] = 'H';           // OK, 배열이므로 수정 가능
    ```


    4. **연결 가능 (컴파일 타임 상수 병합)**

    ```c
    char *s = "abc" "def";  // → "abcdef"
    ```


    5. **다양한 문자형과 접두어 지원**

      | 리터럴 형태 | 설명                   | 타입               |
      |-------------|------------------------|--------------------|
      | `"abc"`     | 좁은 문자열             | `const char[]`     |
      | `L"abc"`    | 넓은 문자열             | `const wchar_t[]`  |
      | `u"abc"`    | UTF-16 문자열           | `const char16_t[]` |
      | `U"abc"`    | UTF-32 문자열           | `const char32_t[]` |

    6. **배열 변수 초기화**
    ```c
    #define S_INIT "abc" //-> "abcd" 로 변경시
    const char s[4] = S_INIT; // s에는 null문자 저장 안됨
    const char s[] = S_INIT;  // s에 null문자 저장됨 
    ```
    배열 초기화를 문자열 상수로 한다면 배열의 크기를 지정하지 않는것이 유지보수에 용이하다.

  포인터와 배열 차이

  ```c
  char *p = "hi";      // 읽기 전용 문자열을 가리킴
  char a[] = "hi";     // 문자 배열에 복사됨, 수정 가능
  ```


  문자열 리터럴의 크기

  ```c
  char *s = "hello";
  sizeof("hello")       // 6 (널 문자 포함)
  strlen("hello")       // 5 (널 문자 제외)
  ```


  ### 문자열 처리 함수
  > <string.h>, <wchar.h> 표준 라이브러리 함수

  - 버퍼오버플로우와 같은 보안 취약점으로 C11에서 k 경계검사 인테페이스 도입
  - strcpy,strcat,strncpy,strncat -> strcpy_s,strcat_s,strncpy_s,strncat_s
  - strdup, strndup (POSIX)


  > 문자열 길이 계산 `size_t strlen(const char *s);`
    - `'\0'`이 나오기 전까지의 문자 개수를 반환 (널 문자는 포함하지 않음)
    - `NULL` 포인터를 넣으면 **정의되지 않은 동작**
    - `\0` 없는 버퍼 -> **무한 루프**
    - O(n) -> 종단 문자를 만날 때까지 1바이트씩 순회 

    ```c
    #include <stdio.h>
    #include <string.h>

    int main() {
      char szInput[256];
      printf("Enter a sentence: ");
      scanf("%s", szInput);
      printf("The sentence entered is %lu characters long.\n", strlen(szInput));
      return 0;
    }
    ```

  > 문자열 복사 `char *strcpy(char *dest, const char *src);`
  - `src` 문자열을 `'\0'` 포함해서 `dest`에 복사
  - `dest`의 크기가 작을 경우 **버퍼 오버플로우 위험 있음**
  - O(n)
  ```c
  char buf[100];
  strcpy(buf, "Hello");
  ```
  > n만큼 문자열 복사 `char *strncpy(char *dest, const char *src, size_t n);`
  - 최대 `n` 바이트까지 복사
  - `src`가 `n`보다 짧으면 `dest` 나머지를 `'\0'`로 채움
  - `src`가 길면 `'\0'`이 안 붙을 수도 있음
  ```c
  char buf[10];
  strncpy(buf, "ABC", 10);  // '\0' 포함됨
  ```
  > 문자열 덧붙이기 `char *strcat(char *dest, const char *src);`
  - `dest` 끝에 `src`를 붙임 (널 문자 기준)
  - `dest`의 널문자에 `src`의 첫번째 문자를 덮어 씌운다
  - `dest`는 충분한 크기를 가져야 함, 작으면 오버플로우
  ```c
  char buf[100] = "Hi ";
  strcat(buf, "there");
  ```

  > n만큼 문자열 덧붙이기 `char *strncat(char *dest, const char *src, size_t n);`
  - `src`에서 최대 `n`바이트만 덧붙임
  - `dest`끝에 자동으로 NULL문자 붙여진다.
  - `src`의 문자열의 길이가 `n`보다 작다면 `src`의 NULL문자 까지만 붙여진다.
  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
    char str1[20];
    char str2[20];
    strcpy(str1, "To be ");
    strcpy(str2, "or not to be");
    strncat(str1, str2, 6);
    puts(str1); // To be or not
    return 0;
  }
  ```

  > 문자열 비교 `int strcmp(const char *s1, const char *s2);`
  - 문자열을 사전 순으로 비교
  - 같으면 0, s1 < s2면 음수, s1 > s2면 양수
  ```c
  if (strcmp("abc", "abd") < 0) {
      printf("abc < abd\n");
  }
  ```

  > n개의 문자열 비교 `int strncmp(const char *s1, const char *s2, size_t n);`

  - 앞에서 최대 `n` 바이트까지만 비교
  - NULL문자에 먼저 도달하면 종료
  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
    char str[][5] = {"R2D2", "C3PO", "R2A6"};
    int n;
    puts("Looking for R2 astromech droids...");
    for (n = 0; n < 3; n++)
      if (strncmp(str[n], "R2xx", 2) == 0) {
        printf("found %s\n", str[n]);
      }
    return 0;
  }
  ```

  > 문자열 검색 `char *strchr(const char *s, int c);`

  - 문자열에서 문자 `c`가 **처음** 나오는 위치를 반환
  - 문자열 맨 끝 부분을 가리키는 포인터를 얻기 위해 `c`에 NULL을 사용할 수 도 있음
  - 없으면 `NULL`
  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
    char str[] = "This is a sample string";
    char* pch;
    printf("Looking for the 's' character in \"%s\"...\n", str);

    pch = strchr(str, 's');

    while (pch != NULL) {
      printf("found at %d\n", pch - str + 1);
      pch = strchr(pch + 1, 's');
    }

    return 0;
  }
  ```


  > `char *strrchr(const char *s, int c);`

  - 문자열에서 문자 `c`가 **마지막**에 나오는 위치 반환
  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
    char str[] = "This is a sample string";
    char* pch;
    pch = strrchr(str, 's');
    printf("Last occurence of 's' found at %d \n", pch - str + 1);  //18
    return 0;
  }
  ```


  > `char *strstr(const char *haystack, const char *needle);`
  - `haystack` 문자열 안에 `needle`이 **처음 나오는 위치** 반환
  - 일치하는 문자열이 없을 경우 NULL 포인터 반환
  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
    char str[] = "This is a simple string";
    char* pch;
    pch = strstr(str, "simple");
    strncpy(pch, "sample", 6);  // this is a sample string
    puts(str);
    return 0;
  }
  ```


  > `char *strpbrk(const char *s, const char *accept);`

  - `s`에서 `accept`에 포함된 문자 중 **하나라도 처음 나오는 위치** 반환
  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
    char str[] = "This is a sample string";
    char key[] = "aeiou";
    char* pch;
    printf("Vowels in '%s': ", str);
    pch = strpbrk(str, key);

    while (pch != NULL) {
      printf("%c ", *pch);
      pch = strpbrk(pch + 1, key);
    }
    printf("\n");

    return 0;
  }
  ```


  > `size_t strcspn(const char *s, const char *reject);`

  - `s`에서 `reject`에 포함된 문자가 **처음 나오는 위치의 인덱스** 반환
  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
    char str[] = "fcba73";
    char keys[] = "1234567890";
    int i;
    i = strcspn(str, keys);
    printf("The first number in str is at position %d.\n", i + 1);  // 5
    return 0;
  }
  ```

  > 문자열 분할 `char *strtok(char *str, const char *delim);`

  - 문자열 `str`을 `delim` 기준으로 잘라서 **첫 토큰** 반환
  - 이후에는 `str`에 `NULL` 넣어서 **다음 토큰** 반환
  - 내부 static 포인터를 쓰므로 **스레드 안전하지 않음**
  ```c
  #include <stdio.h>
  #include <string.h>
  int main() {
    char str[] = "- This, a sample string.";
    char* pch;
    printf("Splitting string \"%s\" into tokens:\n", str);
    pch = strtok(str, " ,.-");
    while (pch != NULL) {
      printf("%s\n", pch);  
      pch = strtok(NULL, " ,.-");
    }
    return 0;
  }
  ```
  결과
  ```bash
  this
  is
  a
  sample
  string
  ```


  > 문자열 복제 (POSIX), (C23) `char *strdup(const char *s);`

  - NULL 종료 문자열 `s`를 복사해 **동적 할당된 새 문자열** 반환 (`malloc` 사용)
  - 사용 후 `free()` 필요
  - 실패시 NULL 반환
  ```c
  #include <string.h>
  #include <stdio.h>
  #include <stdlib.h>
  
  int main(void)
  {
      const char *s1 = "Duplicate me!";
      char *s2 = strdup(s1);
      printf("s2 = \"%s\"\n", s2);
      free(s2);
  }
  ```

  > 메모리 복사
  ```c
  void *memcpy(void *restrict dest, const void *restrict src, size_t count);
  ```
  - `src` 메모리에서 `count` 바이트를 **`dest`로 그대로 복사**
  - **두 메모리가 겹치면 동작이 정의되지 않음**
  - 반환값은 `dest`

  구현 원리
  - 내부적으로는 바이트 단위 또는 word 단위 복사를 빠르게 처리
  - 대부분의 구현은 CPU 명령어 최적화 (`SSE`, `AVX` 등)

  성능
  - **굉장히 빠름** (대부분의 경우 수동 루프보다 효율적)
  - `strcpy`, `memmove`보다 일반적으로 빠름 (널 확인, 겹침 처리 안 하기 때문)

  위험성
  - `dest`와 `src`가 겹치면 **데이터 깨짐**
  - 유효하지 않은 포인터나 count를 넘는 크기 복사 → **미정의 동작**
  - `restrict` 키워드가 붙은 이후(C99부터) **동일 메모리 참조 시 UB**


  ```c
  char src[] = "ABCDEF";
  char dest[10];
  memcpy(dest, src, 6); // 'A', 'B', ..., '\0' 까지 복사
  ```

  > memcpy_s (C11 bounds-checking version)

  ```c
  errno_t memcpy_s(void *restrict dest, rsize_t destsz,
                  const void *restrict src, rsize_t count);
  ```
  - `count` 바이트 복사하려고 할 때, **다음 조건을 만족해야 정상 동작**:
    - `dest != NULL`
    - `src != NULL`
    - `count <= destsz`
    - `destsz <= RSIZE_MAX`
    - `src`와 `dest`는 겹치지 않아야 함
  - 위 조건을 위반하면:
    - **`dest` 영역 전체를 0으로 초기화**
    - **등록된 제약 처리기(기본은 abort 또는 ignore)가 호출됨**
    - **반환값이 `!= 0`**

  장점
  - **런타임에서 오류를 감지할 수 있음**
  - **안전성 강화**, 보안 코딩에 적합

  단점
  - **느리다**
  - `__STDC_LIB_EXT1__` 가 정의되어 있어야 사용 가능 (즉, 구현체가 지원해야 함)
  - 사용 전에 `#define __STDC_WANT_LIB_EXT1__ 1` 필요

  ```c
  #define __STDC_WANT_LIB_EXT1__ 1
  #include <string.h>

  char src[] = "12345";
  char dst[5];

  // 정상 복사
  memcpy_s(dst, sizeof(dst), src, 5);

  // 실패 (count > destsz), dst는 전부 '\0'로 초기화됨
  memcpy_s(dst, 5, src, 6);
  ```


  비트 해석 (aliasing 문제 우회)

  ```c
  double d = 0.1;
  int64_t i;
  memcpy(&i, &d, sizeof(d)); // 안전
  ```

  > `void *memmove(void *dest, const void *src, size_t n);`

  ```c
  void *memmove(void *dest, const void *src, size_t count);
  ```

  용도
  - 메모리 블록을 **안전하게 복사**
  - `src`와 `dest` **겹치는 경우에도 안전하게 동작**
  - `memcpy()`와 다르게 **overlap 허용**

  동작
  - 내부적으로 `src < dest`인 경우 **뒤에서부터 복사**
  - `src >= dest`인 경우 **앞에서부터 복사**
  - 이 방식은 "as if temporary buffer"처럼 보이지만, 실제 구현은 **임시 버퍼를 쓰지 않고 방향만 바꾼다**

  성능
  - `memcpy`보다 약간 느릴 수 있음 (복사 방향 판단 필요)
  - 겹침이 없으면 내부적으로 `memcpy`로 최적화되기도 함

  위험성
  - `dest` 또는 `src`가 `NULL` → 정의되지 않은 동작
  - `count`가 잘못된 경우 → 버퍼 오버런 발생 가능
  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
      char data[] = "1234567890";
      memmove(data + 4, data + 3, 3); // '4', '5', '6' → '5', '6', '7' 위치로 복사
      puts(data); // 출력: 1234456890
      return 0;
  }
  ```

  > `memmove_s` (C11 bounds-checking extension)

  ```c
  errno_t memmove_s(void *dest, rsize_t destsz, const void *src, rsize_t count);
  ```
  용도
  - `memmove`에 **런타임 제약 검사**를 추가
  - **버퍼 오버플로우**, **NULL 포인터**, **겹침 여부** 등을 체크함

  조건 위반 시 동작
  - `dest != NULL` && `destsz` 유효하면 → `dest` 전체를 0으로 초기화
  - 등록된 제약 처리기 함수(`abort`, `ignore`, `custom`)가 호출됨
  - 반환값은 `0` (성공) 또는 **비 0** (에러)

  성능
  - 추가 검사 때문에 `memmove`보다 느림
  - 하지만 안전성 면에서 우위

  사용 조건
  - 사용 전 반드시 다음 전처리기 정의 필요:
    ```c
    #define __STDC_WANT_LIB_EXT1__ 1
    ```
  - `<string.h>` 포함 전에 정의해야 함

  ```c
  #define __STDC_WANT_LIB_EXT1__ 1
  #include <string.h>
  #include <stdio.h>

  int main() {
      char src[] = "ABCDE";
      char dst[] = "12345";

      int r = memmove_s(dst, sizeof(dst), src, 3);  // 정상 복사
      printf("dst: %s, result: %d\n", dst, r);      // dst: ABC45

      r = memmove_s(dst, 3, src, 5);  // count > destsz → 오류
      printf("result: %d\n", r);      // dst는 전부 '\0'로 초기화됨
      return 0;
  }
  ```


  > `void *memset(void *s, int c, size_t n);`

  ```c
  void *memset(void *dest, int ch, size_t count);
  ```

  기능
  - 메모리 블록을 `ch`로 `count`바이트만큼 채운다.
  - `ch`는 `unsigned char`로 변환된다.
  - 반환값은 `dest`.

  위험성
  - `dest == NULL`, `count` 과다 → 정의되지 않은 동작
  - 버퍼 경계를 넘어서 채우면 메모리 손상
  - 컴파일러 최적화에 의해 제거될 수 있음 (예: 비밀번호 초기화용으로 부적절)

  성능
  - 매우 빠름 (단순 반복/하드웨어 가속 있음)


  ```c
  char buf[10] = "abcdefghi";
  memset(buf, '*', 5); // buf: "*****fghi"
  ```


  > `memset_explicit` (C23)

  ```c
  void *memset_explicit(void *dest, int ch, size_t count);
  ```

  기능
  - `memset`과 동일하지만 **컴파일러 최적화로 제거되지 않도록 보장**됨
  - 민감한 정보(예: 비밀번호, 키 등) 지우기에 사용

  목적
  - 컴파일러가 "이 값 어차피 안 쓰니까 memset 없애도 되지?" 라고 판단하는 걸 **막기 위한 함수**

  위험성
  - 잘못된 포인터나 크기를 넣으면 여전히 정의되지 않은 동작

  ```c
  #include <string.h>

  void secure_erase(char *buf, size_t len) {
      memset_explicit(buf, 0, len); // 보안용 초기화
  }
  ```


  > `memset_s` (C11 + Annex K: bounds-checking extension)

  ```c
  errno_t memset_s(void *dest, rsize_t destsz, int ch, rsize_t count);
  ```

  기능
  - `memset` + **런타임 안전성 검사**
  - 조건 위반 시 `dest`를 모두 `ch`로 채운 후, **제약 처리 함수 호출** (기본: abort)

  사용 조건
  - `#define __STDC_WANT_LIB_EXT1__ 1`를 `<string.h>` 포함 전에 선언해야 함
  - 구현체에서 `__STDC_LIB_EXT1__`도 정의되어 있어야 사용 가능

  체크 조건 (실패 시 오류 반환):
  - `dest == NULL`
  - `count > destsz`
  - `count > RSIZE_MAX`
  - `destsz > RSIZE_MAX`

  실패 시 동작
  - `dest`가 유효하면 전체를 `ch`로 채움
  - 오류 반환 코드 반환 (예: `EINVAL`, `ERANGE`, etc.)


  ```c
  #define __STDC_WANT_LIB_EXT1__ 1
  #include <string.h>
  #include <stdio.h>

  int main() {
      char str[] = "hello world";
      memset_s(str, sizeof(str), 0, 5);  // 앞 5바이트만 0으로 채움
      puts(str);                         // "\0\0\0\0\0 world" 출력

      int r = memset_s(str, 5, 0, 10);   // count > destsz → 오류
      printf("result: %d\n", r);
      return 0;
  }
  ```

  >`memcmp()` 

  ```c
  #include <string.h>

  int memcmp(const void *lhs, const void *rhs, size_t count);
  ```

  기능

  - `lhs`와 `rhs`가 가리키는 메모리 블록의 앞쪽 `count` 바이트를 **바이트 단위로 비교**
  - 리턴값은 다음과 같다:

  | 반환값           | 의미                                         |
  |------------------|----------------------------------------------|
  | `< 0`            | `lhs`가 `rhs`보다 **사전 순으로 앞**        |
  | `== 0`           | `lhs`와 `rhs`가 **같다 (동일한 바이트열)** |
  | `> 0`            | `lhs`가 `rhs`보다 **사전 순으로 뒤**        |

  - **unsigned char** 단위로 비교하므로, 음수/양수 부호 차이는 없음



  동작 원리

  - `memcmp(lhs, rhs, n)`은 아래와 유사하게 동작:

  ```c
  int memcmp(const void *lhs, const void *rhs, size_t n) {
      const unsigned char *p1 = lhs, *p2 = rhs;
      for (size_t i = 0; i < n; ++i) {
          if (p1[i] != p2[i])
              return p1[i] - p2[i];  // int로 승격된 차이
      }
      return 0;
  }
  ```

  
  위험성

  - `lhs`, `rhs` 중 하나라도 `NULL` → **정의되지 않은 동작**
  - `count`가 실제 메모리 범위를 초과 → **메모리 접근 오류**
  - 구조체 비교 시 **padding byte 포함** → 예상과 다르게 동작할 수 있음

  ```c
  struct S { char c; int i; }; // padding 존재 가능
  memcmp(&s1, &s2, sizeof(struct S)); // padding까지 비교됨
  ```


  예제

  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
      char a[] = "abc";
      char b[] = "abd";

      int cmp = memcmp(a, b, 3); // 'c' < 'd' → 음수 반환
      if (cmp < 0)
          puts("a < b");
      else if (cmp > 0)
          puts("a > b");
      else
          puts("a == b");

      return 0;
  }
  ```


  성능

  - **O(n)** 바이트 순차 비교
  - 대부분의 libc 구현은 8/16/32비트 단위로 블록 비교하도록 최적화
  - `strncmp()`보다 빠름 (`'\0'` 검사 없음)

  
 실무 사용 주의

  1. **단순한 메모리 블록 비교에만 사용**
    - 구조체, float, union, padding, endian 문제 발생 가능

  2. **문자열 비교는 `strcmp` 또는 `strncmp` 사용**
    - `memcmp`은 `'\0'`을 무시하고 개수만큼 비교함

  3. **보안 비교에는 부적절**
    - `memcmp`은 차이를 발견하는 즉시 반환 → 시간 차이 발생
    - 암호 비교에는 `constant-time memcmp()`가 따로 필요

 다음은 `memchr()` 함수에 대한 완전 정리이다. 정의, 동작 원리, 위험성, 성능, 예제까지 포함한다.



  > `memchr`

  ```c
  void *memchr(const void *ptr, int ch, size_t count);
  ```
  (C23부터는 **타입 제네릭 버전**도 도입됨, 아래에 설명)

  동작

  - `ptr`로 지정된 메모리 블록의 처음 `count` 바이트에서 **`(unsigned char)ch`와 일치하는 첫 번째 바이트**를 찾는다.
  - 찾으면 **그 바이트의 주소 반환**, 없으면 `NULL` 반환.
  - `ch`는 정수지만 내부적으로는 `unsigned char`로 해석됨.



  ## 동작 원리 (요약 구현)

  ```c
  void *memchr(const void *ptr, int ch, size_t count) {
      const unsigned char *p = ptr;
      for (size_t i = 0; i < count; ++i) {
          if (p[i] == (unsigned char)ch)
              return (void *)(p + i);
      }
      return NULL;
  }
  ```



  반환값

  - 일치하는 바이트의 포인터
  - 없으면 `NULL`


  ```c
  #include <stdio.h>
  #include <string.h>

  int main() {
      const char data[] = "ABCDEFG";
      char *found = memchr(data, 'D', strlen(data));

      if (found)
          printf("Found at: %s\n", found); // 출력: DEFG
      else
          printf("Not found\n");

      return 0;
  }
  ```

  성능

  - **O(n)** (최대 `count` 바이트까지 직선 탐색)
  - 일부 구현(libc 등)은 word 단위로 벡터화하여 최적화함
  - `strchr`보다 빠를 수 있음 (`'\0'` 체크 없음)


  위험성

  - `ptr == NULL`이면 → 정의되지 않은 동작
  - `count`가 실제 유효 메모리 크기보다 크면 → **버퍼 오버런**
  - **구조체**, **비NUL 종료 문자열**에 사용 시 주의
  - 정수 `ch`는 항상 `unsigned char`로 처리됨에 주의


  > C23 확장: 타입 제네릭 `memchr`

  ```c
  void *memchr(/*type-generic*/ *ptr, int ch, size_t count); // C23
  ```

  - `ptr`의 타입에 따라 반환값이 `void *` 또는 `const void *` 자동 결정됨
  - 예:
    ```c
    const char *s = "ABC";
    auto result = memchr(s, 'B', 3); // result 타입: const void *
    ```

  실무에서 주의할 점

  - 문자열에서 `strchr()` 대신 사용하면 `'\0'`까지 안 가도 동작 가능
  - 바이너리 데이터 검색에 유용
  - 보안 관련 코드에서는 반드시 유효한 범위 내에서만 사용해야 함


  > `gets`

  ```c
  char *gets(char *str); // <stdio.h>
  ```

  기능
  - 표준 입력(`stdin`)에서 **개행 전까지 문자**를 `str` 버퍼에 복사
  - `'\n'`은 버리고, 마지막에 `'\0'` 붙임

  위험성 (심각)
  - **입력 길이 제한 없음**
  - 버퍼 크기보다 긴 입력이 들어오면 **버퍼 오버플로우 발생**
  - **해킹 공격의 대표적인 진입점**
  - **C11부터 완전히 삭제됨** (표준 라이브러리에서 제거됨)

  결론
  ```c
  // 절대 사용 금지
  char buf[10];
  gets(buf);  // 취약점 발생 가능성 100%
  ```



  > `gets_s` (C11 Annex K, bounds-checked version)
  ```c
  #define __STDC_WANT_LIB_EXT1__ 1
  #include <stdio.h>

  char *gets_s(char *str, rsize_t n); // only if __STDC_LIB_EXT1__ is defined
  ```

  기능
  - 최대 `n - 1`개의 문자를 읽고, 항상 마지막에 `'\0'`을 넣음
  - `'\n'`은 버림
  - 만약 줄 끝(`\n`) 또는 EOF 전에 `n - 1`을 초과하면:
    - **입력 스트림에서 남은 글자를 모두 버림**
    - **오류 처리기 호출 (abort 등)**

  제약 조건 (모두 위반 시 오류)

  | 조건 위반      | 결과                                    |
  |----------------|------------------------------------------|
  | `str == NULL`  | 제약 오류                                |
  | `n == 0`       | 제약 오류                                |
  | `n > RSIZE_MAX`| 제약 오류                                |
  | 줄 끝 전에 `n-1` 이상 입력됨 | 입력 무시 + 오류 처리기 호출 |

  반환값
  - 성공 시 `str` 포인터
  - 실패 시 `NULL` + 입력 스트림 정리됨


  ```c
  #define __STDC_WANT_LIB_EXT1__ 1
  #include <stdio.h>

  int main() {
  #ifdef __STDC_LIB_EXT1__
      char buf[10];
      set_constraint_handler_s(ignore_handler_s); // abort 방지

      if (gets_s(buf, sizeof(buf))) {
          printf("입력: %s\n", buf);
      } else {
          printf("gets_s 실패 또는 입력 초과\n");
      }
  #else
      puts("gets_s는 이 구현에서 지원되지 않음");
  #endif
      return 0;
  }
  ```


  > `fgets`

  ```c
  char buf[100];
  if (fgets(buf, sizeof(buf), stdin)) {
      // fgets는 \n 포함됨, 필요시 제거
      buf[strcspn(buf, "\n")] = '\0';
  }
  ```

  - 입력 길이 제한을 명시할 수 있음
  - 줄바꿈 문자를 제거하려면 후처리 필요
  - 표준 C89부터 항상 지원됨
