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
extern int atoi(const char *);

#endif
