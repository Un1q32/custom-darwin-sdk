#include <malloc.h>
#include <strings.h>

void *calloc(size_t count, size_t size) {
  size_t total_size = count * size;
  void *ptr = malloc(total_size);
  if (ptr == NULL)
    return NULL;

  bzero(ptr, total_size);
  return ptr;
}
