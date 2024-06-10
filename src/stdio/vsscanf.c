#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vsscanf(const char *str, const char *format, va_list ap) {
  int ret = 0;
  size_t i = 0, j = 0;
  while (format[i]) {
    if (format[i] == '%') {
      const char *fmt = format + i + 1;
      ssize_t width = -1;
      size_t formatlen;
      unsigned int flags = _scanf_format(fmt, &width, &formatlen);
      fmt += formatlen;
      switch (*fmt) {
      case '%':
        if (str[j] != '%')
          return ret;
        j++;
        break;
      case 'd': {
        size_t numlen = 0;
        if (str[j] == '-') {
          j++;
          numlen++;
        }
        while (str[j] >= '0' && str[j] <= '9') {
          j++;
          numlen++;
        }
        if (numlen == 0)
          return ret;
        char numstr[numlen + 1];
        memcpy(numstr, str + j - numlen, numlen);
        numstr[numlen] = '\0';
        if (!(flags & 1 << 9)) {
          void *ptr = va_arg(ap, void *);
          if (flags & 1 << 4)
            *(intmax_t *)ptr = strtoimax(numstr, NULL, 10);
          else if (flags & 1 << 8)
            *(quad_t *)ptr = strtoq(numstr, NULL, 10);
          else if (flags & 1 << 1)
            *(long long *)ptr = strtoll(numstr, NULL, 10);
          else if (flags & 1 << 5 || flags & 1 << 6)
            *(ptrdiff_t *)ptr = strtol(numstr, NULL, 10);
          else if (flags & 1 << 0)
            *(long *)ptr = strtol(numstr, NULL, 10);
          else if (flags & 1 << 2)
            *(short *)ptr = strtol(numstr, NULL, 10);
          else if (flags & 1 << 3)
            *(char *)ptr = strtol(numstr, NULL, 10);
          else
            *(int *)ptr = strtol(numstr, NULL, 10);
          ret++;
        }
      } break;
      case 'u': {
        size_t numlen = 0;
        while (str[j] >= '0' && str[j] <= '9') {
          j++;
          numlen++;
        }
        if (numlen == 0)
          return ret;
        char numstr[numlen + 1];
        memcpy(numstr, str + j - numlen, numlen);
        numstr[numlen] = '\0';
        if (!(flags & 1 << 9)) {
          void *ptr = va_arg(ap, void *);
          if (flags & 1 << 4)
            *(uintmax_t *)ptr = strtoumax(numstr, NULL, 10);
          else if (flags & 1 << 8)
            *(u_quad_t *)ptr = strtouq(numstr, NULL, 10);
          else if (flags & 1 << 1)
            *(unsigned long long *)ptr = strtoull(numstr, NULL, 10);
          else if (flags & 1 << 5 || flags & 1 << 6)
            *(size_t *)ptr = strtoul(numstr, NULL, 10);
          else if (flags & 1 << 0)
            *(unsigned long *)ptr = strtoul(numstr, NULL, 10);
          else if (flags & 1 << 2)
            *(unsigned short *)ptr = strtoul(numstr, NULL, 10);
          else if (flags & 1 << 3)
            *(unsigned char *)ptr = strtoul(numstr, NULL, 10);
          else
            *(unsigned int *)ptr = strtoul(numstr, NULL, 10);
          ret++;
        }
      } break;
      case 'S':
        flags |= 1 << 0;
        /* fall through */
      case 's': {
        char *dst = NULL;
        if (!(flags & 1 << 9))
          dst = va_arg(ap, char *);
        size_t strlength = 0;
        while (str[j] && str[j] != ' ' && str[j] != '\t' && str[j] != '\n' &&
               str[j] != '\r')
          if (width == -1)
            strlength++;
          else if (width--)
            strlength++;
          else
            break;
        if (strlength) {
          if (dst) {
            memcpy(dst, str + j, strlength);
            dst[strlength] = '\0';
            ret++;
          }
          j += strlength;
        }
      } break;
      case 'C':
        flags |= 1 << 0;
        /* fall through */
      case 'c':
        if (width == -1)
          width = 1;
        if (!str[j])
          return ret;
        if (!(flags & 1 << 9)) {
          memcpy(va_arg(ap, char *), str + j, width);
          ret++;
        }
        j += width;
        break;
      default:
        if (str[j] != *fmt)
          return ret;
        j++;
        break;
      }
      i = fmt - format + 1;
    } else {
      if (str[j] != format[i])
        return ret;
      i++;
      j++;
    }
  }
  return ret;
}
