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
  size_t size = sizeof(sigrecord);

  if((fp = fopen("sig.dat", "rb")) == NULL) {
    fputs("Can't open file.\n", stderr);
    return EXIT_FAILURE;
  }

  if(fseek(fp, 0, SEEK_SET) != 0) {
    fputs("Can't seek file.\n", stderr);
    status = EXIT_FAILURE;
    goto close_files;
  }

  if(fread(&sigrec, size, 1, fp) != 1) {
    fputs("Can't read sigrec.\n", stderr);
    status = EXIT_FAILURE;
    goto close_files;
  }

  printf("sigrec: %d %s %s\n", sigrec.signum, sigrec.signame, sigrec.sigdesc);


close_files:
  if (fclose(fp) == EOF) {
    fputs("Can't close file.\n", stderr);
    status = EXIT_FAILURE;
  }

  return status;
}