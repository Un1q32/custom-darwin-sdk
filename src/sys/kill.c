#include <sys/syscall.h>
#include <unistd.h>

int kill(pid_t pid, int sig) { return syscall(SYS_kill, pid, sig); }
