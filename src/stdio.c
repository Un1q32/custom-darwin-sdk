#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

FILE *fdopen(int fd, const char *mode) {
  (void)mode;
  FILE *ret = malloc(sizeof(FILE));
  if (ret == NULL)
    return NULL;
  ret->_file = fd;
  ret->_flags = 0;
  return ret;
}

FILE *fopen(const char *filename, const char *mode) {
  mode_t flags = 0;
  if (strcmp(mode, "r") == 0)
    flags = O_RDONLY;
  else if (strcmp(mode, "w") == 0)
    flags = O_WRONLY | O_CREAT | O_TRUNC;
  else if (strcmp(mode, "a") == 0)
    flags = O_WRONLY | O_CREAT | O_APPEND;
  else if (strcmp(mode, "r+") == 0)
    flags = O_RDWR;
  else if (strcmp(mode, "w+") == 0)
    flags = O_RDWR | O_CREAT | O_TRUNC;
  else if (strcmp(mode, "a+") == 0)
    flags = O_RDWR | O_CREAT | O_APPEND;
  else
    return NULL;
  int fd = open(filename, flags, 0644);
  if (fd == -1)
    return NULL;
  return fdopen(fd, mode);
}

int fclose(FILE *stream) {
  int ret = 0;
  if (stream->_file >= 3)
    ret = close(stream->_file);
  if (stream != __stdinp && stream != __stdoutp && stream != __stderrp)
    free(stream);
  return ret;
}

int fseek(FILE *stream, long offset, int whence) {
  return lseek(stream->_file, offset, whence);
}

void rewind(FILE *stream) { fseek(stream, 0, SEEK_SET); }

long ftell(FILE *stream) { return lseek(stream->_file, 0, SEEK_CUR); }

int ferror(FILE *stream) { return stream->_flags & __SERR; }

int fflush(FILE *stream) {
  (void)stream;
  return 0;
}

int fcloseall(void) { return 0; }

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  return read(stream->_file, ptr, size * nmemb) / size;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
  return write(stream->_file, ptr, size * nmemb) / size;
}

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

