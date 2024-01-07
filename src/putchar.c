#include <stdio.h>
#include <unistd.h>

int putchar(int c) {
    return putc(c, stdout);
}
