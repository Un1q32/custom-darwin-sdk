#include <stdlib.h>

int _rand(unsigned int seed) {
  long hi, lo, x;
  if (seed == 0)
    seed = 123459876;
  hi = seed / 127773;
  lo = seed % 127773;
  x = 16807 * lo - 2836 * hi;
  if (x < 0)
    x += 0x7FFFFFFF;
  return x % ((unsigned long)RAND_MAX + 1);
}
