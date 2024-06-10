#ifndef _INTTYPES_H_
#define _INTTYPES_H_

#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS
extern intmax_t strtoimax(const char *, char **, int);
extern uintmax_t strtoumax(const char *, char **, int);
__END_DECLS

#endif
