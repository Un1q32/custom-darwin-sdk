#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <alloca.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define RAND_MAX 0x7FFFFFFF

__BEGIN_DECLS
extern void exit(int);
extern void _Exit(int);
extern long strtol(const char *, char **, int);
extern long long strtoll(const char *, char **, int);
extern quad_t strtoq(const char *, char **, int);
extern unsigned long strtoul(const char *, char **, int);
extern unsigned long long strtoull(const char *, char **, int);
extern u_quad_t strtouq(const char *, char **, int);
extern int atoi(const char *);
extern long atol(const char *);
extern long long atoll(const char *);
extern char *_itoa(long long);
extern char *_utoa(unsigned long long);
extern char *_ftoa(long double, int);
extern char *_utox(unsigned long long);
extern char *_utoX(unsigned long long);
extern char *getenv(const char *);
extern int setenv(const char *, const char *, int);
extern int putenv(char *);
extern int unsetenv(const char *);
extern int clearenv(void);
extern int system(const char *);
extern void srand(unsigned int);
extern int rand(void);
extern int atexit(void (*)(void));
extern long double strtold(const char *, char **);
extern double strtod(const char *, char **);
extern float strtof(const char *, char **);
extern int abs(int);
extern void abort(void);
extern uint32_t arc4random(void);
extern void arc4random_buf(void *, size_t);

#ifdef _UNIQ_LIBC_PRIVATE_API
#include <stdbool.h>

extern int _rand(unsigned int);
extern bool _environ_allocated;
extern void _environ_alloc(void);
extern int _findenv(const char *);
extern int _putenv(char *, int);
extern unsigned int _random_seed;
extern void (*_atexit_funcs[32])(void);
extern void (**_atexit_funcs_extra)(void);
extern int _atexit_count;
#endif
__END_DECLS

#endif
