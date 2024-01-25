#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#include <stddef.h>
#include <sys/types.h>

#define PROT_NONE 0x00
#define PROT_READ 0x01
#define PROT_WRITE 0x02
#define PROT_EXEC 0x04

#define MAP_SHARED 0x0001
#define MAP_PRIVATE 0x0002
#define MAP_FIXED 0x0010
#define MAP_RENAME 0x0020
#define MAP_NORESERVE 0x0040
#define MAP_RESERVED0080 0x0080
#define MAP_NOEXTEND 0x0100
#define MAP_HASSEMAPHORE 0x0200
#define MAP_NOCACHE 0x0400

#define MAP_COPY MAP_PRIVATE

#define MAP_FILE 0x0000
#define MAP_ANON 0x1000

#define MAP_ANONYMOUS MAP_ANON

#define MAP_FAILED ((void *)-1)

void *mmap(void *, size_t, int, int, int, off_t);
int munmap(void *, size_t);

#endif
