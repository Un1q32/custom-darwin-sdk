#include <stddef.h>

char *strcat(char *dest, const char *src) {
    char *p = dest;
    while (*p) p++;
    while (*src) *p++ = *src++;
    *p = '\0';
    return dest;
}

char *strcpy(char *dest, const char *src) {
    char *ret = dest;
    while ((*dest++ = *src++) != '\0')
        ;
    return ret;
}

char *stpcpy(char *dest, const char *src) {
    while ((*dest++ = *src++) != '\0')
        ;
    return dest - 1;
}

void *memcpy(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    while (n--)
        *d++ = *s++;
    return dest;
}

void *memset(void *s, int c, size_t n) {
    char *s2 = s;
    while (n--)
        *s2++ = (unsigned char)c;
    return s;
}

size_t strlen(const char *s) {
    int n;

    for (n = 0; *s != '\0'; s++)
        n++;
    return n;
}
