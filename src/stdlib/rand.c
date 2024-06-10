#include <stdlib.h>

int rand(void) {
  int ret = _rand(_random_seed);
  _random_seed = ret;
  return ret;
}
