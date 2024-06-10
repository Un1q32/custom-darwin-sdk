#include <stdio.h>

int fputc(int ch, FILE *stream) {
  fwrite(&ch, 1, 1, stream);
  return ch;
}
