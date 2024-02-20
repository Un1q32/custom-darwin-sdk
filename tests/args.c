#include <stdio.h>

int main(int argc, const char *argv[]) {
  printf("argc: %d\n", argc);
  int i;
  for (i = 0; i < argc; i++)
    puts(argv[i]);
  return 0;
}
