#include <stdlib.h>
#include <unistd.h>

unsigned long __stack_chk_guard = 0xBAAAAAAD;

void __stack_chk_fail(void) {
  static const char msg[] = "Stack smashing detected!\n";
  write(STDERR_FILENO, msg, sizeof(msg) - 1);
  _exit(EXIT_FAILURE);
}
