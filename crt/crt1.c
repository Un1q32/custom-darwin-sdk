#include <stdlib.h>
extern int main(int argc, char *argv[]);

void _start(void) __asm__("start");
void _start(void) {
    int argc = 0;
    char **argv = (char **)(&argc + 4);
    while (argv[argc] != NULL)
        argc++;
    exit(main(argc, argv));
}
