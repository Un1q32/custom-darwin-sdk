#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

FILE __stdio[3] = {
    {
        ._file = STDIN_FILENO,
        ._flags = __SRD,
    },
    {
        ._file = STDOUT_FILENO,
        ._flags = __SWR,
    },
    {
        ._file = STDERR_FILENO,
        ._flags = __SWR | __SNBF,
    },
};

FILE *__stdinp = &__stdio[0];
FILE *__stdoutp = &__stdio[1];
FILE *__stderrp = &__stdio[2];

int puts(const char *str) {
  size_t len = strlen(str);
  char str2[len + 1];
  memcpy(str2, str, len);
  str2[len] = '\n';
  return write(STDOUT_FILENO, str2, len + 1);
}

int fputs(const char *str, FILE *stream) {
  return write(stream->_file, str, strlen(str));
}

int putchar(int ch) { return putc(ch, stdout); }

int putc(int ch, FILE *stream) { return fputc(ch, stream); }

int fputc(int ch, FILE *stream) {
  write(stream->_file, (unsigned char *)&ch, 1);
  return ch;
}

char *__tostr(const char *format, int charssofar, va_list ap) {
  if (format == NULL)
    return NULL;
  char *ret = NULL;
  int flags = 0, formatlen = 1, percision = 6, zerofill = 0;
  bool done = false;
  while (!done) {
    switch (format[formatlen - 1]) {
    case '%':
      ret = strdup("%");
      done = true;
      break;
    case 's':
    case 'S':
      ret = strdup(va_arg(ap, char *));
      done = true;
      break;
    case 'c':
    case 'C':
      ret = malloc(2);
      ret[0] = (unsigned char)va_arg(ap, int);
      ret[1] = '\0';
      done = true;
      break;
    case 'd':
    case 'i':
      if (flags & 1 << 4)
        ret = strdup(itoa(va_arg(ap, intmax_t)));
      else if (flags & 1 << 8)
        ret = strdup(itoa(va_arg(ap, quad_t)));
      else if (flags & 1 << 1)
        ret = strdup(itoa(va_arg(ap, long long)));
      else if (flags & 1 << 5 || flags & 1 << 6)
        ret = strdup(itoa(va_arg(ap, ptrdiff_t)));
      else if (flags & 1 << 0)
        ret = strdup(itoa(va_arg(ap, long)));
      else if (flags & 1 << 2)
        ret = strdup(itoa((short)va_arg(ap, int)));
      else if (flags & 1 << 3)
        ret = strdup(itoa((char)va_arg(ap, int)));
      else
        ret = strdup(itoa(va_arg(ap, int)));
      int len = strlen(ret);
      if (len < zerofill) {
        char *ret2 = malloc(zerofill + 1);
        memset(ret2, '0', zerofill - len);
        memcpy(ret2 + zerofill - len, ret, len);
        ret2[zerofill] = '\0';
        free(ret);
        ret = ret2;
      }
      done = true;
      break;
    case 'u':
      if (flags & 1 << 4)
        ret = strdup(utoa(va_arg(ap, uintmax_t)));
      else if (flags & 1 << 8)
        ret = strdup(utoa(va_arg(ap, u_quad_t)));
      else if (flags & 1 << 1)
        ret = strdup(utoa(va_arg(ap, unsigned long long)));
      else if (flags & 1 << 5 || flags & 1 << 6)
        ret = strdup(utoa(va_arg(ap, size_t)));
      else if (flags & 1 << 0)
        ret = strdup(utoa(va_arg(ap, unsigned long)));
      else if (flags & 1 << 2)
        ret = strdup(utoa((unsigned short)va_arg(ap, unsigned int)));
      else if (flags & 1 << 3)
        ret = strdup(utoa((unsigned char)va_arg(ap, unsigned int)));
      else
        ret = strdup(utoa(va_arg(ap, unsigned int)));
      int len2 = strlen(ret);
      if (len2 < zerofill) {
        char *ret2 = malloc(zerofill + 1);
        memset(ret2, '0', zerofill - len2);
        memcpy(ret2 + zerofill - len2, ret, len2);
        ret2[zerofill] = '\0';
        free(ret);
        ret = ret2;
      }
      done = true;
      break;
    case 'f':
    case 'F':
      if (flags & 1 << 7)
        ret = strdup(ftoa(va_arg(ap, long double), percision));
      else
        ret = strdup(ftoa(va_arg(ap, double), percision));
      done = true;
      break;
    case 'n':
      if (flags & 1 << 4)
        *(va_arg(ap, intmax_t *)) = charssofar;
      else if (flags & 1 << 8)
        *(va_arg(ap, quad_t *)) = charssofar;
      else if (flags & 1 << 1)
        *(va_arg(ap, long long *)) = charssofar;
      else if (flags & 1 << 5 || flags & 1 << 6)
        *(va_arg(ap, ptrdiff_t *)) = charssofar;
      else if (flags & 1 << 0)
        *(va_arg(ap, long *)) = charssofar;
      else if (flags & 1 << 2)
        *(va_arg(ap, short *)) = charssofar;
      else if (flags & 1 << 3)
        *(va_arg(ap, char *)) = charssofar;
      else
        *(va_arg(ap, int *)) = charssofar;
      ret = malloc(1);
      ret[0] = '\0';
      done = true;
      break;
    case 'l':
      formatlen++;
      if (flags & 1 << 0)
        flags |= 1 << 1;
      else
        flags |= 1 << 0;
      break;
    case 'h':
      formatlen++;
      if (flags & 1 << 2)
        flags |= 1 << 3;
      else
        flags |= 1 << 2;
      break;
    case 'j':
      formatlen++;
      flags |= 1 << 4;
      break;
    case 't':
      formatlen++;
      flags |= 1 << 5;
      break;
    case 'z':
      formatlen++;
      flags |= 1 << 6;
      break;
    case 'L':
      formatlen++;
      flags |= 1 << 7;
      break;
    case 'q':
      formatlen++;
      flags |= 1 << 8;
      break;
    case '.':
      formatlen++;
      while (isdigit(format[formatlen - 1]))
        formatlen++;
      char *percisionstr = malloc(formatlen - 1);
      memcpy(percisionstr, format + 1, formatlen - 2);
      percisionstr[formatlen - 1] = '\0';
      percision = atoi(percisionstr);
      free(percisionstr);
      break;
    case '0':
      formatlen++;
      while (isdigit(format[formatlen - 1]))
        formatlen++;
      char *zerofillstr = malloc(formatlen - 1);
      memcpy(zerofillstr, format + 1, formatlen - 2);
      zerofillstr[formatlen - 1] = '\0';
      zerofill = atoi(zerofillstr);
      free(zerofillstr);
      break;
    default:
      formatlen--;
      ret = malloc(1);
      ret[0] = '\0';
      done = true;
      break;
    }
  }
  if (ret != NULL) {
    size_t len = strlen(ret);
    char *ret2 = realloc(ret, len + 2);
    if (ret2 != NULL)
      ret = ret2;
    else {
      free(ret);
      return NULL;
    }
    ret[len + 1] = formatlen;
  }
  return ret;
}

