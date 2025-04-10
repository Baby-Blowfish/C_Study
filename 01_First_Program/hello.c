#include<stdio.h> // 전처리기 지시문(preprocessor directive)
#include<stdlib.h> // EXIT_SUCCESS 매크로가 정의된 stdlib.h 헤더 호출, 일반적으로 0으로 정의됨

int main(void)  //호스팅 환경에서 실행되는 프로그램의 기본 진입점, int는 함수의 반환형, void는 매개변수가 없음을 의미
{

  if(puts("Hello, world") == EOF) // stdout(콘솔, 윈도우 터미널)에 문자열인수와 줄바꿈 문자를 출력
  {
    return EXIT_FAILURE;  // EXIT_FAILURE : 0이 아닌 값
    // return문 이후 코드는 실행되지 않는다
  }
    char user_input[100];
    scanf("%s", user_input);
    printf(user_input);
    printf("%s", user_input);
 
    printf("%s\n","Hello,world");   // 문자열 이외의 인수를 출력 할때 사용
    return EXIT_SUCCESS;  // return문 : 프로그램 종료시 호스트환경에 정수값을 반환하거나 스크립트를 불러올수 있음.

  // return문 이후 코드 : dead code, 이후 코드는 컴파일러가 무시
}

/**
 * @brief printf() - 표준 출력으로 형식화된 문자열을 출력하는 함수
 * 
 * @details
 * printf() 함수는 표준 출력(stdout)으로 형식화된 문자열을 출력합니다.
 * 첫 번째 인자로 형식 문자열(format string)을 받고, 그 뒤에 가변 인자로
 * 형식 문자열에 지정된 값들을 받습니다.
 * 
 * @param format 형식 문자열(format string)
 *   - %d: 정수 (int) -> conversion specification
 *   - %s: 문자열 (char*)
 *   - %f: 실수 (float/double)
 *   - %c: 문자 (char)
 *   - %x: 16진수
 *   - %p: 포인터
 *   - \n: 줄바꿈
 *   - \t: 탭
 *   - \\: 백슬래시
 *   - %%: % 문자
 * 
 * @return 성공 시 출력된 문자 수, 실패 시 음수 값
 * 
 * @note
 * - 형식 문자열과 가변 인자의 개수와 타입이 일치해야 합니다.
 * - 버퍼 오버플로우를 방지하기 위해 충분한 크기의 버퍼를 사용해야 합니다.
 * 
 * @warning
 * - formatted output security vulnerability : 형식화된 출력 보안 취약점
 * - 형식 문자열에 사용자 입력을 직접 포함시키면 보안 취약점이 될 수 있습니다.
 * - printf("%s", user_input) 형식으로 사용하는 것이 안전합니다.
 * 
 * @example
 * ```c
 * // 기본 문자열 출력
 * printf("Hello, %s!\n", "World");     // 출력: Hello, World!
 * 
 * // 정수 출력
 * printf("Number: %d\n", 42);          // 출력: Number: 42
 * printf("Hex: %x\n", 255);            // 출력: Hex: ff
 * 
 * // 실수 출력
 * printf("Pi: %.2f\n", 3.14159);       // 출력: Pi: 3.14
 * printf("E: %e\n", 2.71828);          // 출력: E: 2.718280e+00
 * 
 * // 문자 출력
 * printf("First letter: %c\n", 'A');   // 출력: First letter: A
 * 
 * // 포인터 출력
 * int x = 10;
 * printf("Address: %p\n", (void*)&x);  // 출력: Address: 0x7fff5fbff8ac
 * 
 * // 여러 값 출력
 * printf("Name: %s, Age: %d\n", "John", 30);  // 출력: Name: John, Age: 30
 * 
 * // 필드 너비 지정
 * printf("|%10s|%5d|\n", "Name", 42);  // 출력: |      Name|   42|
 * 
 * // 왼쪽 정렬
 * printf("|%-10s|%5d|\n", "Name", 42); // 출력: |Name      |   42|
 * 
 * // 소수점 자릿수 지정
 * printf("%.3f\n", 3.14159);           // 출력: 3.142
 * 
 * // 0으로 채우기
 * printf("%05d\n", 42);                // 출력: 00042
 * 
 * // 형식화된 출력 보안 취약점 예시
 * char user_input[100];
 * scanf("%s", user_input);  // 사용자 입력: "%x%x%x%x"
 * 
 * // 취약한 사용법 - 사용자 입력을 형식 문자열로 직접 사용
 * printf(user_input);  // 위험! 메모리 내용이 노출될 수 있음
 * 
 * // 안전한 사용법 - 사용자 입력을 가변 인자로 전달
 * printf("%s", user_input);  // 안전함
 * ```
 */

/**
 * @brief puts() - 표준 출력으로 문자열을 출력하고 줄바꿈을 추가하는 함수
 * 
 * @details
 * puts() 함수는 표준 출력(stdout)으로 문자열을 출력하고 자동으로 줄바꿈 문자('\n')를 추가합니다.
 * 이 함수는 printf()와 달리 형식 문자열을 사용하지 않고 단순히 문자열만 출력합니다.
 * 
 * @param str 출력할 문자열 (NULL로 종료되는 문자열)
 * 
 * @return 성공 시 음수가 아닌 값, 실패 시 EOF(-1)
 * 
 * @note
 * - 문자열 끝에 자동으로 줄바꿈 문자가 추가됩니다.
 * - puts()는 printf()보다 단순하고 효율적입니다.
 * - 문자열은 NULL 문자('\0')로 종료되어야 합니다.
 * 
 * @warning
 * - str이 NULL인 경우 정의되지 않은 동작이 발생합니다.
 * - 버퍼 오버플로우를 방지하기 위해 충분한 크기의 버퍼를 사용해야 합니다.
 * 
 * @example
 * ```c
 * puts("Hello, World!");  // 출력: Hello, World! (줄바꿈 포함)
 * 
 * char str[] = "Hello";
 * puts(str);  // 출력: Hello (줄바꿈 포함)
 * ```
 */