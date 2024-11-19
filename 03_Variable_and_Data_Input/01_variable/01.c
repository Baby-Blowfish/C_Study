// 자료형의 범위 : -2^(비트수-1) ~ 2^(비트수 -1)-1
//         char : -128 ~ 127
/*    정수형 자료형
      char : 1byte            %c, %d
      short : 2byte           %d
      int : 4byte             %d
      long : 4byte            %ld
      long long : 8byte       %lld
      unsigned char : 1byte            %u
      unsigned short : 2byte           %u
      unsigned int : 4byte             %u
      unsigned long : 4byte            %lu
      unsigned long long : 8byte       %llu
*/
// unsigned 자료형을 쓸 땐 항상 양수만 저장하고 %u로 출력한다!

/*    실수형 자료형
      float :4byte          유효숫자 : 7            %f
      double : 8byte        유효숫자 : 15           %lf
      long double : 8byte   유효숫자 : 15이상       %Lf

*/

/*    문자열
      char 배열명[문자열길이 +1] = 문자열;
      컴파일러가 문자열의 끝에 널문자('\0')을 자동으로 추가
*/

/*    const 키워드
      const 자료형 변수명 = 값;
      const는 변수를 초기화 시에만 사용가능하다.
      const를 사용한 변수는 초기화된 값을 바꿀 수 없다.
*/

/*    예약어(reserved word, key word)와 식별자(identifier)

*/

#include<stdio.h>
#include<string.h>

int main(void)
{
  char fruit[20] = "strawberry";
  strcpy(fruit,"banana");
  printf("%s",fruit);

  return 0;
}