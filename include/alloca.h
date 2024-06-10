#ifndef _ALLOCA_H_
#define _ALLOCA_H_

#include <stddef.h>
#include <sys/cdefs.h>

#undef alloca

__BEGIN_DECLS
extern void *alloca(size_t);
__END_DECLS

#ifdef __GNUC__
#define alloca(size) __builtin_alloca(size)
#endif

#endif
