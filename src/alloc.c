#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

void free(void *ptr) {
  if (ptr == NULL)
    return;

  ptr = (char *)ptr - sizeof(size_t);
  size_t size = *(size_t *)ptr;

  int ret = munmap(ptr, size);
  if (ret == -1) {
    perror("free()");
    return;
  }
}

void *malloc(size_t size) {
  if (size == 0)
    return NULL;

  size_t total_size = size + sizeof(size_t);
  void *ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANON, -1, 0);
  if (ptr == MAP_FAILED)
    return NULL;

  *(size_t *)ptr = total_size;

  return (char *)ptr + sizeof(size_t);
}

void *realloc(void *ptr, size_t size) {
  if (ptr == NULL)
    return malloc(size);

  if (size == 0) {
    free(ptr);
    return NULL;
  }

  void *new_ptr = malloc(size);
  if (new_ptr == NULL)
    return NULL;

  memcpy(new_ptr, ptr, size);
  free(ptr);
  return new_ptr;
}

void *reallocf(void *ptr, size_t size) {
  void *new_ptr = realloc(ptr, size);
  if (new_ptr == NULL)
    free(ptr);
  return new_ptr;
}

void *calloc(size_t count, size_t size) {
  size_t total_size = count * size;
  void *ptr = malloc(total_size);
  if (ptr == NULL)
    return NULL;

  memset(ptr, 0, total_size);
  return ptr;
}
