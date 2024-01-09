#include <stdio.h>
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
