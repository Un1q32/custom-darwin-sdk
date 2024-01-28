#include <stdio.h>
#include <unistd.h>

int main() {
  puts("five");
  sleep(1);
  puts("four");
  sleep(1);
  puts("three");
  sleep(1);
  puts("two");
  sleep(1);
  puts("one");
  sleep(1);
  puts("boom!");
  return 0;
}
