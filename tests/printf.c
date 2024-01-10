#include <stdio.h>

int main(int argc, char *argv[]) {
    int num = -123;
    printf("num = %d\n", num);
    int num2 = 12345;
    printf("num2 = %d\n", num2);
    unsigned long long num3 = 12345678;
    printf("num3 = %llu\n", num3);
    if (argc > 1)
        printf("argv[1] = %s\n", argv[1]);

    return 0;
}
