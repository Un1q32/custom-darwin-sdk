#include <sys/syscall.h>
#include <unistd.h>

int pipe(int pipefd[2]) { return syscall(SYS_pipe, pipefd); }
