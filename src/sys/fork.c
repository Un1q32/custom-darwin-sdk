#include <sys/syscall.h>
#include <unistd.h>

pid_t fork(void) {
  pid_t child = syscall(SYS_fork);
  if (child == -1)
    return -1;
  if (child == getpid())
    return 0;
  return child;
}
