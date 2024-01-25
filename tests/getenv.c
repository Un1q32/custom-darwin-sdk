#include <stdio.h>
#include <stdlib.h>

int main() {
    char *home = getenv("HOME");
    if (home)
        puts(home);
    return 0;
}
