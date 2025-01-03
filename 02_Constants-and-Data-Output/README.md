# 2장 상수와 데이터 출력

# 프로그램 구조, 데이터 출력 방법 (예제 : 2-1 ~ 2-4)

stdio.h : standard input output 표준 입출력

## To main & CRT

### 스타터 코드

CRT(초기화 파일인 init.o와 CRTO.o)는 C 런타임 라이브러리(C-runtime library)를 의미합니다. 컴파일러가 미리 만들어서 main() 함수를 실행하기 위한 환경을 설정하고 main() 함수를 호출하는 역할을 합니다.

### 개념

CRT는 C 프로그램이 실행되기 전에 초기화 작업을 수행하는 코드 집합입니다. 이 초기화 작업에는 전역 변수를 초기화하거나, 동적 메모리 할당을 준비하는 등의 작업이 포함됩니다. CRT는 일반적으로 컴파일러에 의해 자동으로 링크되며, main() 함수가 호출되기 전에 실행됩니다.

### 예시

다음은 CRT가 어떻게 작동하는지 간단히 설명하는 예시입니다.

```c
// main.c 파일
#include <stdio.h>

int global_var = 10; // 전역 변수

void init_function() {
    printf("초기화 함수 호출\\\\n");
    // 초기화 작업 수행
}

int main() {
    printf("main 함수 시작\\\\n");
    printf("global_var: %d\\\\n", global_var);
    return 0;
}

```

```c
// CRT 초기화 코드 (컴파일러가 생성하는 코드의 예시)
void _start() {
    // 전역 변수 초기화
    global_var = 10;

    // 사용자 정의 초기화 함수 호출
    init_function();

    // main 함수 호출
    main();

    // 프로그램 종료 처리
    exit(0);
}

```

이 예시에서 `_start` 함수는 CRT 초기화 코드의 일부로, 전역 변수를 초기화하고 사용자 정의 초기화 함수를 호출한 후 main() 함수를 호출합니다. 실제로는 CRT 초기화 코드가 훨씬 복잡하지만, 이 예시는 기본적인 개념을 이해하는 데 도움이 됩니다.

```c
int main() {
    int k = 1; // 메모리(RAM)인 .STACK에 저장됨, 스택 포인터(SP): 메모리 어딘가에 스택의 위치를 나타냄, CRT가 처음의 SP의 위치를 잡아줌
} // 스택 프레임
//스택 포인터(Stack Pointer)는 현재 스택의 최상위 위치를 가리키는 포인터입니다. 스택은 함수 호출 시 지역 변수와 반환 주소 등을 저장하는 메모리 영역으로, 스택 포인터는 이 메모리 영역의 주소를 관리합니다. 스택 프레임이 생성되거나 제거될 때마다 스택 포인터는 그 위치를 업데이트하여 스택의 상태를 유지합니다.
```

### 제어 문자 : 문자는 아니지만 출력 형태를 바꾸는 문자

- \n : 라인 피드
- \r : 캐리지 리턴
- \t : 탭
- \b : 백스페이스 : 한칸 왼쪽으로 이동
- \a : alert 경보 : 벨소리출력

형식 지정자 : 숫자를 출력시 변환 문자를 사용해 문자열로 변환함

### 데이터 타입

1. 정수형 (integer)
    - bool: true/false
    - (signed/unsigned) char: 1B
    - short: 2B
    - int: 2B/4B
    - long: 4B
    - Unix 계열 타입: int8_t, int16_t, int32_t
2. 실수형 (real number)
    - float: 4B (유효숫자 7개)
    - double: 8B (유효숫자 15개)

### main 함수의 인수

```c
#include <stdio.h>

int main(int argc, char **argv) {
    printf("명령줄 인수의 개수: %d\\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\\n", i, argv[i]);
    }

    return 0;
}
```

이 프로그램을 컴파일하고 실행하는 과정과 결과를 살펴보겠습니다.

1. 프로그램을 `example.c`라는 파일에 저장합니다.
2. 터미널에서 다음 명령어를 입력해 컴파일합니다:
    
    ```
    gcc -o example example.c
    
    ```
    
3. 컴파일된 프로그램을 실행합니다:
    
    ```
    ./example arg1 arg2 arg3
    
    ```
    

이제 프로그램의 출력 결과를 살펴보겠습니다:

```
명령줄 인수의 개수: 4
argv[0]: ./example
argv[1]: arg1
argv[2]: arg2
argv[3]: arg3

```

이 예제에서:

- `argc`는 4입니다. 즉, 프로그램 이름을 포함하여 총 4개의 인수가 전달되었습니다.
- `argv` 배열에는 각 인수가 문자열로 저장되어 있습니다. `argv[0]`는 프로그램 실행 경로인 "./example"이고, `argv[1]`, `argv[2]`, `argv[3]`는 각각 "arg1", "arg2", "arg3"입니다.

이와 같이 `int main(int argc, char **argv)`를 사용하여 명령줄 인수를 받아 프로그램 내부에서 처리할 수 있습니다.

# 상수와 데이터 표현법 (예제 : 2-5 ~ 2-7)

### **상수(constant) : 값이 바뀌지 않는 데이터**

## 정수 상수

