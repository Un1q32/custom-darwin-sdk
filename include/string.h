#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>

extern size_t strlen(const char *);
extern char *strcat(char *, const char *);
extern char *strcpy(char *, const char *);
extern char *stpcpy(char *, const char *);
extern char *strdup(const char *);
extern void *memcpy(void *, const void *, size_t);
extern void *memset(void *, int, size_t);

#endif
