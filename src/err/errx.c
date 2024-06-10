#include <err.h>
#include <stdarg.h>

void errx(int status, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  verrx(status, fmt, ap);
  va_end(ap);
}
