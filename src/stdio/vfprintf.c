#include <stdio.h>

int vfprintf(FILE *stream, const char *format, va_list ap) {
  va_list ap2;
  va_copy(ap2, ap);
  char nothing[1];
  char buf[vsnprintf(nothing, 0, format, ap2) + 1];
  va_end(ap2);
  int ret = vsprintf(buf, format, ap);
  fwrite(buf, 1, ret, stream);
  return ret;
}
