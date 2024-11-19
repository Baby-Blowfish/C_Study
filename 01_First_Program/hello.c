
//preprocessor directive
#include <stdio.h>		// puts(), 표준 입출력 함수
#include <stdlib.h>		// EXIT_SUCCESS 매크로, 일반 유틸리티 함수

int main(void) // int형 반환, 인수 없음
{// 프로그램의 기본 진입점

// 	if(puts("Hello World") == EOF){
// 		return EXIT_FAILURE;
// 		// 여기 코드는 실행되지 않음, 즉 return문 다음에 오는 코드는 죽은 코드임, 컴파일러에서 무시됨
// 	}	
// 	// 콘솔(화면,stdout)으로 문자열 인수를 쓰고 출력에 줄 바꿈 문자 추가 표준 라이브러리 함수
// 

	printf("%s\n", "Hello World");
	// 첫번째 인수 포맷 스트링, %s : 두번째 인수를 그대로 stdout에 출력지시하는 변환 지정자



	return EXIT_SUCCESS; // 일반적으로 0으로 정의되는 객체형 매크로 호출한 호스트 환경으로 반환
}

