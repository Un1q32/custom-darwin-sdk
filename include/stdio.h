#ifndef _STDIO_H
#define _STDIO_H 1

#include <stddef.h>
#include <sys/types.h>

struct __sbuf {
    unsigned char *_base;
    int _size;
};

struct __sFILEX;

typedef struct __sFILE {
    unsigned char *_p;
    int _r;
    int _w;
    short _flags;
    short _file;
    struct __sbuf _bf;
    int _lbfsize;
    void *_cookie;
    int (*_close)(void *);
    int (*_read) (void *, char *, int);
    fpos_t (*_seek) (void *, fpos_t, int);
    int (*_write)(void *, const char *, int);
    struct __sbuf _ub;
    struct __sFILEX *_extra;
    int _ur;
    unsigned char _ubuf[3];
    unsigned char _nbuf[1];
    struct __sbuf _lb;
    int _blksize;
    fpos_t _offset;
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
