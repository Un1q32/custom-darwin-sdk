#ifndef _ERR_H_
#define _ERR_H_

#include <stdarg.h>
#include <sys/cdefs.h>

__BEGIN_DECLS
extern void err(int, const char *, ...);
extern void verr(int, const char *, va_list ap);
extern void errx(int, const char *, ...);
extern void verrx(int, const char *, va_list ap);
extern void warn(const char *, ...);
extern void vwarn(const char *, va_list ap);
extern void warnx(const char *, ...);
extern void vwarnx(const char *, va_list ap);
__END_DECLS

#endif
