#include <stddef.h>
#include <string.h>
#include <sys/mman.h>

void free(void *ptr) {
    if (ptr == NULL)
        return;

    munmap(ptr, 0);
}

void *malloc(size_t size) {
    if (size == 0)
        return NULL;

    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (ptr == MAP_FAILED)
        return NULL;

    return ptr;
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
