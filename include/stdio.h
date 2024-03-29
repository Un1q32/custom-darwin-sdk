#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdarg.h>
#include <stddef.h>
#include <sys/types.h>

typedef struct {
  short _file;
  short _flags;
} FILE;

extern FILE *__stdinp;
extern FILE *__stdoutp;
extern FILE *__stderrp;

#define stdin __stdinp
#define stdout __stdoutp
#define stderr __stderrp

#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SRD 0x0004
#define __SWR 0x0008
#define __SRW 0x0010
#define __SERR 0x0040

#define BUFSIZ 1024
#define EOF (-1)

#define getc(fp) getc(fp)

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
extern int fclose(FILE *);
extern int fseek(FILE *, long, int);
extern void rewind(FILE *);
extern long ftell(FILE *);
extern int ferror(FILE *);
extern int fflush(FILE *);
extern int fcloseall(void);
extern int fgetc(FILE *);
extern int getc(FILE *);
extern int getchar(void);
extern char *fgets(char *, int, FILE *);
extern char *gets(char *);
extern size_t fread(void *, size_t, size_t, FILE *);
extern size_t fwrite(const void *, size_t, size_t, FILE *);

#endif
