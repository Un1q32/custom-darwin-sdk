#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid = fork();
    if (pid == 0) {
        printf("Hello from child [PID - %d]\n", getpid());
        chdir("..");
        char *cwd = getcwd(NULL, 0);
        printf("Current working directory: %s\n", cwd);
        free(cwd);
    } else if (pid > 0) {
        printf("Hello from parent [PID - %d]\n", getpid());
        char *cwd = getcwd(NULL, 0);
        printf("Current working directory: %s\n", cwd);
        free(cwd);
    } else {
        return 1;
    }
}