정수 상수는 소수점이 없는 숫자로, 예를 들어 1, -100, 42 등이 있습니다. 정수 상수는 양수일 수도 있고 음수일 수도 있습니다.

- **10진법(Decimal)**: 기본 숫자 체계로, 특별한 접두사 없이 숫자를 그대로 사용합니다. 예: `10`, `255`, `1024`.
- **2진법(Binary)**: `0b` 또는 `0B` 접두사를 사용하여 표현합니다. 예: `0b1010` (10진법으로 10), `0b11111111` (10진법으로 255).
- **8진법(Octal)**: `0` 접두사를 사용하여 표현합니다. 예: `012` (10진법으로 10), `0377` (10진법으로 255).
- **16진법(Hexadecimal)**: `0x` 또는 `0X` 접두사를 사용하여 표현합니다. 예: `0xA` (10진법으로 10), `0xFF` (10진법으로 255), `0x400` (10진법으로 1024).
- 

```c
#include <stdio.h>

int main() {
    // 10진법 정수 상수
    int decimal = 255;
    printf("10진법: %d\\n", decimal);

    // 2진법 정수 상수
    int binary = 0b11111111;
    printf("2진법: %d\\n", binary);

    // 8진법 정수 상수
    int octal = 0377;
    printf("8진법: %d\\n", octal);

    // 16진법 정수 상수
    int hexadecimal = 0xFF;
    printf("16진법: %d\\n", hexadecimal);

    // 실수 상수
    float pi = 3.14f;
    printf("실수: %f\\n", pi);

    // 문자 상수
    char letter = 'A';
    printf("문자: %c\\n", letter);

    // 문자열 상수
    char string[] = "Hello, World!";
    printf("문자열: %s\\n", string);

    return 0;
}

```

### 실행 결과

```
10진법: 255
2진법: 255
8진법: 255
16진법: 255
실수: 3.140000
문자: A
문자열: Hello, World!
```

### 2, 8, 16 진수로 값을 출력하는 예제

다음은 정수 값을 2진수, 8진수, 16진수로 출력하는 예제 코드입니다.

```c
#include <stdio.h>

int main() {
    int number = 255;

    // 10진법으로 출력
    printf("10진법: %d\\\\n", number);

    // 2진법으로 출력
    printf("2진법: %b\\\\n", number); // C에서는 직접적으로 %b를 지원하지 않으므로 별도의 함수 필요

    // 8진법으로 출력
    printf("8진법: %o\\\\n", number);

    // 16진법으로 출력
    printf("16진법: %x\\\\n", number);

    return 0;
}

```

위 코드는 C 언어에서 기본적으로 %b 형식을 지원하지 않기 때문에, 2진법 출력은 별도의 함수 구현이 필요합니다. 다음은 2진법 출력을 위한 예제 코드입니다.

```c
#include <stdio.h>

void printBinary(int n) {
    for (int i = 31; i >= 0; i--) {
        int bit = (n >> i) & 1;
        printf("%d", bit);
        if (i % 4 == 0) printf(" "); // 가독성을 위해 4비트마다 공백 추가
    }
    printf("\\\\n");
}

int main() {
    int number = 255;

    // 10진법으로 출력
    printf("10진법: %d\\\\n", number);

    // 2진법으로 출력
    printf("2진법: ");
    printBinary(number);

    // 8진법으로 출력
    printf("8진법: %o\\\\n", number);

    // 16진법으로 출력
    printf("16진법: %x\\\\n", number);

    return 0;
}

```

### 실행 결과

```
10진법: 255
2진법: 0000 0000 0000 0000 0000 0000 1111 1111
8진법: 377
16진법: ff

```

## **실수 상수 : 소수점 형태 표기법, 지수 형태 표기법(정규화 표기법)**

![첫 번째 이미지](image/image1.png)
![두 번째 이미지](image/image2.png)
![세 번째 이미지](image/image3.png)


### 문자와 문자열

- 문자(character) : 작은 따옴표, 아스키값 ,'X’, %c
- 문자열(string) : 큰 따옴표, 4바이트의 주소값,  "X", %s

# 컴파일 후의 상수 형태

```c
int i = 123455678;
printf("address of i is %d\n", &i);
printf("size of i is %d\n", sizeof(i));
printf("size of i is %d\n", sizeof(&i)); // 32bit 컴파일러는 포인터 크기가 4byte이다.

printf("%c\n", 'A'); // A (65의 값을 아스키 코드를 찾아서 반환)
printf("%d\n", 'A'); // 65

printf("%c\n", "A"); // 프로그램 어딘가에 저장된 "A"가 저장된 곳을 가리키는 주소 값이다.
printf("%d\n", "A"); // 4바이트의 주소값
printf("%s\n", "A"); // A, LCO: hello world, 포인터 상수(주소), 프로그램 안에 A란 문자가 저장되어 있는데 그 주소값을

```

![Untitled](2%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%89%E1%85%A1%E1%86%BC%E1%84%89%E1%85%AE%E1%84%8B%E1%85%AA%20%E1%84%83%E1%85%A6%E1%84%8B%E1%85%B5%E1%84%90%E1%85%A5%20%E1%84%8E%E1%85%AE%E1%86%AF%E1%84%85%E1%85%A7%E1%86%A8%203732f0859dad4576be5f5214074ca9dd/Untitled.png)
