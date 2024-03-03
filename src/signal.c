#include <signal.h>

void (*signal(int sig, void (*func)(int)))(int) {
  (void)sig;
  (void)func;
  return (void (*)(int))0;
}
