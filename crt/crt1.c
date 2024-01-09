#include <stdlib.h>
extern int main(int argc, char *argv[]);

#ifdef __APPLE__
void _start(void) __asm__("start");
#endif
void _start(void) {
    int argc = 0;
    char **argv = (char **)(&argc + 4);
    char **argv_index = argv;
    while (*argv_index != NULL)
        argv_index++;
    argc = argv_index - argv;
    exit(main(argc, argv));
}
