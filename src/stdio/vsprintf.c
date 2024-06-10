#include <stdint.h>
#include <stdio.h>

int vsprintf(char *str, const char *format, va_list ap) {
  return vsnprintf(str, SIZE_MAX, format, ap);
}
