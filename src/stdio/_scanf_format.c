#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

unsigned int _scanf_format(const char *format, ssize_t *width,
                           size_t *formatlen) {
  const char *fmt = format;
  unsigned int flags = 0;
  bool done = false;
  while (!done) {
    if (*fmt >= '0' && *fmt <= '9') {
      char widthstr[strlen(fmt) + 1];
      size_t i = 0;
      while (*fmt >= '0' && *fmt <= '9')
        widthstr[i++] = *fmt++;
      widthstr[i] = '\0';
      *width = strtoul(widthstr, NULL, 10);
    }
    switch (*fmt++) {
    case 'l':
      if (flags & 1 << 0)
        flags |= 1 << 1;
      else
        flags |= 1 << 0;
      break;
    case 'h':
      if (flags & 1 << 2)
        flags |= 1 << 3;
      else
        flags |= 1 << 2;
      break;
    case 'j':
      flags |= 1 << 4;
      break;
    case 't':
      flags |= 1 << 5;
      break;
    case 'z':
      flags |= 1 << 6;
      break;
    case 'L':
      flags |= 1 << 7;
      break;
    case 'q':
      flags |= 1 << 8;
      break;
    case '*':
      flags |= 1 << 9;
      break;
    default:
      fmt--;
      done = true;
      break;
    }
  }
  *formatlen = fmt - format;
  return flags;
}
