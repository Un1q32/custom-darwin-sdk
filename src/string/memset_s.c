#include <errno.h>
#include <stdint.h>
#include <string.h>

errno_t memset_s(void *s, rsize_t smax, int c, rsize_t n) {
  errno_t err = 0;
  if (s == NULL)
    return EINVAL;
  if (smax > RSIZE_MAX)
    return E2BIG;
  if (n > RSIZE_MAX) {
    err = E2BIG;
    n = smax;
  }
  if (n > smax) {
    err = EOVERFLOW;
    n = smax;
  }
  memset(s, c, n);
  return err;
}
