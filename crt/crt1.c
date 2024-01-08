#include <stdlib.h>
extern int main(int argc, char *argv[]);

void start(void) __asm__("start");
void start(void) {
    int argc = 0;
    char **argv = (char **)(&argc + 4);
    char **argv_index = argv;
    while (*argv_index != NULL)
        argv_index++;
    argc = argv_index - argv;
    exit(main(argc, argv));
}
