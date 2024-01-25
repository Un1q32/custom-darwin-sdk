#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

void free(void *ptr) {
    if (ptr == NULL)
        return;

    ptr = (char *)ptr - sizeof(size_t) - 1;
    if (*(char *)ptr != 0x5a) {
        puts("free(): invalid pointer");
        return;
    }
    size_t size = *(size_t *)((char *)ptr + 1);

    munmap(ptr, size);
}

void *malloc(size_t size) {
    if (size == 0)
        return NULL;

    size_t total_size = size + sizeof(size_t) + 1;
    void *ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (ptr == MAP_FAILED) {
        errno = ENOMEM;
        return NULL;
    }

    *(char *)ptr = 0x5a;
    *(size_t *)((char *)ptr + 1) = total_size;

    return (char *)ptr + sizeof(size_t) + 1;
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
