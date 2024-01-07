#include <stdio.h>
#include <string.h>
#include <unistd.h>

int puts(const char *s) {
    int ret = write(STDOUT_FILENO, s, strlen(s));
    putchar('\n');
    return ret;
}
