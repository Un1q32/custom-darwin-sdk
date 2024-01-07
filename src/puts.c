#include <stdio.h>
#include <string.h>
#include <unistd.h>

int puts(const char *s) {
    char str[strlen(s) + 2];
    strcpy(str, s);
    strcat(str, "\n");
    int ret = write(STDOUT_FILENO, str, strlen(str));
    return ret;
}
