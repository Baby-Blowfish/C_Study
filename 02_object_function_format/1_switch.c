#include <stdio.h>
void swap(int,int);
void swapByAddress(int *,int *);

int j;
void f(int i);
void g(int j);
void increment(void);
int main(void)
{
    int a = 10; // 지역 변수
    int b = 20;
    swap(a,b);
    printf("main : a = %d, b = %d\n",a,b);
    swapByAddress(&a,&b);
    printf("main : a = %d, b = %d\n",a,b);
    f(a);
    g(a);
    printf("main : j = %d\n",j);
    
    for(int i = 0; i < 5; i++)
    {
      increment();
    }

    return 0;
}

void swap(int a,int b)
{
    int temp = a;
    a = b;
    b = temp;
    printf("swap : a = %d, b = %d\n",a,b);
}

void swapByAddress(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void f(int i) // i의 블록 범위 시작
{
    int j = 1; // j의 블록 범위 시작, 파일 범위에서 선언된 j와 동일한 이름의 변수를 숨김
    i++;      // i는 함수의 매개변수를 참조함
    for(int i = 0; i < 2; i++) // i는 함수의 지역 변수를 참조함
    {
        int j = 2; // j의 내부 블록 범위 시작, 외부 j를 숨김
        printf("f : j = %d\n",j); //j = 2 출력 
    }
    printf("f : j = %d\n",j); //j = 1 출력
}

void g(int j) // j의 블록 범위 시작
{
    j++;
    printf("g : j = %d\n",j); // 내부 j+1 출력
}

void increment(void)
{
  static unsigned int counter = 0; // 정적 변수, 프로그램 시작부터 종료까지 메모리에 존재, 초기화 하지 않으면 0으로 초기화, 프로그램 시작시 한번만 초기화 수행, 마지막으로 저장된 값이 유지됨
  counter++;
  printf("counter = %d\n",counter);
}


/*
개체(object) : 값을 표현할 수 있는 스토리지(storage), 실행 환경에서 해당 내용이 값을 표현할 수 있는 데이터스토리지의 영역

변수(variable) : 개체중 하나, 개체의 종류를 알려주는 형식(type) 선언 필요→ why  개체를 표현하는 비트 집합이 다른 유형의 개체로 해석되면 다른 값을 가지게 됨

함수(function) : 개체는 아니지만 형식을 가짐, 함수형(function type) : 반환형(return type) + 함수의 매개변수 개수 + 유형

포인터(pointer): 개체나 함수가 저장되는 메모리의 위치를 나타내는 주소(address), 포인터형(pointer type) = 참조형(referenced type)인 함수형과 개체형에서 파생됨, 개체 포인터와 함수 포인터는 다르게 취급

변수선언 :  object type    identifier    =    initializer;  ,  변수형식 식별자 = 초기값;

복합문(compound statement) : 여러 문장을 하나의 문장으로 처리하는 문장, 중괄호(brace)로 묶음

1. 리터럴 상수(literal constant) : 컴파일 시간에 값이 결정되는 상수, 예시 : 10, 3.14, 'A'

2. 상수 식(constant expression) : 컴파일 시간에 값이 결정되는 상수 식, 예시 : 10 + 5, 3.14 * 2, 'A' + 1

3. enum 멤버(enum member) : 열거형(enum)에서 정의된 상수, 예시 : enum { RED, GREEN, BLUE };에서 RED, GREEN, BLUE

4. alignof, sizeof 연산자의 결과 : 컴파일 시간에 값이 결정되는 상수 식, 예시 : sizeof(int), alignof(double)







===========================================
스토리지 기간(storage duration) : 변수가 메모리에 존재하는 기간, 컴파일 시간(compile time)에 결정됨
===========================================

정적 스토리지 기간(static storage duration) : 프로그램이 시작되고 종료될 때까지 변수가 메모리에 존재하는 기간, 정적 변수(static variable)

자동 스토리지 기간(automatic storage duration) : 함수가 호출될 때 변수가 메모리에 존재하는 기간, 변수가 정의된 블록 내에서 유효, 자동 변수(automatic variable)

스레드 스토리지 기간(thread storage duration) : 스레드가 시작되고 종료될 때까지 변수가 메모리에 존재하는 기간, 스레드 변수(thread variable)

할당 스토리지 기간(allocated storage duration) : 동적으로 할당된 메모리, 할당 변수(allocated variable)





===========================================
[변수 분류 기준]
===========================================

C 언어에서 변수는 두 가지 기준으로 분류됩니다:

1. 스토리지 기간(storage duration)에 따른 분류
   - 정적 스토리지 기간(static storage duration)
   - 자동 스토리지 기간(automatic storage duration)

2. 스코프(scope)에 따른 분류
   - 전역 스코프(global scope)
   - 지역 스코프(local scope)



===========================================
[변수 유형 정의]
===========================================

1. 정적 변수(static variable)
   - static 키워드로 선언된 변수
   - 정적 스토리지 기간을 가짐 (프로그램 시작부터 종료까지 메모리에 존재)
   - 초기화하지 않으면 0으로 초기화됨
   - 프로그램 시작시 한번만 초기화 수행, 마지막으로 저장된 값이 유지됨
   - 초기화에 사용되는 값은 컴파일 타임에 결정될 수 있는 상수여야함.
   - 리터럴 상수, 상수 식, enum 멤버, alignof,sizeof 연산자의 결과 가능, const 변수는 가능하지 않음
   - 스코프에 따라 두 가지로 나뉨:
     * 함수 내부에서 선언된 정적 변수: 함수 내에서만 접근 가능
     * 함수 외부에서 선언된 정적 변수: 파일 내에서만 접근 가능

2. 자동 변수(automatic variable)
   - auto 키워드로 선언되거나 키워드 없이 함수 내에서 선언된 변수
   - 자동 스토리지 기간을 가짐 (함수 호출 시 생성되고 함수 종료 시 소멸)
   - 지역 스코프를 가짐 (선언된 블록 내에서만 접근 가능)

3. 지역 변수(local variable)
   - 함수나 블록 내에서 선언된 변수
   - 지역 스코프를 가짐 (선언된 블록 내에서만 접근 가능)
   - 대부분 자동 스토리지 기간을 가짐 (블록 종료 시 소멸)
   - 정적 지역 변수(static local variable)는 정적 스토리지 기간을 가짐

4. 전역 변수(global variable)
   - 모든 함수 외부에서 선언된 변수
   - 전역 스코프를 가짐 (프로그램 전체에서 접근 가능)
   - 정적 스토리지 기간을 가짐 (프로그램 종료 시까지 존재)
   - static 키워드 없이 선언된 전역 변수는 다른 파일에서도 접근 가능
   - static 키워드로 선언된 전역 변수는 파일 내에서만 접근 가능





===========================================
[변수 유형 관계]
===========================================

- 정적 변수는 스토리지 기간에 따른 분류이며, 지역 변수와 전역 변수 모두에 적용될 수 있음
- 자동 변수는 스토리지 기간에 따른 분류이며, 주로 지역 변수에 적용됨
- 지역 변수는 스코프에 따른 분류이며, 자동 스토리지 기간 또는 정적 스토리지 기간을 가질 수 있음
- 전역 변수는 스코프에 따른 분류이며, 정적 스토리지 기간을 가짐




===========================================
[매개변수와 인수]
===========================================

1. 매개변수(Parameter)
   - 함수 정의에서 선언된 변수
   - 함수가 호출될 때 전달받는 값을 저장하는 변수
   - 함수 내부에서 지역 변수로 취급됨
   - 함수 호출 시 인수의 값이 복사되어 매개변수에 할당됨
   - 함수 내에서 매개변수를 수정해도 원래 인수에는 영향을 주지 않음 (값에 의한 호출)
   - 예시: void swap(int a, int b)에서 a와 b는 매개변수

2. 인수(Argument)
   - 함수 호출 시 전달하는 값이나 변수
   - 함수 호출 시 매개변수에 전달되는 실제 값
   - 함수 호출 시 인수의 값이 매개변수로 복사됨
   - 인수는 상수, 변수, 표현식 등이 될 수 있음
   - 예시: swap(a, b)에서 a와 b는 인수

3. 매개변수와 인수의 관계
   - 함수 호출 시 인수의 값이 매개변수로 복사됨
   - 매개변수는 함수 내부에서 지역 변수로 취급됨
   - 매개변수를 수정해도 원래 인수에는 영향을 주지 않음 (값에 의한 호출)
   - 포인터를 사용하면 인수의 값을 함수 내에서 수정할 수 있음 (참조에 의한 호출)






===========================================
[함수 호출 방식]
===========================================

1. 값에 의한 호출(Call by Value)
   - 함수 호출 시 인수의 값이 매개변수로 복사됨
   - 함수 내에서 매개변수를 수정해도 원래 인수에는 영향을 주지 않음
   - C 언어의 기본 호출 방식
   - 메모리 사용량이 적고 안전함
   - 예시:
     ```c
     void swap(int a, int b) {
         int temp = a;
         a = b;
         b = temp;
         printf("함수 내부: a = %d, b = %d\n", a, b);
     }
     
     int main() {
         int x = 10, y = 20;
         printf("함수 호출 전: x = %d, y = %d\n", x, y);
         swap(x, y);  // 값에 의한 호출
         printf("함수 호출 후: x = %d, y = %d\n", x, y);
         // x와 y의 값은 변경되지 않음
         return 0;
     }
     ```

2. 주소에 의한 호출(Call by Address)
   - * : 간접참조 연산자(indirect reference operator)
   - & : 주소 연산자(address operator)
   - 함수 호출 시 인수의 주소가 매개변수로 전달됨
   - 함수 내에서 매개변수를 통해 인수의 값을 직접 수정할 수 있음
   - C 언어에서는 포인터를 사용하여 구현
   - 메모리 효율적이고 큰 데이터 구조를 전달할 때 유용함
   - 예시:
     ```c
     void swapByAddress(int *a, int *b) {
         int temp = *a;
         *a = *b;
         *b = temp;
         printf("함수 내부: *a = %d, *b = %d\n", *a, *b);
     }
     
     int main() {
         int x = 10, y = 20;
         printf("함수 호출 전: x = %d, y = %d\n", x, y);
         swapByAddress(&x, &y);  // 주소에 의한 호출
         printf("함수 호출 후: x = %d, y = %d\n", x, y);
         // x와 y의 값이 변경됨
         return 0;
     }
     ```

3. 참조에 의한 호출(Call by Reference)
   - 함수 호출 시 인수의 참조(별칭)가 매개변수로 전달됨
   - 함수 내에서 매개변수를 통해 인수의 값을 직접 수정할 수 있음
   - C 언어에서는 직접적으로 지원하지 않음 (C++에서는 지원)
   - C 언어에서는 포인터를 사용하여 주소에 의한 호출로 구현
   - 코드가 더 간결하고 가독성이 좋음
   - 예시 (C++):
     ```cpp
     void swapByReference(int &a, int &b) {
         int temp = a;
         a = b;
         b = temp;
         printf("함수 내부: a = %d, b = %d\n", a, b);
     }
     
     int main() {
         int x = 10, y = 20;
         printf("함수 호출 전: x = %d, y = %d\n", x, y);
         swapByReference(x, y);  // 참조에 의한 호출
         printf("함수 호출 후: x = %d, y = %d\n", x, y);
         // x와 y의 값이 변경됨
         return 0;
     }
     ```
===========================================
[호출 방식 선택 기준]
===========================================

1. 값에 의한 호출(Call by Value) 사용 시기
   - 인수의 값을 변경할 필요가 없을 때
   - 작은 크기의 데이터를 전달할 됨됨
   - 안전성이 중요할 때

2. 주소에 의한 호출(Call by Address) 사용 시기
   - 인수의 값을 변경해야 할 때
   - 큰 크기의 데이터 구조를 전달할 때
   - 메모리 효율성이 중요할 때

3. 참조에 의한 호출(Call by Reference) 사용 시기
   - C++을 사용할 때
   - 코드 가독성이 중요할 때
   - 인수의 값을 변경해야 할 때





===========================================
[const 한정자]
===========================================

1. const의 기본 개념
   - 변수를 상수화하는 한정자(qualifier)
   - 선언된 변수의 값을 변경할 수 없도록 제한
   - 선언과 동시에 초기화 필요
   - 컴파일러가 값 변경 시도를 감지하고 에러 발생

2. const와 포인터의 관계
   A. const int* ptr 또는 int const* ptr
      - 포인터가 가리키는 값을 수정할 수 없음
      - 포인터 자체는 다른 주소를 가리킬 수 있음
      ```c
      int num = 10;
      const int* ptr = &num;  // 또는 int const* ptr = &num;
      // *ptr = 20;          // 컴파일 에러: 가리키는 값 수정 불가
      ptr = &other_num;      // 가능: 다른 변수 주소로 변경 가능
      ```

   B. int* const ptr
      - 포인터 자체가 상수
      - 포인터가 가리키는 주소를 변경할 수 없음
      - 가리키는 값은 변경 가능
      ```c
      int num = 10;
      int* const ptr = &num;
      *ptr = 20;            // 가능: 가리키는 값 변경 가능
      // ptr = &other_num;  // 컴파일 에러: 주소 변경 불가
      ```

   C. const int* const ptr
      - 포인터와 가리키는 값 모두 상수
      - 포인터가 가리키는 주소도, 값도 변경 불가
      ```c
      int num = 10;
      const int* const ptr = &num;
      // *ptr = 20;        // 컴파일 에러: 값 변경 불가
      // ptr = &other_num; // 컴파일 에러: 주소 변경 불가
      ```

3. const의 주요 활용
   A. 함수 매개변수 보호
      ```c
      // 원본 데이터 보호: 읽기만 가능
      void printArray(const int* arr, int size) {
          for(int i = 0; i < size; i++) {
              printf("%d ", arr[i]);
              // arr[i] = 0;  // 컴파일 에러: 배열 요소 수정 불가
          }
      }
      ```

   B. 상수 데이터 선언
      ```c
      const double PI = 3.14159;
      const char* ERROR_MSG = "Error occurred";
      ```

   C. 구조체 멤버 보호
      ```c
      struct Config {
          const int MAX_USERS;    // 상수 멤버
          const char* SERVER_IP;  // 상수 문자열 포인터
      };
      ```

4. const vs #define
   - const: 타입 안전성, 디버깅 가능, 범위 제한 가능
   - #define: 단순 텍스트 치환, 타입 없음, 전처리기에서 처리
   ```c
   #define MAX_SIZE 100    // 타입 없는 매크로 상수
   const int kMaxSize = 100;  // 타입이 있는 상수
   ```

5. const 사용 시 주의사항
   - 선언과 동시에 초기화 필수
   - 포인터 사용 시 const 위치에 따른 의미 차이 주의
   - 함수 매개변수로 사용 시 원본 데이터 보호 목적 명확히
   ```c
   const int NUM;        // 에러: 초기화 필요
   const int MAX = 100;  // 정상
   ```


 

*/