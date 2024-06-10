#include <errno.h>
#include <signal.h>

int sigismember(const sigset_t *set, int signo) {
  if (signo < 0 || signo > NSIG) {
    errno = EINVAL;
    return -1;
  }
  if (signo == 0)
    return 0;
  return (*set & sigmask(signo)) != 0;
}
