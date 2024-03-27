#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

char *strcat(char *dst, const char *src) {
  char *p = dst;
  while (*p)
    p++;
  while (*src)
    *p++ = *src++;
  *p = '\0';
  return dst;
}

char *strcpy(char *dst, const char *src) {
  char *ret = dst;
  while ((*dst++ = *src++) != '\0')
    ;
  return ret;
}

char *stpcpy(char *dst, const char *src) {
  while ((*dst++ = *src++) != '\0')
    ;
  return dst - 1;
}

char *strdup(const char *str) {
  if (str == NULL)
    return NULL;
  char *dup = malloc(strlen(str) + 1);
  if (dup != NULL)
    strcpy(dup, str);
  return dup;
}

size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len])
    len++;
  return len;
}

size_t strnlen(const char *str, size_t maxlen) {
  size_t ret = strlen(str);
  return ret > maxlen ? maxlen : ret;
}

char *strchr(const char *str, int ch) {
  while (*str != (char)ch) {
    if (*str == '\0')
      return NULL;
    str++;
  }
  return (char *)str;
}

char *strrchr(const char *str, int ch) {
  char *last = NULL;
  do {
    if (*str == (char)ch)
      last = (char *)str;
  } while (*str++);
  return last;
}

int strcmp(const char *str1, const char *str2) {
  while (*str1 && (*str1 == *str2))
    str1++, str2++;
  return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  if (!n--)
    return 0;
  const unsigned char *s1_ = (void *)s1, *s2_ = (void *)s2;
  while (*s1_ && *s2_ && n && *s1_ == *s2_)
    s1_++, s2_++, n--;
  return *s1_ - *s2_;
}

