#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *strcat(char *dest, const char *src) {
    char *p = dest;
    while (*p) p++;
    while (*src) *p++ = *src++;
    *p = '\0';
    return dest;
}

char *strcpy(char *dest, const char *src) {
    char *ret = dest;
    while ((*dest++ = *src++) != '\0');
    return ret;
}

char *stpcpy(char *dest, const char *src) {
    while ((*dest++ = *src++) != '\0');
    return dest - 1;
}

char *strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *dup = malloc(len);
    if (dup)
        memcpy(dup, str, len);
    return dup;
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

int memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *p1 = s1, *p2 = s2;
    while (n-- > 0) {
        if (*p1 != *p2)
            return *p1 - *p2;
        p1++;
        p2++;
    }
    return 0;
}

size_t strlen(const char *s) {
    int n;

    for (n = 0; *s != '\0'; s++)
        n++;
    return n;
}

void explicit_bzero(void *s, size_t n) {
    memset(s, 0, n);
    __asm__ __volatile__("" : : "r"(s) : "memory");
}
