#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

extern void exit(int);
extern void *malloc(size_t);
extern void free(void *);
extern void *realloc(void *, size_t);
extern long strtol(const char *, char **, int);
extern long long strtoll(const char *, char **, int);
extern unsigned long strtoul(const char *, char **, int);
extern unsigned long long strtoull(const char *, char **, int);
extern int atoi(const char *);
extern char *itoa(long long);
extern char *utoa(unsigned long long);
extern char *ftoa(long double, int);
extern char *getenv(const char *);
extern int setenv(const char *, const char *, int);
extern int system(const char *);

#endif
