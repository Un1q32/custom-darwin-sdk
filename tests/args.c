#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
  fputs("argc: ", stdout);
  puts(itoa(argc));
  int i;
  for (i = 0; i < argc; i++)
    puts(argv[i]);
  return 0;
}
