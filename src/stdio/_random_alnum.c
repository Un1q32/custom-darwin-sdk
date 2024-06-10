#include <stdlib.h>

void _random_alnum(char *name, size_t len) {
  const char charset[] =
      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  static unsigned int seed = 0;
  if (seed == 0)
    arc4random_buf(&seed, sizeof(seed));

  size_t i;
  for (i = 0; i < len; i++) {
    name[i] = charset[seed % (sizeof(charset) - 1)];
    seed = _rand(seed);
  }
}
