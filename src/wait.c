#include <stdlib.h>
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *status, int options) {
  return wait4(pid, status, options, NULL);
}

pid_t wait3(int *status, int options, struct rusage *rusage) {
  return wait4(-1, status, options, rusage);
}

pid_t wait(int *status) { return wait3(status, 0, NULL); }
