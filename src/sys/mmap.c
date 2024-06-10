#include <errno.h>
#include <machine/param.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <unistd.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd,
           off_t offset) {
  if ((offset & PAGE_MASK) ||
      (((flags & MAP_PRIVATE) != MAP_PRIVATE) &&
       ((flags & MAP_SHARED) != MAP_SHARED)) ||
      (length == 0)) {
    errno = EINVAL;
    return MAP_FAILED;
  }
  long ret = syscall(SYS_mmap, addr, length, prot, flags, fd, offset);
  return ((ret == -1) ? MAP_FAILED : (void *)ret);
}
