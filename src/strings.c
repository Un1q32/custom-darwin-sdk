#include <stddef.h>

void bzero(void *s, size_t n) {
    char *p = s;
    while (n--)
        *p++ = 0;
}
