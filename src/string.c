#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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
  if (!str)
    return NULL;
  size_t len = strlen(str) + 1;
  char *dup = malloc(len);
  if (dup)
    strcpy(dup, str);
  return dup;
}

size_t strlen(const char *s) {
  size_t len = 0;
  while (s[len])
    len++;
  return len;
}

size_t strnlen(const char *s, size_t maxlen) {
  size_t ret = strlen(s);
  return ret > maxlen ? maxlen : ret;
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
  bzero(s, n);
  __asm__ volatile("" : : "r"(s) : "memory");
}

char *strerror(int errnum) {
  char *ret = NULL;
  switch (errnum) {
  case EPERM:
    ret = "Operation not permitted";
    break;
  case ENOENT:
    ret = "No such file or directory";
    break;
  case ESRCH:
    ret = "No such process";
    break;
  case EINTR:
    ret = "Interrupted system call";
    break;
  case EIO:
    ret = "I/O error";
    break;
  case ENXIO:
    ret = "No such device or address";
    break;
  case E2BIG:
    ret = "Argument list too long";
    break;
  case ENOEXEC:
    ret = "Exec format error";
    break;
  case EBADF:
    ret = "Bad file number";
    break;
  case ECHILD:
    ret = "No child processes";
    break;
  case EDEADLK:
    ret = "Resource deadlock would occur";
    break;
  case ENOMEM:
    ret = "Out of memory";
    break;
  case EACCES:
    ret = "Permission denied";
    break;
  case EFAULT:
    ret = "Bad address";
    break;
  case ENOTBLK:
    ret = "Block device required";
    break;
  case EBUSY:
    ret = "Device or resource busy";
    break;
  case EEXIST:
    ret = "File exists";
    break;
  case EXDEV:
    ret = "Cross-device link";
    break;
  case ENODEV:
    ret = "No such device";
    break;
  case ENOTDIR:
    ret = "Not a directory";
    break;
  case EISDIR:
    ret = "Is a directory";
    break;
  case EINVAL:
    ret = "Invalid argument";
    break;
  case ENFILE:
    ret = "File table overflow";
    break;
  case EMFILE:
    ret = "Too many open files";
    break;
  case ENOTTY:
    ret = "Not a tty";
    break;
  case ETXTBSY:
    ret = "Text file busy";
    break;
  case EFBIG:
    ret = "File too large";
    break;
  case ENOSPC:
    ret = "No space left on device";
    break;
  case ESPIPE:
    ret = "Illegal seek";
    break;
  case EROFS:
    ret = "Read-only file system";
    break;
  case EMLINK:
    ret = "Too many links";
    break;
  case EPIPE:
    ret = "Broken pipe";
    break;
  case EDOM:
    ret = "Math argument out of domain of func";
    break;
  case ERANGE:
    ret = "Math result not representable";
    break;
  case EAGAIN:
    ret = "Resource temporarily unavailable";
    break;
  case EINPROGRESS:
    ret = "Operation now in progress";
    break;
  case EALREADY:
    ret = "Operation already in progress";
    break;
  case ENOTSOCK:
    ret = "Socket operation on non-socket";
    break;
  case EDESTADDRREQ:
    ret = "Destination address required";
    break;
  case EMSGSIZE:
    ret = "Message too long";
    break;
  case EPROTOTYPE:
    ret = "Protocol wrong type for socket";
    break;
  case ENOPROTOOPT:
    ret = "Protocol not available";
    break;
  case EPROTONOSUPPORT:
    ret = "Protocol not supported";
    break;
  case ESOCKTNOSUPPORT:
    ret = "Socket type not supported";
    break;
  case ENOTSUP:
    ret = "Operation not supported";
    break;
  case EPFNOSUPPORT:
    ret = "Protocol family not supported";
    break;
  default:
    ret = "Unknown error";
    break;
  }
  return ret;
}
