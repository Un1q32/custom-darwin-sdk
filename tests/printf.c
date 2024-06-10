#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[]) {
  printf("num = %d\n", -123);
  printf("num2 = %d\n", 12345);
  printf("num3 = %lld\n", 8589934592LL);
  printf("num4 = %llu\n", 0xFFFFFFFFFFFFFFFFULL);
  const float num5 = 3.1415926535897932384;
  printf("num5 = %f\n", num5);
  printf("num5 = %.2f\n", num5);
  printf("num5 = %.15f\n", num5);
  printf("num5 = %.*f\n", 15, num5);
  printf("percent sign: %%, 42 = %d\n", 42);
  const char *str = "chars";
  printf("%c%c%c%c%c\n", str[0], str[1], str[2], str[3], str[4]);
  printf("1 with a width of 3 chars: %03d\n", 1);
  printf("hex: %x\n", 0xdeadbeef);
  printf("HEX: %X\n", 0xdeadbeef);
  printf("hex alt: %#x\n", 0xdeadbeef);
  printf("small hex: %x\n", 0xabc);
  printf("small hex zero padded: %08x\n", 0xabc);
  printf("small hex zero padded alt: %#08x\n", 0xabc);
  printf("padded string:%10s\n", "hello");
  printf("dynamicly padded string:%*s\n", 10, "hello");
  printf("pointer: %p\n", (void *)&num5);
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