char *strncpy(char *dst, const char *src, size_t size) {
  char *ret = dst;
  while (size && (*dst++ = *src++))
    size--;
  while (size--)
    *dst++ = '\0';
  return ret;
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

size_t strspn(const char *str, const char *accept) {
  size_t ret = 0;
  while (*str && strchr(accept, *str++))
    ret++;
  return ret;
}

size_t strcspn(const char *str, const char *reject) {
  size_t ret = 0;
  while (*str) {
    if (strchr(reject, *str))
      return ret;
    else
      str++, ret++;
  }
  return ret;
}

char *strpbrk(const char *str, const char *accept) {
  while (*str) {
    if (strchr(accept, *str))
      return (char *)str;
    else
      str++;
  }
  return NULL;
}

void *memcpy(void *dst, const void *src, size_t size) {
  char *d = dst;
  const char *s = src;
  while (size--)
    *d++ = *s++;
  return dst;
}

void *memset(void *buf, int byte, size_t size) {
  unsigned char *p = buf;
  while (size--)
    *p++ = (unsigned char)byte;
  return buf;
}

void memset_pattern4(void *b, const void *pattern, size_t len) {
  unsigned int *p = b;
  unsigned int pat = *(unsigned int *)pattern;
  while (len >= 4) {
    *p++ = pat;
    len -= 4;
  }
  unsigned char *q = (unsigned char *)p;
  while (len--)
    *q++ = *(unsigned char *)pattern;
}

void memset_pattern8(void *b, const void *pattern, size_t len) {
  unsigned long long *p = b;
  unsigned long long pat = *(unsigned long long *)pattern;
  while (len >= 8) {
    *p++ = pat;
    len -= 8;
  }
  unsigned char *q = (unsigned char *)p;
  while (len--)
    *q++ = *(unsigned char *)pattern;
}

void memset_pattern16(void *b, const void *pattern, size_t len) {
  unsigned long long *p = b;
  unsigned long long pat1 = *(unsigned long long *)pattern;
  unsigned long long pat2 = *((unsigned long long *)pattern + 1);
  while (len >= 16) {
    *p++ = pat1;
    *p++ = pat2;
    len -= 16;
  }
  unsigned char *q = (unsigned char *)p;
  while (len--)
    *q++ = *(unsigned char *)pattern;
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

void *memmove(void *dst, const void *src, size_t n) {
  char *d = dst;
  const char *s = src;
  if (d < s)
    while (n--)
      *d++ = *s++;
  else {
    d += n;
    s += n;
    while (n--)
      *--d = *--s;
  }
  return dst;
}

void *memchr(const void *buf, int ch, size_t size) {
  const unsigned char *p = buf;
  while (size--) {
    if (*p == (unsigned char)ch)
      return (void *)p;
    p++;
  }
  return NULL;
}

char *strtok(char *str, const char *delim) {
  static char *next = NULL;
  if (str)
    next = str;
  else if (!next)
    return NULL;
  str = next + strspn(next, delim);
  next = str + strcspn(str, delim);
  if (next == str)
    return (next = NULL);
  next = *next ? *next = '\0', next + 1 : NULL;
  return str;
}

char *strtok_r(char *str, const char *delim, char **saveptr) {
  char *token;
  if (!str)
    str = *saveptr;
  str += strspn(str, delim);
  if (!*str)
    return *saveptr = str, NULL;
  token = str;
  str = strpbrk(str, delim);
  if (str)
    *str++ = '\0';
  return *saveptr = str, token;
}

void explicit_bzero(void *s, size_t n) {
  bzero(s, n);
  __asm__ volatile("" : : "r"(s) : "memory");
}

char *strerror(int errnum) {
  switch (errnum) {
  case 0:
    return "No error";
  case EPERM:
    return "Operation not permitted";
  case ENOENT:
    return "No such file or directory";
  case ESRCH:
    return "No such process";
  case EINTR:
    return "Interrupted system call";
  case EIO:
    return "I/O error";
  case ENXIO:
    return "No such device or address";
  case E2BIG:
    return "Argument list too long";
  case ENOEXEC:
    return "Exec format error";
  case EBADF:
    return "Bad file number";
  case ECHILD:
    return "No child processes";
  case EDEADLK:
    return "Resource deadlock would occur";
  case ENOMEM:
    return "Out of memory";
  case EACCES:
    return "Permission denied";
  case EFAULT:
    return "Bad address";
  case ENOTBLK:
    return "Block device required";
  case EBUSY:
    return "Device or resource busy";
  case EEXIST:
    return "File exists";
  case EXDEV:
    return "Cross-device link";
  case ENODEV:
    return "No such device";
  case ENOTDIR:
    return "Not a directory";
  case EISDIR:
    return "Is a directory";
  case EINVAL:
    return "Invalid argument";
  case ENFILE:
    return "File table overflow";
  case EMFILE:
    return "Too many open files";
  case ENOTTY:
    return "Not a tty";
  case ETXTBSY:
    return "Text file busy";
  case EFBIG:
    return "File too large";
  case ENOSPC:
    return "No space left on device";
  case ESPIPE:
    return "Illegal seek";
  case EROFS:
    return "Read-only file system";
  case EMLINK:
    return "Too many links";
  case EPIPE:
    return "Broken pipe";
  case EDOM:
    return "Math argument out of domain of func";
  case ERANGE:
    return "Math result not representable";
  case EAGAIN:
    return "Resource temporarily unavailable";
  case EINPROGRESS:
    return "Operation now in progress";
  case EALREADY:
    return "Operation already in progress";
  case ENOTSOCK:
    return "Socket operation on non-socket";
  case EDESTADDRREQ:
    return "Destination address required";
  case EMSGSIZE:
    return "Message too long";
  case EPROTOTYPE:
    return "Protocol wrong type for socket";
  case ENOPROTOOPT:
    return "Protocol not available";
  case EPROTONOSUPPORT:
    return "Protocol not supported";
  case ESOCKTNOSUPPORT:
    return "Socket type not supported";
  case ENOTSUP:
    return "Operation not supported";
  case EPFNOSUPPORT:
    return "Protocol family not supported";
  case EAFNOSUPPORT:
    return "Address family not supported by protocol";
  case EADDRINUSE:
    return "Address already in use";
  case EADDRNOTAVAIL:
    return "Cannot assign requested address";
  case ENETDOWN:
    return "Network is down";
  case ENETUNREACH:
    return "Network is unreachable";
  case ENETRESET:
    return "Network dropped connection on reset";
  case ECONNABORTED:
    return "Software caused connection abort";
  case ECONNRESET:
    return "Connection reset by peer";
  case ENOBUFS:
    return "No buffer space available";
  case EISCONN:
    return "Socket is already connected";
  case ENOTCONN:
    return "Socket is not connected";
  case ESHUTDOWN:
    return "Cannot send after socket shutdown";
  case ETOOMANYREFS:
    return "Too many references: cannot splice";
  case ETIMEDOUT:
    return "Connection timed out";
  case ECONNREFUSED:
    return "Connection refused";
  case ELOOP:
    return "Too many levels of symbolic links";
  case ENAMETOOLONG:
    return "File name too long";
  case EHOSTDOWN:
    return "Host is down";
  case EHOSTUNREACH:
    return "No route to host";
  case ENOTEMPTY:
    return "Directory not empty";
  case EPROCLIM:
    return "Too many processes";
  case EUSERS:
    return "Too many users";
  case EDQUOT:
    return "Disc quota exceeded";
  case ESTALE:
    return "Stale NFS file handle";
  case EREMOTE:
    return "Too many levels of remote in path";
  case EBADRPC:
    return "RPC struct is bad";
  case ERPCMISMATCH:
    return "RPC version wrong";
  case EPROGUNAVAIL:
    return "RPC prog. not avail";
  case EPROGMISMATCH:
    return "Program version wrong";
  case EPROCUNAVAIL:
    return "Bad procedure for program";
  case ENOLCK:
    return "No locks available";
  case ENOSYS:
    return "Function not implemented";
  case EFTYPE:
    return "Inappropriate file type or format";
  case EAUTH:
    return "Authentication error";
  case ENEEDAUTH:
    return "Need authenticator";
  case EPWROFF:
    return "Device power is off";
  case EDEVERR:
    return "Device error";
  case EOVERFLOW:
    return "Value too large to be stored in data type";
  case EBADEXEC:
    return "Bad executable";
  case EBADARCH:
    return "Bad CPU type in executable";
  case ESHLIBVERS:
    return "Shared library version mismatch";
  case EBADMACHO:
    return "Malformed Macho file";
  case ECANCELED:
    return "Operation canceled";
  case EIDRM:
    return "Identifier removed";
  case ENOMSG:
    return "No message of desired type";
  case EILSEQ:
    return "Illegal byte sequence";
  case ENOATTR:
    return "Attribute not found";
  case EBADMSG:
    return "Bad message";
  case EMULTIHOP:
    return "Reserved";
  case ENODATA:
    return "No message available on STREAM";
  case ENOLINK:
    return "Reserved";
  case ENOSR:
    return "No STREAM resources";
  case ENOSTR:
    return "Not a STREAM";
  case EPROTO:
    return "Protocol error";
  case ETIME:
    return "STREAM ioctl timeout";
  case EOPNOTSUPP:
    return "Operation not supported on socket";
  case ENOPOLICY:
    return "No such policy registered";
  case ENOTRECOVERABLE:
    return "State not recoverable";
  case EOWNERDEAD:
    return "Previous owner died";
  case EQFULL:
    return "Interface output queue is full";
  default:
    return "Unknown error";
  }
}
