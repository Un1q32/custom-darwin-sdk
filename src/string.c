#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *strcat(char *dest, const char *src) {
  char *p = dest;
  while (*p)
    p++;
  while (*src)
    *p++ = *src++;
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

char *strdup(const char *str) {
  size_t len = strlen(str) + 1;
  char *dup = malloc(len);
  if (dup)
    memcpy(dup, str, len);
  return dup;
}

size_t strlen(const char *s) {
  int n;

  for (n = 0; *s != '\0'; s++)
    n++;
  return n;
}

char *strchr(const char *s, int c) {
  while (*s != (char)c) {
    if (*s == '\0')
      return NULL;
    s++;
  }
  return (char *)s;
}

char *strrchr(const char *s, int c) {
  char *last = NULL;
  do {
    if (*s == (char)c)
      last = (char *)s;
  } while (*s++);
  return last;
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2))
    s1++, s2++;
  return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  if (!n--)
    return 0;
  const unsigned char *s1_ = (void *)s1, *s2_ = (void *)s2;
  while (*s1_ && *s2_ && n && *s1_ == *s2_)
    s1_++, s2_++, n--;
  return *s1_ - *s2_;
}

char *strstr(const char *haystack, const char *needle) {
  size_t needle_len = strlen(needle);
  size_t haystack_len = strlen(haystack);

  if (needle_len == 0)
    return (char *)haystack;

  if (haystack_len < needle_len)
    return NULL;

  haystack_len -= needle_len;
  size_t i;
  for (i = 0; i <= haystack_len; i++) {
    if (haystack[i] == needle[0] &&
        !memcmp(haystack + i + 1, needle + 1, needle_len - 1))
      return (char *)(haystack + i);
  }

  return NULL;
}

char *strtok(char *str, const char *delim) {
  static char *next = NULL;
  if (str)
    next = str;
  if (!next)
    return NULL;
  char *ret = next;
  next += strspn(next, delim);
  if (!*next) {
    next = NULL;
    return ret;
  }
  next[strcspn(next, delim)] = '\0';
  return ret;
}

char *strtok_r(char *str, const char *delim, char **saveptr) {
  char *ret;
  if (!str)
    str = *saveptr;
  str += strspn(str, delim);
  if (!*str) {
    *saveptr = str;
    return NULL;
  }
  ret = str;
  str += strcspn(str, delim);
  if (*str)
    *str++ = '\0';
  *saveptr = str;
  return ret;
}

size_t strspn(const char *s, const char *accept) {
  size_t ret = 0;
  while (*s && strchr(accept, *s++))
    ret++;
  return ret;
}

size_t strcspn(const char *s, const char *reject) {
  size_t ret = 0;
  while (*s) {
    if (strchr(reject, *s))
      return ret;
    else
      s++, ret++;
  }
  return ret;
}

char *strpbrk(const char *s, const char *accept) {
  while (*s) {
    if (strchr(accept, *s))
      return (char *)s;
    else
      s++;
  }
  return NULL;
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

void explicit_bzero(void *s, size_t n) {
  memset(s, 0, n);
  __asm__ volatile("" : : "r"(s) : "memory");
}
