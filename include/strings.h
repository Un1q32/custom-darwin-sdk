#ifndef _STRINGS_H_
#define _STRINGS_H_

#include <stddef.h>
#include <sys/cdefs.h>

__BEGIN_DECLS
extern void bzero(void *, size_t);
extern int bcmp(const void *, const void *, size_t);
extern void bcopy(const void *, void *, size_t);
__END_DECLS

#endif
