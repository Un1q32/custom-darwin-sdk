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

int vsnprintf(char *str, size_t size, const char *format, va_list ap) {
  size_t i = 0, j = 0;
  while (format[i]) {
    if (format[i] == '%') {
      size_t argstrlen;
      const char *fmt = format + i + 1, *fmt2 = format + i;
      bool done = false, altform = false;
      unsigned int fill = 0, percision = 6, flags = 0;
      char fillchar = ' ';
      while (!done) {
        if (*fmt == '#')
          altform = true;
        else if (*fmt == '.') {
          if (fmt[1] == '*') {
            percision = va_arg(ap, int);
            fmt++;
          } else {
            const char *strstart = fmt + 1, *strend = fmt + 1;
            while (isdigit(*strend))
              strend++;
            char percisionstr[strend - strstart + 1];
            memcpy(percisionstr, strstart, strend - strstart);
            percisionstr[strend - strstart] = '\0';
            percision = atoi(percisionstr);
            fmt = strend - 1;
          }
        } else if (*fmt == '0')
          fillchar = '0';
        else if (isdigit(*fmt)) {
          const char *strstart = fmt, *strend = fmt + 1;
          while (isdigit(*strend))
            strend++;
          char fillstr[strend - strstart + 1];
          memcpy(fillstr, strstart, strend - strstart);
          fillstr[strend - strstart] = '\0';
          fill = atoi(fillstr);
          fmt = strend - 1;
        } else if (*fmt == '*')
          fill = va_arg(ap, int);
        else {
          fmt--;
          done = true;
        }
        fmt++;
      }
      done = false;
      while (!done) {
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
        default:
          fmt--;
          done = true;
          break;
        }
      }
      char *tmp = NULL;
      size_t k = 0;
      switch (*fmt) {
      case '%':
        if (j < size)
          str[j] = '%';
        j++;
        break;
      case 'S':
        flags |= 1 << 0;
        /* fall through */
      case 's':
        tmp = va_arg(ap, char *);
        if (tmp == NULL)
          tmp = "(null)";
        argstrlen = strlen(tmp);
        while (fill > argstrlen) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        break;
      case 'C':
        flags |= 1 << 0;
        /* fall through */
      case 'c':
        if (fill > 1) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        if (j < size)
          str[j] = va_arg(ap, int);
        j++;
        break;
      case 'd':
      case 'i':
        if (flags & 1 << 4)
          tmp = itoa(va_arg(ap, intmax_t));
        else if (flags & 1 << 8)
          tmp = itoa(va_arg(ap, quad_t));
        else if (flags & 1 << 1)
          tmp = itoa(va_arg(ap, long long));
        else if (flags & 1 << 5 || flags & 1 << 6)
          tmp = itoa(va_arg(ap, ptrdiff_t));
        else if (flags & 1 << 0)
          tmp = itoa(va_arg(ap, long));
        else if (flags & 1 << 2)
          tmp = itoa((short)va_arg(ap, int));
        else if (flags & 1 << 3)
          tmp = itoa((char)va_arg(ap, int));
        else
          tmp = itoa(va_arg(ap, int));
        argstrlen = strlen(tmp);
        while (fill > argstrlen) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        free(tmp);
        break;
      case 'u':
        if (flags & 1 << 4)
          tmp = utoa(va_arg(ap, uintmax_t));
        else if (flags & 1 << 8)
          tmp = utoa(va_arg(ap, u_quad_t));
        else if (flags & 1 << 1)
          tmp = utoa(va_arg(ap, unsigned long long));
        else if (flags & 1 << 5 || flags & 1 << 6)
          tmp = utoa(va_arg(ap, size_t));
        else if (flags & 1 << 0)
          tmp = utoa(va_arg(ap, unsigned long));
        else if (flags & 1 << 2)
          tmp = utoa((unsigned short)va_arg(ap, unsigned int));
        else if (flags & 1 << 3)
          tmp = utoa((unsigned char)va_arg(ap, unsigned int));
        else
          tmp = utoa(va_arg(ap, unsigned int));
        argstrlen = strlen(tmp);
        while (fill > argstrlen) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        free(tmp);
        break;
      case 'F':
      case 'f':
        if (flags & 1 << 7)
          tmp = ftoa(va_arg(ap, long double), percision);
        else
          tmp = ftoa(va_arg(ap, double), percision);
        argstrlen = strlen(tmp);
        while (fill > argstrlen) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        free(tmp);
        break;
      case 'p':
        altform = true;
        flags |= 1 << 0;
        /* fall through */
      case 'x':
        if (flags & 1 << 4)
          tmp = utox(va_arg(ap, uintmax_t));
        else if (flags & 1 << 8)
          tmp = utox(va_arg(ap, u_quad_t));
        else if (flags & 1 << 1)
          tmp = utox(va_arg(ap, unsigned long long));
        else if (flags & 1 << 5 || flags & 1 << 6)
          tmp = utox(va_arg(ap, size_t));
        else if (flags & 1 << 0)
          tmp = utox(va_arg(ap, unsigned long));
        else if (flags & 1 << 2)
          tmp = utox((unsigned short)va_arg(ap, unsigned int));
        else if (flags & 1 << 3)
          tmp = utox((unsigned char)va_arg(ap, unsigned int));
        else
          tmp = utox(va_arg(ap, unsigned int));
        argstrlen = strlen(tmp);
        if (altform) {
          if (j < size)
            str[j] = '0';
          j++;
          if (j < size)
            str[j] = 'x';
          j++;
        }
        while (fill > argstrlen) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        free(tmp);
        break;
      case 'X':
        if (flags & 1 << 4)
          tmp = utoX(va_arg(ap, uintmax_t));
        else if (flags & 1 << 8)
          tmp = utoX(va_arg(ap, u_quad_t));
        else if (flags & 1 << 1)
          tmp = utoX(va_arg(ap, unsigned long long));
        else if (flags & 1 << 5 || flags & 1 << 6)
          tmp = utoX(va_arg(ap, size_t));
        else if (flags & 1 << 0)
          tmp = utoX(va_arg(ap, unsigned long));
        else if (flags & 1 << 2)
          tmp = utoX((unsigned short)va_arg(ap, unsigned int));
        else if (flags & 1 << 3)
          tmp = utoX((unsigned char)va_arg(ap, unsigned int));
        else
          tmp = utoX(va_arg(ap, unsigned int));
        argstrlen = strlen(tmp);
        if (altform) {
          if (j < size)
            str[j] = '0';
          j++;
          if (j < size)
            str[j] = 'X';
          j++;
        }
        while (fill > argstrlen) {
          if (j < size)
            str[j] = fillchar;
          j++;
          fill--;
        }
        while (tmp[k]) {
          if (j < size)
            str[j] = tmp[k];
          j++;
          k++;
        }
        free(tmp);
        break;
      case 'n':
        if (flags & 1 << 4)
          *va_arg(ap, uintmax_t *) = j;
        else if (flags & 1 << 8)
          *va_arg(ap, u_quad_t *) = j;
        else if (flags & 1 << 1)
          *va_arg(ap, unsigned long long *) = j;
        else if (flags & 1 << 5 || flags & 1 << 6)
          *va_arg(ap, size_t *) = j;
        else if (flags & 1 << 0)
          *va_arg(ap, unsigned long *) = j;
        else if (flags & 1 << 2)
          *va_arg(ap, unsigned short *) = j;
        else if (flags & 1 << 3)
          *va_arg(ap, unsigned char *) = j;
        else
          *va_arg(ap, unsigned int *) = j;
        break;
      default:
        fmt--;
        break;
      }
      i += fmt - fmt2 + 1;
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

char *fgets(char *str, int size, FILE *stream) {
  int i = 0;
  while (i < size - 1) {
    int c = fgetc(stream);
    if (c == EOF) {
      if (i == 0)
        return NULL;
      break;
    }
    str[i] = c;
    if (c == '\n')
      break;
    i++;
  }
  str[i + 1] = '\0';
  return str;
}

char *gets(char *str) {
  int i = 0;
  while (1) {
    int c = getchar();
    if (c == EOF) {
      if (i == 0)
        return NULL;
      break;
    }
    str[i] = c;
    if (c == '\n')
      break;
    i++;
  }
  str[i + 1] = '\0';
  return str;
}
