#include <stdarg.h>
#include <stdio.h>

extern char *__progname;

void vwarnx(const char *fmt, va_list ap) {
  fprintf(stderr, "%s: ", __progname);
  if (fmt)
    vfprintf(stderr, fmt, ap);
  putc('\n', stderr);
}
