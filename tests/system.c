#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <command>\n", argv[0]);
    return 1;
  }
  int ret = system(argv[1]);
  printf("Return value: %d\n", ret);
  return 0;
}
