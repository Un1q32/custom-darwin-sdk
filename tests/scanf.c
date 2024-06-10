#include <stdio.h>

int main(void) {
  int a = 0, b = 0;
  long long c = 0;
  unsigned int d = 0;
  char str[14];
  char *nothing = NULL;
  int ret =
      sscanf("123%456 987 notwhitespacex8589934592 54321",
             "%d%%%d %*d %13sx%lld %u%s", &a, &b, str, &c, &d, nothing);
  printf("a = %d, b = %d\n", a, b);
  printf("c = %lld\n", c);
  printf("d = %u\n", d);
  printf("str = %s\n", str);
  if (ret == 5) {
    puts("All conversions successful");
    return 0;
  } else {
    puts("Some conversions failed");
    return 1;
  }
}
