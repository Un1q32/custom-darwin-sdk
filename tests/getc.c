#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    perror("fopen");
    return 1;
  }

  int c;
  while ((c = getc(file)) != EOF)
    printf("%d\n", c);
  return 0;
}
