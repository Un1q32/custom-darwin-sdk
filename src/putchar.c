#include <stdio.h>
#include <unistd.h>

int putchar(int c) {
    // return putc(c, stdout);
    return write(1, &c, 1);
}
