#include <stdlib.h>

int atexit(void (*func)(void)) {
  if (_atexit_count < 32)
    _atexit_funcs[_atexit_count++] = func;
  else {
    void (**tmp)(void) =
        realloc(_atexit_funcs_extra, (_atexit_count - 32 + 1) * sizeof(void *));
    if (tmp == NULL)
      return -1;
    _atexit_funcs_extra = tmp;
    _atexit_funcs_extra[_atexit_count++ - 32] = func;
  }
  return 0;
}
