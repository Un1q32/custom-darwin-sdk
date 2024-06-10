#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stddef.h>
#include <sys/cdefs.h>

__BEGIN_DECLS
extern void *malloc(size_t);
extern void *realloc(void *, size_t);
extern void *reallocf(void *, size_t);
extern void *calloc(size_t, size_t);
extern void free(void *);
extern size_t malloc_usable_size(void *);
__END_DECLS

#endif
