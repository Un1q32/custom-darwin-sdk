#include <malloc.h>
#include <string.h>

void *realloc(void *ptr, size_t size) {
  void *new_ptr = malloc(size);
  if (new_ptr == NULL || ptr == NULL)
    return new_ptr;

  size_t old_size = malloc_usable_size(ptr);
  memcpy(new_ptr, ptr, old_size < size ? old_size : size);
  free(ptr);
  return new_ptr;
}
