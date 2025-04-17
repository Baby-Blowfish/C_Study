  #include <stdio.h>

  // [1] 함수: 2차원 배열을 decay된 포인터로 받음
  void decay2D(int arr[][3]) {
    // decay : int [][3] -> int (*)[3] : 1차원 배열 int[3]을 가리키는 포인터
    printf("[decay2D] sizeof(arr) = %lu\n", sizeof(arr));       // (int (*)[3] 포인터 이므로 -> 8
    printf("[decay2D] sizeof(arr[0]) = %lu\n", sizeof(arr[0])); // int[3] -> 첫번째 행 -> 12(4*3)
    printf("[decay2D] arr[1][2] = %d\n", arr[1][2]); // 실제 값 확인용    
  }

  // [2] 함수: 배열 포인터로 받음
  void array_ptr(int (*arr)[3]) {
      // int (*)[3]
      printf("[array_ptr] sizeof(*arr) = %lu\n", sizeof(*arr));   // int[3] -> 12(4*3)

    // 배열 포인터로 역참조해서 값 출력
    printf("[array_ptr] (*arr)[2] = %d\n", (*arr)[2]); // 첫 번째 행의 세 번째 값
  }

  // [3] 함수: 포인터 배열 받기
  void pointer_array(int *arr[3]) {
      // decay : int *[3] -> int ** : 정수 포인터를 가리키는 포인터
      printf("[pointer_array] sizeof(arr) = %lu\n", sizeof(arr)); // int** -> 8
          // 포인터 배열 dereference → arr[2]는 포인터, *arr[2]은 값
    printf("[pointer_array] *arr[2] = %d\n", *arr[2]); // arr[2]가 가리키는 값
  }

  // [4] 함수: 이중 포인터 받기
  void double_ptr(int **p) {
      // int ** : 정수 포인터를 가리키는 포인터
      printf("[double_ptr] sizeof(p) = %lu\n", sizeof(p));        // int** -> 8
          // 이중 포인터 역참조
    printf("[double_ptr] *p[2] = %d\n", *p[2]); // p[2]가 가리키는 값
  }

  int main() {
      int arr2D[2][3] = {{1,2,3}, {4,5,6}}; // int[2][3] => 2행 3열의 2차원 배열, 일반 표현식에서는 decay되어 int (*)[3]이 된다.
      // arr[i] : int[3]
      // arr[i][j] : int

      int (*p)[3] = arr2D;    // 배열 포인터    decay  : 2차원 배열 int[2][3] -> 첫번째 행의 포인터 int(*)[3] 
      int *q = arr2D[0];      // 포인터        decay  : 1차원 배열 int[3]    -> 첫번째 행의 첫 요소의 주소 int *
      int *q1 = arr2D[1];     // 포인터        decay  : 1차원 배열 int[3]    -> 두번째 행의 첫 요소의 주소 int *
      int x = arr2D[1][2];    // int형 변수    decay  : int형 변수 int       -> 두번째 행의 세번째 요소 int
      int *ptrs[3];         // 포인터 배열 (3개의 int* 슬롯)
      int **pp;             // 이중 포인터

      // 포인터 배열 초기화
      for (int i = 0; i < 3; i++) {
          ptrs[i] = &arr2D[0][i];
      }
      pp = ptrs;

      // 배열 크기 확인
      printf("[main] sizeof(arr2D) = %lu\n", sizeof(arr2D));              // decay 발생 x -> int[2][3] -> 24(4*2*3)
      printf("[main] sizeof(arr2D[0]) = %lu\n", sizeof(arr2D[0]));        // decay 발생 x -> int[3] -> 12(4*3)
      printf("[main] sizeof(arr2D[0][0]) = %lu\n", sizeof(arr2D[0][0]));  // decay 발생 x -> int -> 4
      printf("[main] sizeof(&arr2D) = %lu\n", sizeof(&arr2D));            // decay 발생 x -> int (*)[2][3] -> 8 (배열 전체 주소)
      // 함수 호출
      decay2D(arr2D);         // 2차원 배열 int [2][3]   -> decay 이후 : int (*)[3]
      array_ptr(&arr2D[1]);   // 배열 포인터 int (*)[3] 넘겨 주려면 -> arr2D[1] 주소를 넘겨줘야함,   
      // pointer_array(); 인수는 포인터 배열이므로 -> int *[3] 포인터 배열의 주소를 넘겨줘야함
      // 그런데 arr2D는 배열 포인터는 되지만 포인터 배열이 될 수 없음
      // 그래서 포인터 배열 ptrs를 만든거임
      pointer_array(ptrs);    // 포인터 배열 int *[3]    -> decay 이후 : int **
      double_ptr(pp);         // 이중 포인터 int **

      return 0;
  }