#include <stdio.h>

int main(int argc, char *argv[]) {
    int num = 123;
    printf("num = %d\n", num);
    if (argc > 1)
        printf("argv[1] = %s\n", argv[1]);

    return 0;
}
