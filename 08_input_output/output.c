
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct sigrecord {
    int signum;
    char signame[20];
    char sigdesc[100];
} sigrecord;

int main(void)
{
  int status = EXIT_SUCCESS;
  FILE *fp;

  sigrecord sigrec;

  if((fp = fopen("sig.dat", "wb")) == NULL) {
    fputs("Can't open file.\n", stderr);
    return EXIT_FAILURE;
  }

  sigrecord sigrec30 = {30, "SIGKILL", "Kill"};
  sigrecord sigrec31 = { .signum = 31, .signame = "SIGPIPE", .sigdesc = "Broken pipe"};

  size_t size = sizeof(sigrecord);

  if (fwrite(&sigrec30, size, 1, fp) != 1) {
    fputs("Can't write sigrec30.\n", stderr);
    status = EXIT_FAILURE;
    goto close_files;
  }

  if (fwrite(&sigrec31, size, 1, fp) != 1) {
    fputs("Can't write sigrec31.\n", stderr);
    status = EXIT_FAILURE;
  }

close_files:
  if (fclose(fp) == EOF) {
    fputs("Can't close file.\n", stderr);
    status = EXIT_FAILURE;
  }

  return status;
}