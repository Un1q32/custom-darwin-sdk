#include <errno.h>

long _syscallret2 = 0;

long _syscall_error(long err, long ret2) {
  (void)ret2;
  errno = err;
  return -1;
}

long _syscall_success(long ret, long ret2) {
  _syscallret2 = ret2;
  return ret;
}
