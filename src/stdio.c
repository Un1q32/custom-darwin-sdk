#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

int puts(const char *s) {
    size_t len = strlen(s);
    char str[len + 1];
    memcpy(str, s, len);
    str[len] = '\n';
    return write(STDOUT_FILENO, str, len + 1);
}

int fputs(const char *s, FILE *stream) {
    return write(stream->_file, s, strlen(s));
}

int putchar(int c) {
    return putc(c, stdout);
}

int putc(int c, FILE *stream) {
    return fputc(c, stream);
}

int fputc(int c, FILE *stream) {
    char ch = c;
    write(stream->_file, &ch, 1);
    return c;
}

char *__tostr(const char *format, va_list ap) {
    char *ret;
    switch (format[0]) {
        case 'd':
            ret = itoa(va_arg(ap, int));
            break;
        case 's':
            ret = va_arg(ap, char *);
            break;
        case 'c':
            ret = malloc(2);
            ret[0] = va_arg(ap, int);
            ret[1] = '\0';
            break;
        default:
            ret = NULL;
            break;
    }
    return ret;
}

int vsprintf(char *str, const char *format, va_list ap) {
    int i = 0, j = 0;
    while (format[i]) {
        if (format[i] == '%') {
            char *tmp = __tostr(format + i + 1, ap);
            if (tmp) {
                if (str != NULL)
                    strcpy(str + j, tmp);
                j += strlen(tmp);
                i += 2;
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
    char buf[vsnprintf(NULL, 0, format, ap) + 1];
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
