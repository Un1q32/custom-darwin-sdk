#ifndef _STDIO_H
#define _STDIO_H 1

#include <stddef.h>
#include <sys/types.h>

typedef struct {
    int _file;
    int _flags;
} FILE;

extern FILE *__stdinp;
extern FILE *__stdoutp;
extern FILE *__stderrp;

#define stdin  __stdinp
#define stdout __stdoutp
#define stderr __stderrp

extern int fputc(int c, FILE *stream);
extern int putc(int c, FILE *stream);
extern int putchar(int c);
extern int puts(const char *s);

#endif
