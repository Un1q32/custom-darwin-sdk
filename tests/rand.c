#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <seed>\n", argv[0]);
    return 1;
  }

  srand(atoi(argv[1]));
  int i;
  for (i = 0; i < 10; i++)
    printf("%d\n", rand());
  return 0;
}
