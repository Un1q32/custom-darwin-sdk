#include <stdio.h>
#include <sys/mman.h>

void free(void *ptr) {
  if (ptr == NULL)
    return;

  ptr = (size_t *)ptr - 1;
  size_t size = *(size_t *)ptr;

  int ret = munmap(ptr, size);
  if (ret == -1) {
    perror("free()");
    return;
  }
}
