#include <stdlib.h>
#include <string.h>

char *_itoa(long long num) {
  if (num < 0) {
    char *ret = _utoa(-num);
    char *ret2 = malloc(strlen(ret) + 2);
    if (ret2) {
      ret2[0] = '-';
      strcpy(ret2 + 1, ret);
    }
    free(ret);
    return ret2;
  } else
    return _utoa(num);
}
