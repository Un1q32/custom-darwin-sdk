#include <err.h>
#include <stdarg.h>
#include <stdlib.h>

void verrx(int status, const char *fmt, va_list ap) {
  vwarnx(fmt, ap);
  exit(status);
}
