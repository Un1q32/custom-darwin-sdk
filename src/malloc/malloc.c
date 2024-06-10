#include <sys/mman.h>

void *malloc(size_t size) {
  size += sizeof(size_t);
  size_t *ptr =
      mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
  if (ptr == MAP_FAILED)
    return NULL;

  *ptr = size;

  return ptr + 1;
}
