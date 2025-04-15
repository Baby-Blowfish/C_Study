# 흐름 제어
> 각 문(statement)이 평가되는 순서를 알아봄

> 수행할 작업을 정의하는 식 문과 복합 문을 알아봄

> 실행할 코드 블록을 결정하는 선택과 반복, 점프 세 종류의 문을 알아봄

## 식 문
- `expression statement` : 세미콜론으로 끝나는 선택적 문이다. 작업의 기본 단위
```c
a = 6;
c = a + b;
; // null 문, 아무것도 하지 않음
++count;
```
- 각 식의 평가하고 나면 식의 값은 버려진다.

## 복합 문
> `compound statement`
- 복합문 또는 블록 : `{}`로 묶인 0개 이상의 문 목록 
- 블록 안의 각 문은 제어 문으로 수정하지 않는 한 순차적으로 실행
- 마지막 문을 평가한 후 중괄호 다음 문을 실행
- 복합문 안에 복합문을 만들어 중첩될 수 있다.
- 문이 하나도 없이 블록을 만들 수 있다.

## 선택 문
> `selection statement` : 제어식의 값에 따라 조건부로 하위문을 실행할수 있다.
> `controlling expression` :제어식은 조건에 따라 실행할 문을 결정한다.

  ### if 문
  ```c
  if(expreesion)
    substatement
  ```
  - expression이 0이 아니라면 substatement 실행
  ```c
  bool safediv(int dividend, int divisor, int *quotient)
  {
    if(!quotient) return false;

    if((divisor == 0) || (dividend == INT_MIN) && (divisor == -1))
      return false;
    *quotient = dividend / divisor;

    return true;
  }
  ```c
  if(expression)
    substatement1
  else
    substatement2
  ```
  - expression이 0이 아니면 substatement 1 실행, 0이면 substatement2 실행
  

  ### switch 문
  - 제어식에 정수 형식이 있어야함
  - 제어식의 값과 각 case 레이블의 상수 식의 값에 따라 점프
  - 다음 제어 흐름 문을 만날때까지 순차 실행
  ```c
  switch(expression)
  case constant1:
    substatement1;
    break;
  case constant2:
    substatement2;
    break;
  ...
  default:
    substatementN;
  ```
  - 제어식에 대해 정수 확장 수행
  - case의 상수 식은 제어식의 확장된 형식으로 변환됨
  - 일치하는 상수식이 없고 default레이블이 없을 경우 어떤 부분도 실행되지 않음

## 반복문
> `loop statement` : 종료 기준에 따라 하위문을 0번 이상 실행

  ### while문
  ```c
  while (expression)
    substatement;
  ```
  - `expression`이 **참(0이 아님)**인 동안 **반복** 실행
  - 조건이 **처음부터 거짓이면 한 번도 실행되지 않음** : 진입조건이 충족되는 동안만 실행
  ```c
  int i = 0;
  while (i < 5) {
      printf("%d ", i);
      i++;
  }
  ```
  → 출력: `0 1 2 3 4`


  ### do-while문
  ```c
  do
      substatement;
  while (expression);
  ```
  - `substatement`를 **무조건 1번 실행**한 후, `expression`이 참이면 계속 반복
  - 제어식의 평가가 루프 본문 실행 후에 이뤄짐
  - 사용자 입력, 메뉴 선택 등에서 자주 사용
  ```c
  int num;
  do {
      printf("숫자를 입력하세요: ");
      scanf("%d", &num);
  } while (num != 0);
  ```

  ### for 문
  ```c
  for (초기식; 조건식; 증감식)
      substatement;
  ```
  - 반복 횟수를 정해 놓고 반복할 때 사용
  - 반복 변수의 초기화, 조건 검사, 증가/감소를 한 줄에 씀
  - 조건식은 루프 시작전 평가, 증감식은 루프 본문 실행 후 평가
  ```c
  for (int i = 0; i < 5; i++) {
      printf("%d ", i);
  }
  ```
  → 출력: `0 1 2 3 4`

## 점프 문
> 제어를 같은 함수의 다른 부분으로 무조건 넘김, 최하위 수준 제어 흐름 문으로 어셈블리 언어 코드와 거의 일치
- 레이블(lable) : 같은 함수 안에서만 유효, `:` 으로 정의
```c
label_name:
    substatement;
```
  ### goto문
  ```c  
  goto label;
  ... // 무시됨
  label:
    substatement;
  ```
  - 프로그램의 흐름을 지정된 **label**로 **무조건 점프**함
  - 반복문, 조건문과 무관하게 **흐름을 끊고 이동**
  - 파일, 소켓, 메모리 등 여러 자원을 순차적으로 다룰 때 -> `goto 체인`을 사용
  ```c
  int do_someting(void)
  {
    FILE *file1, *file2;
    object_t *obj;

    int ret_val = 0;  // 처음에 성공한 반환값 가정
    
    file1 = fopen("a_file","w");
    if(file1 == NULL)
    {
      ret_val = -1;
      goto FAIL_FILE1;
    }

    file2 = fopen("b_file","w");
    if(file2 == NULL)
    {
      ret_val = -1;
      goto FAIL_FILE2;
    }

    obj = malloc(sizeof(object_t));
    if(obj == NULL)
    {
      ret_val = -1;
      goto FAIL_OBJ;
    }

    // 할당된 자워 동작
    
    free(obj);

  FAIL_OBJ:
    fclose(file2);
  FAIL_FILE2:
    fclose(file1);
  FAIL_FILE1:
    return ret_val;
  }
  ```
  ### continue
  - 루프 본문의 끝으로 점프, 현재 반복에 대한 루프 본문안에 남아 있는 문의 실행을 건너뛸 수 있음
  - 각 루프의 goto END_LOOP_BODY와 같음
  ```c
  while (expression) {
      if (조건)
          continue;
      substatement;  // continue 아래는 실행되지 않음
  }
  
  
  while (expression) {
    // ~~
    continue;
    // ~~
  END_LOOP_BODY: ;
  }
  
  
  do{
    // ~~
    continue;
    // ~~
  END_LOOP_BODY: ;
  }while (expression) 
  
  
  for( ){
    // ~~
    continue;
    // ~~
  END_LOOP_BODY: ;
  }
  ```

  ### break
  - switch나 반복만의 실행을 종료
  ```c
  while (expression) {
      if (조건)
          break;
      substatement;
  }
  ```
  - **가장 가까운 반복문 또는 switch문을 즉시 탈출**
  - 반복 조건과 무관하게 **즉시 종료**

  ### return
  - 현재 함수의 실행을 종료하고 제어를 호출자에게 반환
  ```c
  return;
  ```

  or

  ```c
  return expression;
  ```
  - `void` 함수는 `return;`만,  
    `int` 함수는 `return 정수값;`처럼 사용
  - 함수 중간에서도 사용 가능


  ### 예시 비교

  ```c
  #include <stdio.h>

  int main() {
      for (int i = 0; i < 10; i++) {

          if (i == 3)
              continue;  // i == 3이면 아래 코드 생략하고 다음 반복

          if (i == 6)
              break;     // i == 6이면 반복문 전체 종료

          if (i == 8)
              goto end;  // i == 8이면 지정된 위치로 점프

          printf("%d ", i);
      }

  end:
      printf("\nDone\n");
      return 0;  // 함수 종료
  }
  ```
