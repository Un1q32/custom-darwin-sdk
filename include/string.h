#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS
extern char *strcat(char *, const char *);
extern char *strncat(char *, const char *, size_t);
extern char *strcpy(char *, const char *);
extern char *stpcpy(char *, const char *);
extern char *strdup(const char *);
extern char *strndup(const char *, size_t);
extern size_t strlen(const char *);
extern size_t strnlen(const char *, size_t);
extern char *strchr(const char *, int);
extern char *strrchr(const char *, int);
extern int strcmp(const char *, const char *);
extern int strncmp(const char *, const char *, size_t);
extern char *strncpy(char *, const char *, size_t);
extern char *strstr(const char *, const char *);
extern char *strtok(char *, const char *);
extern char *strtok_r(char *, const char *, char **);
extern size_t strspn(const char *, const char *);
extern size_t strcspn(const char *, const char *);
extern char *strpbrk(const char *, const char *);
extern void *memcpy(void *, const void *, size_t);
extern void *memset(void *, int, size_t);
extern errno_t memset_s(void *, size_t, int, size_t);
extern void memset_pattern4(void *, const void *, size_t);
extern void memset_pattern8(void *, const void *, size_t);
extern void memset_pattern16(void *, const void *, size_t);
extern int memcmp(const void *, const void *, size_t);
extern void *memmove(void *, const void *, size_t);
extern void *memchr(const void *, int, size_t);
extern void explicit_bzero(void *, size_t);
extern char *strerror(int);
extern size_t strlcpy(char *, const char *, size_t);
extern size_t strlcat(char *, const char *, size_t);
extern char *strsep(char **, const char *);
__END_DECLS

#endif
