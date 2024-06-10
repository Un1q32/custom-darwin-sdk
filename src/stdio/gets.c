#include <stdio.h>

char *gets(char *str) {
  int i = 0;
  while (1) {
    int c = getchar();
    if (c == EOF) {
      if (i == 0)
        return NULL;
      break;
    }
    str[i] = c;
    if (c == '\n')
      break;
    i++;
  }
  str[i + 1] = '\0';
  return str;
}
