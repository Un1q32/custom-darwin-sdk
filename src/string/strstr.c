#include <string.h>

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
