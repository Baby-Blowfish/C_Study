  #include <assert.h>
  #include <stdio.h>

  int main() {
      int x = -1;
      assert(x > 0 && "x는 양수여야 합니다");
      printf("x = %d\n", x);
      return 0;
  }