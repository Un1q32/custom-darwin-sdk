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
  puts(itoa(*str));
  bzero(str, 4);
  puts(itoa(*str));
  return 0;
}
