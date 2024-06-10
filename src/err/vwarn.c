#include <stdarg.h>
#include <stdio.h>

extern char *__progname;

void vwarn(const char *fmt, va_list ap) {
  fprintf(stderr, "%s: ", __progname);
  if (fmt) {
    vfprintf(stderr, fmt, ap);
    fputs(": ", stderr);
  }
  perror(0);
}
