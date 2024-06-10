#include <stdio.h>
#include <unistd.h>

int fgetc(FILE *stream) {
  unsigned char c;
  if (fread(&c, 1, 1, stream) == 1)
    return c;
  return EOF;
}
