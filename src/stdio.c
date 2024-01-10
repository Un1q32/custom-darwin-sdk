#include <stdarg.h>
#include <stdbool.h>
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

char *__tostr(const char *format, int charssofar, va_list ap) {
    char *ret;
    char size = 0, formatlen = 1;
    bool done = false;
    while (!done) {
        switch (format[formatlen - 1]) {
            case 's':
                /* TODO: if size > 0 then use unicode */
                ret = va_arg(ap, char *);
                done = true;
                break;
            case 'c':
                /* TODO: unicode */
                ret = malloc(2);
                ret[0] = va_arg(ap, int);
                ret[1] = '\0';
                done = true;
                break;
            case 'd':
            case 'i':
                if (size == 0)
                    ret = itoa((int)va_arg(ap, int));
                else if (size == 1)
                    ret = itoa((long)va_arg(ap, long));
                else if (size == 2)
                    ret = itoa(va_arg(ap, long long));
                else if (size == -1)
                    ret = itoa((short)va_arg(ap, int));
                else if (size == -2)
                    ret = itoa((char)va_arg(ap, int));
                done = true;
                break;
            case 'u':
            case 'o':
            case 'x':
            case 'X':
                if (size == 0)
                    ret = utoa((int)va_arg(ap, unsigned int));
                else if (size == 1)
                    ret = utoa((long)va_arg(ap, unsigned long));
                else if (size == 2)
                    ret = utoa(va_arg(ap, unsigned long long));
                else if (size == -1)
                    ret = utoa((short)va_arg(ap, unsigned int));
                else if (size == -2)
                    ret = utoa((char)va_arg(ap, unsigned int));
                done = true;
                break;
            case 'n':
                if (size == 0)
                    *(int *)va_arg(ap, int *) = charssofar;
                else if (size == 1)
                    *(long *)va_arg(ap, long *) = charssofar;
                else if (size == 2)
                    *(long long *)va_arg(ap, long long *) = charssofar;
                else if (size == -1)
                    *(short *)va_arg(ap, short *) = charssofar;
                else if (size == -2)
                    *(char *)va_arg(ap, char *) = charssofar;
                done = true;
                break;
            case 'l':
                formatlen++;
                if (size < 1)
                    size = 1;
                else if (size < 2)
                    size = 2;
                break;
            case 'j':
            case 'q':
                formatlen++;
                size = 2;
                break;
            case 'h':
                formatlen++;
                if (size == 0)
                    size = -1;
                else if (size < 0)
                    size = -2;
                break;
            case 't':
            case 'z':
                formatlen++;
                if (sizeof(size_t) == sizeof(long)) {
                    if (size < 2)
                        size = 2;
                } else if (size < 0)
                    size = 0;
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
