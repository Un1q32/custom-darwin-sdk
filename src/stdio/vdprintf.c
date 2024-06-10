#include <stdio.h>
#include <unistd.h>

int vdprintf(int fd, const char *format, va_list ap) {
  va_list ap2;
  va_copy(ap2, ap);
  char nothing[1];
  char buf[vsnprintf(nothing, 0, format, ap2) + 1];
  va_end(ap2);
  int ret = vsprintf(buf, format, ap);
  write(fd, buf, ret);
  return ret;
}
