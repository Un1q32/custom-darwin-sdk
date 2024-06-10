#include <err.h>
#include <stdarg.h>

void err(int status, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  verr(status, fmt, ap);
  va_end(ap);
}
