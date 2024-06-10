#include <unistd.h>

void _Exit(int status) {
  _exit(status);
  while (1)
    ;
}
