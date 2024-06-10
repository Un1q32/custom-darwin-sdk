#include <string.h>

void bcopy(const void *src, void *det, size_t n) {
    memcpy(det, src, n);
}
