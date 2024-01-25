#include <stdio.h>
#include <stdlib.h>

int main() {
  char *str = malloc(4);
  str[0] = 'a';
  str[1] = 'b';
  str[2] = 'c';
  str[3] = '\0';
  puts(str);
  free(str);
  return 0;
}
