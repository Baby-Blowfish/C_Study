#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int print_error(int errnum)
{
  const char* msg = strerror(errnum);
  if (msg != NULL) {
    fprintf(stderr, "Error: %s\n", msg);
    return 0;
  } else {
    fprintf(stderr, "Unknown error\n");
    return ENOMEM;
  }
}


int main(void)
{
  printf("Testing memory allocation error:\n");
  print_error(ENOMEM);
  
  printf("\nTesting permission denied error:\n");
  print_error(EACCES);
  
  printf("\nTesting file not found error:\n");
  print_error(ENOENT);
  
  return 1;
}

    