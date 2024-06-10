#ifndef _STDIO_H_
#define _STDIO_H_

#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#define L_ctermid PATH_MAX
#define L_tmpnam PATH_MAX

#define FILENAME_MAX PATH_MAX

typedef struct {
  short fd;
  short flags;
  char *buf;
  unsigned short bufcount;
  unsigned short listpos;
} FILE;

#define stdin stdin
#define stdout stdout
#define stderr stderr

#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SRD 0x0004
#define __SWR 0x0008
#define __SRW 0x0010
#define __SEOF 0x0020
#define __SERR 0x0040

#define BUFSIZ 1024
#define EOF (-1)

#define P_tmpdir "/var/tmp"

#define getc(fp) getc(fp)

__BEGIN_DECLS
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

extern int fputc(int, FILE *);
extern int putc(int, FILE *);
extern int putchar(int);
extern int puts(const char *);
extern int fputs(const char *, FILE *);
extern int printf(const char *, ...);
extern int fprintf(FILE *, const char *, ...);
extern int dprintf(int, const char *, ...);
extern int sprintf(char *, const char *, ...);
extern int snprintf(char *, size_t, const char *, ...);
extern int vprintf(const char *, va_list);
extern int vfprintf(FILE *, const char *, va_list);
extern int vdprintf(int, const char *, va_list);
extern int vsprintf(char *, const char *, va_list);
extern int vsnprintf(char *, size_t, const char *, va_list);
extern void perror(const char *);
extern FILE *fopen(const char *, const char *);
extern FILE *fdopen(int, const char *);
extern FILE *freopen(const char *, const char *, FILE *);
extern int fclose(FILE *);
extern void fcloseall(void);
extern int fseek(FILE *, long, int);
extern void rewind(FILE *);
extern long ftell(FILE *);
extern int ferror(FILE *);
extern int fflush(FILE *);
extern int fpurge(FILE *);
extern int feof(FILE *);
extern void clearerr(FILE *);
extern int fgetc(FILE *);
extern int getc(FILE *);
extern int getchar(void);
extern char *fgets(char *, int, FILE *);
extern char *gets(char *);
extern size_t fread(void *, size_t, size_t, FILE *);
extern size_t fwrite(const void *, size_t, size_t, FILE *);
extern char *ctermid(char *);
extern int fileno(FILE *);
extern char *tmpnam(char *);
extern int sscanf(const char *, const char *, ...);
extern int vsscanf(const char *, const char *, va_list);

#ifdef _UNIQ_LIBC_PRIVATE_API
extern FILE *_open_stream_list[65536];
extern int _fopen_mode_parse(const char *);
extern FILE *_fdopen(int, mode_t);
extern unsigned int _scanf_format(const char *, ssize_t *, size_t *);
extern void _random_alnum(char *, size_t);
#endif
__END_DECLS

#endif
