#ifndef _CRT_EXTERNS_H_
#define _CRT_EXTERNS_H_

#include <sys/cdefs.h>

__BEGIN_DECLS
extern char ***_NSGetArgv(void);
extern int *_NSGetArgc(void);
extern char ***_NSGetEnviron(void);
extern char **_NSGetProgname(void);
__END_DECLS

#endif