char *__tostr(const char *format, int charssofar, va_list ap, int *formatlen,
              int *vaargs) {
  if (format == NULL || vaargs == NULL || formatlen == NULL)
    return NULL;
  *vaargs = 0;
  char *ret = NULL, type = '\0';
  const char *format2 = format;
  unsigned int flags = 0, percision = 6, fill = 0;
  bool done = false, altform = false, zerofill = false;
  while (!done) {
    if (*format == '#') {
      altform = true;
    } else if (*format == '.') {
      if (*(format + 1) == '*') {
        percision = va_arg(ap, int);
        *vaargs += 1;
        format++;
      } else {
        const char *tmp = format + 1;
        while (isdigit(*tmp))
          tmp++;
        char percisionstr[tmp - format];
        memcpy(percisionstr, format + 1, tmp - format);
        percisionstr[tmp - format - 1] = '\0';
        percision = atoi(percisionstr);
        format = tmp - 1;
      }
    } else if (*format == '0') {
      zerofill = true;
    } else if (isdigit(*format)) {
      const char *tmp = format;
      while (isdigit(*tmp))
        tmp++;
      char fillstr[tmp - format];
      memcpy(fillstr, format, tmp - format);
      fillstr[tmp - format] = '\0';
      fill = atoi(fillstr);
      format = tmp - 1;
    } else if (*format == '*') {
      fill = va_arg(ap, int);
      *vaargs += 1;
    } else {
      format--;
      done = true;
    }
    format++;
  }
  done = false;
  while (!done) {
    switch (*format++) {
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
    default:
      format--;
      done = true;
      break;
    }
  }
  switch (*format) {
  case '%':
    ret = strdup("%");
    if (ret == NULL)
      return NULL;
    break;
  case 'S':
    flags |= 1 << 0;
    /* fall through */
  case 's':
    ret = strdup(va_arg(ap, char *));
    *vaargs += 1;
    if (ret == NULL)
      ret = strdup("(null)");
    if (ret == NULL)
      return NULL;
    break;
  case 'C':
    flags |= 1 << 0;
    /* fall through */
  case 'c':
    ret = malloc(2);
    if (ret == NULL)
      return NULL;
    ret[0] = (unsigned char)va_arg(ap, int);
    ret[1] = '\0';
    *vaargs += 1;
    break;
  case 'd':
  case 'i':
    if (flags & 1 << 4)
      ret = itoa(va_arg(ap, intmax_t));
    else if (flags & 1 << 8)
      ret = itoa(va_arg(ap, quad_t));
    else if (flags & 1 << 1)
      ret = itoa(va_arg(ap, long long));
    else if (flags & 1 << 5 || flags & 1 << 6)
      ret = itoa(va_arg(ap, ptrdiff_t));
    else if (flags & 1 << 0)
      ret = itoa(va_arg(ap, long));
    else if (flags & 1 << 2)
      ret = itoa((short)va_arg(ap, int));
    else if (flags & 1 << 3)
      ret = itoa((char)va_arg(ap, int));
    else
      ret = itoa(va_arg(ap, int));
    *vaargs += 1;
    if (ret == NULL)
      return NULL;
    break;
  case 'u':
    if (flags & 1 << 4)
      ret = utoa(va_arg(ap, uintmax_t));
    else if (flags & 1 << 8)
      ret = utoa(va_arg(ap, u_quad_t));
    else if (flags & 1 << 1)
      ret = utoa(va_arg(ap, unsigned long long));
    else if (flags & 1 << 5 || flags & 1 << 6)
      ret = utoa(va_arg(ap, size_t));
    else if (flags & 1 << 0)
      ret = utoa(va_arg(ap, unsigned long));
    else if (flags & 1 << 2)
      ret = utoa((unsigned short)va_arg(ap, unsigned int));
    else if (flags & 1 << 3)
      ret = utoa((unsigned char)va_arg(ap, unsigned int));
    else
      ret = utoa(va_arg(ap, unsigned int));
    *vaargs += 1;
    if (ret == NULL)
      return NULL;
    break;
  case 'f':
  case 'F':
    type = 'f';
    if (flags & 1 << 7)
      ret = ftoa(va_arg(ap, long double), percision);
    else
      ret = ftoa(va_arg(ap, double), percision);
    *vaargs += 1;
    if (ret == NULL)
      return NULL;
    break;
  case 'p':
    altform = true;
    flags = 1 << 0;
    /* fall through */
  case 'x':
    type = 'x';
    if (flags & 1 << 4)
      ret = utox(va_arg(ap, uintmax_t));
    else if (flags & 1 << 8)
      ret = utox(va_arg(ap, u_quad_t));
    else if (flags & 1 << 1)
      ret = utox(va_arg(ap, unsigned long long));
    else if (flags & 1 << 5 || flags & 1 << 6)
      ret = utox(va_arg(ap, size_t));
    else if (flags & 1 << 0)
      ret = utox(va_arg(ap, unsigned long));
    else if (flags & 1 << 2)
      ret = utox((unsigned short)va_arg(ap, unsigned int));
    else if (flags & 1 << 3)
      ret = utox((unsigned char)va_arg(ap, unsigned int));
    else
      ret = utox(va_arg(ap, unsigned int));
    *vaargs += 1;
    if (ret == NULL)
      return NULL;
    break;
  case 'X':
    type = 'X';
    if (flags & 1 << 4)
      ret = utoX(va_arg(ap, uintmax_t));
    else if (flags & 1 << 8)
      ret = utoX(va_arg(ap, u_quad_t));
    else if (flags & 1 << 1)
      ret = utoX(va_arg(ap, unsigned long long));
    else if (flags & 1 << 5 || flags & 1 << 6)
      ret = utoX(va_arg(ap, size_t));
    else if (flags & 1 << 0)
      ret = utoX(va_arg(ap, unsigned long));
    else if (flags & 1 << 2)
      ret = utoX((unsigned short)va_arg(ap, unsigned int));
    else if (flags & 1 << 3)
      ret = utoX((unsigned char)va_arg(ap, unsigned int));
    else
      ret = utoX(va_arg(ap, unsigned int));
    *vaargs += 1;
    if (ret == NULL)
      return NULL;
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
    *vaargs += 1;
    ret = malloc(1);
    if (ret == NULL)
      return NULL;
    ret[0] = '\0';
    break;
  default:
    format--;
    ret = malloc(1);
    if (ret == NULL)
      return NULL;
    ret[0] = '\0';
    break;
  }
  *formatlen = format - format2 + 2;
  unsigned int retlen = strlen(ret);
  if (altform && (type == 'x' || type == 'X'))
    retlen += 2;
  if (fill > retlen) {
    char *ret2 = malloc(fill + 1);
    if (ret2 == NULL) {
      free(ret);
      return NULL;
    }
    memset(ret2, zerofill ? '0' : ' ', fill - retlen);
    strcpy(ret2 + fill - retlen, ret);
    free(ret);
    ret = ret2;
  }
  if (altform) {
    retlen = strlen(ret);
    if (type == 'x' || type == 'X') {
      char *ret2 = malloc(retlen + 3);
      if (ret2 == NULL) {
        free(ret);
        return NULL;
      }
      ret2[0] = '0';
      ret2[1] = type;
      strcpy(ret2 + 2, ret);
      free(ret);
      ret = ret2;
    }
  }
  return ret;
}

int vsnprintf(char *str, size_t size, const char *format, va_list ap) {
  size_t i = 0, j = 0;
  while (format[i]) {
    if (format[i] == '%') {
      int formatlen, vaargs;
      char *tmp = __tostr(format + i + 1, j, ap, &formatlen, &vaargs);
#ifdef __arm__
      while (vaargs--)
        va_arg(ap, int);
#endif
      if (tmp != NULL) {
        size_t k = 0;
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        i += formatlen;
        free(tmp);
      } else {
        if (j < size)
          str[j] = format[i];
        j++;
        i++;
      }
    } else {
      if (j < size)
        str[j] = format[i];
      j++;
      i++;
    }
  }
  if (j < size)
    str[j] = '\0';
  else if (size > 0)
    str[size - 1] = '\0';
  return j;
}

int vsprintf(char *str, const char *format, va_list ap) {
  return vsnprintf(str, SIZE_MAX, format, ap);
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
  char nothing[1];
  char buf[vsnprintf(nothing, 0, format, ap2) + 1];
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

void perror(const char *str) {
  const char *errstr = strerror(errno);
  size_t len = 0;
  if (str != NULL)
    len = strlen(str) + strlen(errstr) + 4;
  else
    len = strlen(errstr) + 2;
  char buf[len];
  buf[0] = '\0';
  if (str != NULL) {
    strcpy(buf, str);
    strcat(buf, ": ");
  }
  strcat(buf, errstr);
  strcat(buf, "\n");
  write(STDERR_FILENO, buf, len);
}

int fgetc(FILE *stream) {
  unsigned char c;
  if (read(stream->_file, &c, 1) == 1)
    return c;
  return EOF;
}

int getc(FILE *stream) { return fgetc(stream); }

int getchar(void) { return getc(stdin); }
