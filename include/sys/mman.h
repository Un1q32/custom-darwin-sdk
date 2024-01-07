#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#include <sys/types.h>

void *mmap(void *, size_t, int, int, int, off_t);

#endif
