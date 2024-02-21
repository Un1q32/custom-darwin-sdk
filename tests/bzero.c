#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int main() {
  char str[5];
  str[0] = 'p';
  str[1] = 'a';
  str[2] = 's';
  str[3] = 's';
  str[4] = '\0';
  bzero(str, 4);
  if (str[0] == 0 && str[1] == 0 && str[2] == 0 && str[3] == 0) {
    puts("bzero works");
  } else {
    puts("bzero does not work");
  }
  return 0;
}
