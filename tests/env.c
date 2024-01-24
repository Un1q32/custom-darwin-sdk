#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    (void)argc;
    (void)argv;
    int i;
    for (i = 0; envp[i] != NULL; i++)
        puts(envp[i]);
    return 0;
}
