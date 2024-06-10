#include <stdio.h>
#include <unistd.h>

void (*_atexit_funcs[32])(void);
void (**_atexit_funcs_extra)(void);
int _atexit_count = 0;

void exit(int status) {
  while (_atexit_count > 32)
    _atexit_funcs_extra[--_atexit_count - 32]();
  while (_atexit_count > 0)
    _atexit_funcs[--_atexit_count]();
  fcloseall();
  /* TODO: unlink all files created with tmpfile() */
  _exit(status);
  while (1)
    ;
}
