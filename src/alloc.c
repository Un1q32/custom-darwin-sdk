#include <stddef.h>
#include <string.h>
#include <sys/mman.h>

void free(void *ptr) {
    if (ptr == NULL)
        return;

    ptr = (char *)ptr - sizeof(size_t);
    size_t size = *(size_t *)ptr;

    munmap(ptr, size);
}

void *malloc(size_t size) {
    if (size == 0)
        return NULL;

    size_t total_size = size + sizeof(size_t);
    void *ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
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
