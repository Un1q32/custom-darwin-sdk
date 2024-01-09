#include <stddef.h>
#include <string.h>

int bcmp(const void *s1, const void *s2, size_t n) {
    return memcmp(s1, s2, n);
}

void bzero(void *s, size_t n) {
    char *p = s;
    while (n--)
        *p++ = 0;
}
