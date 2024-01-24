#include <stdlib.h>
extern int main(int argc, char *argv[], char *envp[]);

extern int NXArgc;
extern char **NXArgv;
extern char **environ;

void start(void) __asm__("start");
void start(void) {
    int argc = 0;
    char **argv = (char **)(&argc + 4);
    while (argv[argc] != NULL)
        argc++;
    char **envp = argv + argc + 1;
    NXArgc = argc;
    NXArgv = argv;
    environ = envp;
    exit(main(argc, argv, envp));
    while (1);
}
