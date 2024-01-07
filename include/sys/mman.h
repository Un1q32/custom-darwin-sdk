#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#include <stddef.h>
#include <sys/types.h>

#define PROT_READ   0x0001
#define PROT_WRITE  0x0002
#define MAP_PRIVATE 0x0002
#define MAP_ANON    0x1000
#define MAP_ANONYMOUS MAP_ANON

#define MAP_FAILED ((void *)-1)

void *mmap(void *, size_t, int, int, int, off_t);
int munmap(void *, size_t);

#endif
