#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }
  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    perror("fopen");
    return 1;
  }
  int c;
  while ((c = fgetc(file)) != EOF) {
    if (putchar(c) < 0) {
      perror("putchar");
      return 1;
    }
  }
  if (ferror(file)) {
    perror("fgetc");
    return 1;
  }
  if (fclose(file) != 0) {
    perror("fclose");
    return 1;
  }
  return 0;
}
