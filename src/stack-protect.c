#include <stdio.h>
#include <stdlib.h>

unsigned long __stack_chk_guard = 0xdeadbeef;

void __stack_chk_fail(void) {
  puts("Stack smashing detected");
  exit(EXIT_FAILURE);
}
