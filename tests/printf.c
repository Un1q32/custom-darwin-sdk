#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[]) {
  printf("num = %d\n", -123);
  printf("num2 = %d\n", 12345);
  printf("num3 = %lld\n", 8589934592);
  printf("num4 = %llu\n", 0xFFFFFFFFFFFFFFFF);
  float num5 = 3.1415926535897932384;
  printf("num5 = %f\n", num5);
  printf("num5 = %.2f\n", num5);
  printf("num5 = %.15f\n", num5);
  printf("percent sign: %%\n");
  if (argc > 1) {
    int charcount = 0;
    printf("argv[1] = (%s)%n\n", argv[1], &charcount);
    int truecharcount = strlen(argv[1]) + 12;
    if (charcount == truecharcount)
      printf("Correct charcount, expected %d got %d\n", truecharcount,
             charcount);
    else
      printf("Incorrect charcount, expected %d got %d\n", truecharcount,
             charcount);
  }

  return 0;
}
