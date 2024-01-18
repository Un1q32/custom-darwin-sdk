#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid = fork();
    if (pid == 0) {
        printf("Hello from child [PID - %d]\n", getpid());
        chdir("..");
        char *cwd = getcwd(NULL, 0);
        printf("Child cwd: %s\n", cwd);
        free(cwd);
    } else if (pid > 0) {
        printf("Hello from parent [PID - %d]\n", getpid());
        char *cwd = getcwd(NULL, 0);
        printf("Parent cwd: %s\n", cwd);
        free(cwd);
    } else {
        puts("Fork failed");
        return 1;
    }
    return 0;
}
