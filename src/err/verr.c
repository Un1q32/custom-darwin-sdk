#include <err.h>
#include <stdarg.h>
#include <stdlib.h>

void verr(int status, const char *fmt, va_list ap) {
  vwarn(fmt, ap);
  exit(status);
}