int vsprintf(char *str, const char *format, va_list ap) {
  int i = 0, j = 0;
  while (format[i]) {
    if (format[i] == '%') {
      char *tmp = __tostr(format + i + 1, j, ap);
      va_arg(ap, void *);
      if (tmp) {
        if (str != NULL)
          strcpy(str + j, tmp);
        j += strlen(tmp);
        i += tmp[strlen(tmp) + 1] + 1;
        free(tmp);
      } else {
        if (str != NULL)
          str[j] = format[i];
        j++;
        i++;
      }
    } else {
      if (str != NULL)
        str[j] = format[i];
      j++;
      i++;
    }
  }
  if (str != NULL)
    str[j] = '\0';
  return j;
}

int vsnprintf(char *str, size_t size, const char *format, va_list ap) {
  int ret = vsprintf(str, format, ap);
  if (ret >= (int)size && str != NULL)
    str[size - 1] = '\0';
  return ret;
}

int snprintf(char *str, size_t size, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int ret = vsnprintf(str, size, format, ap);
  va_end(ap);
  return ret;
}

int sprintf(char *str, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int ret = vsprintf(str, format, ap);
  va_end(ap);
  return ret;
}

int vdprintf(int fd, const char *format, va_list ap) {
  va_list ap2;
  va_copy(ap2, ap);
  char buf[vsprintf(NULL, format, ap2) + 1];
  va_end(ap2);
  int ret = vsprintf(buf, format, ap);
  write(fd, buf, ret);
  return ret;
}

int dprintf(int fd, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int ret = vdprintf(fd, format, ap);
  va_end(ap);
  return ret;
}

int vfprintf(FILE *stream, const char *format, va_list ap) {
  return vdprintf(stream->_file, format, ap);
}

int fprintf(FILE *stream, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int ret = vfprintf(stream, format, ap);
  va_end(ap);
  return ret;
}

int vprintf(const char *format, va_list ap) {
  return vdprintf(STDOUT_FILENO, format, ap);
}

int printf(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int ret = vprintf(format, ap);
  va_end(ap);
  return ret;
}
