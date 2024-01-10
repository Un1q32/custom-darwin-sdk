#include <stdio.h>

int main(int argc, char *argv[]) {
    int num = -123;
    printf("num = %d\n", num);
    int num2 = 12345;
    printf("num2 = %d\n", num2);
    long num3 = 123456;
    printf("num3 = %ld\n", num3);
    unsigned long long num4 = 1234567;
    printf("num4 = %llu\n", num4);
    if (argc > 1)
        printf("argv[1] = %s\n", argv[1]);

    return 0;
}
