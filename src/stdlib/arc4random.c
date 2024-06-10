#include <stdint.h>
#include <stdlib.h>

uint32_t arc4random(void) {
  uint32_t ret;
  arc4random_buf(&ret, sizeof(ret));
  return ret;
}
