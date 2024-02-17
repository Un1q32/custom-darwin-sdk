#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
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

char *__tostr(const char *format, int charssofar, va_list ap, int *formatlen) {
  if (format == NULL)
    return NULL;
  char *ret = NULL;
  unsigned int flags = 0, percision = 6, zerofill = 0, len = 0;
  *formatlen = 1;
  bool done = false, altform = false;
  while (!done) {
    switch (format[*formatlen - 1]) {
    case '%':
      ret = strdup("%");
      if (ret == NULL)
        return NULL;
      done = true;
      break;
    case 'S':
      flags |= 1 << 0;
    case 's':
      ret = strdup(va_arg(ap, char *));
      if (ret == NULL)
        return NULL;
      done = true;
      break;
    case 'C':
      flags |= 1 << 0;
    case 'c':
      ret = malloc(2);
      if (ret == NULL)
        return NULL;
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
      if (ret == NULL)
        return NULL;
      len = strlen(ret);
      if (len < zerofill) {
        char *ret2 = malloc(zerofill + 1);
        if (ret2 == NULL) {
          free(ret);
          return NULL;
        }
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
      if (ret == NULL)
        return NULL;
      len = strlen(ret);
      if (len < zerofill) {
        char *ret2 = malloc(zerofill + 1);
        if (ret2 == NULL) {
          free(ret);
          return NULL;
        }
        memset(ret2, '0', zerofill - len);
        memcpy(ret2 + zerofill - len, ret, len);
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
      if (ret == NULL)
        return NULL;
      done = true;
      break;
    case 'x':
      if (flags & 1 << 4)
        ret = strdup(utox(va_arg(ap, uintmax_t)));
      else if (flags & 1 << 8)
        ret = strdup(utox(va_arg(ap, u_quad_t)));
      else if (flags & 1 << 1)
        ret = strdup(utox(va_arg(ap, unsigned long long)));
      else if (flags & 1 << 5 || flags & 1 << 6)
        ret = strdup(utox(va_arg(ap, size_t)));
      else if (flags & 1 << 0)
        ret = strdup(utox(va_arg(ap, unsigned long)));
      else if (flags & 1 << 2)
        ret = strdup(utox((unsigned short)va_arg(ap, unsigned int)));
      else if (flags & 1 << 3)
        ret = strdup(utox((unsigned char)va_arg(ap, unsigned int)));
      else
        ret = strdup(utox(va_arg(ap, unsigned int)));
      if (ret == NULL)
        return NULL;
      len = strlen(ret);
      if (len < zerofill) {
        char *ret2 = malloc(zerofill + 1);
        if (ret2 == NULL) {
          free(ret);
          return NULL;
        }
        memset(ret2, '0', zerofill - len);
        memcpy(ret2 + zerofill - len, ret, len);
        ret2[zerofill] = '\0';
        free(ret);
        ret = ret2;
      }
      if (altform) {
        char *ret2 = malloc(len + 3);
        if (ret2 == NULL) {
          free(ret);
          return NULL;
        }
        ret2[0] = '0';
        ret2[1] = 'x';
        memcpy(ret2 + 2, ret, len);
        ret2[len + 2] = '\0';
        free(ret);
        ret = ret2;
      }
      done = true;
      break;
    case 'X':
      if (flags & 1 << 4)
        ret = strdup(utoX(va_arg(ap, uintmax_t)));
      else if (flags & 1 << 8)
        ret = strdup(utoX(va_arg(ap, u_quad_t)));
      else if (flags & 1 << 1)
        ret = strdup(utoX(va_arg(ap, unsigned long long)));
      else if (flags & 1 << 5 || flags & 1 << 6)
        ret = strdup(utoX(va_arg(ap, size_t)));
      else if (flags & 1 << 0)
        ret = strdup(utoX(va_arg(ap, unsigned long)));
      else if (flags & 1 << 2)
        ret = strdup(utoX((unsigned short)va_arg(ap, unsigned int)));
      else if (flags & 1 << 3)
        ret = strdup(utoX((unsigned char)va_arg(ap, unsigned int)));
      else
        ret = strdup(utoX(va_arg(ap, unsigned int)));
      if (ret == NULL)
        return NULL;
      len = strlen(ret);
      if (len < zerofill) {
        char *ret2 = malloc(zerofill + 1);
        if (ret2 == NULL) {
          free(ret);
          return NULL;
        }
        memset(ret2, '0', zerofill - len);
        memcpy(ret2 + zerofill - len, ret, len);
        ret2[zerofill] = '\0';
        free(ret);
        ret = ret2;
      }
      if (altform) {
        char *ret2 = malloc(len + 3);
        if (ret2 == NULL) {
          free(ret);
          return NULL;
        }
        ret2[0] = '0';
        ret2[1] = 'X';
        memcpy(ret2 + 2, ret, len);
        ret2[len + 2] = '\0';
        free(ret);
        ret = ret2;
      }
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
      if (ret == NULL)
        return NULL;
      ret[0] = '\0';
      done = true;
      break;
    case 'l':
      *formatlen += 1;
      if (flags & 1 << 0)
        flags |= 1 << 1;
      else
        flags |= 1 << 0;
      break;
    case 'h':
      *formatlen += 1;
      if (flags & 1 << 2)
        flags |= 1 << 3;
      else
        flags |= 1 << 2;
      break;
    case 'j':
      *formatlen += 1;
      flags |= 1 << 4;
      break;
    case 't':
      *formatlen += 1;
      flags |= 1 << 5;
      break;
    case 'z':
      *formatlen += 1;
      flags |= 1 << 6;
      break;
    case 'L':
      *formatlen += 1;
      flags |= 1 << 7;
      break;
    case 'q':
      *formatlen += 1;
      flags |= 1 << 8;
      break;
    case '.':
      *formatlen += 1;
      while (isdigit(format[*formatlen - 1]))
        *formatlen += 1;
      char *percisionstr = malloc(*formatlen - 1);
      if (percisionstr == NULL)
        return NULL;
      memcpy(percisionstr, format + 1, *formatlen - 2);
      percisionstr[*formatlen - 1] = '\0';
      percision = atoi(percisionstr);
      free(percisionstr);
      break;
    case '0':
      *formatlen += 1;
      while (isdigit(format[*formatlen - 1]))
        *formatlen += 1;
      char *zerofillstr = malloc(*formatlen - 1);
      if (zerofillstr == NULL)
        return NULL;
      memcpy(zerofillstr, format + 1, *formatlen - 2);
      zerofillstr[*formatlen - 1] = '\0';
      zerofill = atoi(zerofillstr);
      free(zerofillstr);
      break;
    case '#':
      *formatlen += 1;
      altform = true;
      break;
    default:
      *formatlen -= 1;
      ret = malloc(1);
      if (ret == NULL)
        return NULL;
      ret[0] = '\0';
      done = true;
      break;
    }
  }
  return ret;
}

int vsprintf(char *str, const char *format, va_list ap) {
  int i = 0, j = 0;
  while (format[i]) {
    if (format[i] == '%') {
      int formatlen;
      char *tmp = __tostr(format + i + 1, j, ap, &formatlen);
      va_arg(ap, void *);
      if (tmp != NULL) {
        if (str != NULL)
          strcpy(str + j, tmp);
        j += strlen(tmp);
        i += formatlen + 1;
        free(tmp);
      } else {
        if (str != NULL)
          strcpy(str + j, "(null)");
        j += 6;
        i += formatlen + 1;
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

void perror(const char *str) {
  char *errstr = strerror(errno);
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
  char c;
  if (read(stream->_file, &c, 1) == 1)
    return c;
  return EOF;
}
