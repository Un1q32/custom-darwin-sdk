#include <signal.h>
#include <sys/syscall.h>
#include <unistd.h>

int sigaction(int signum, const struct sigaction *act,
              struct sigaction *oldact) {
  return syscall(SYS_sigaction, signum, act, oldact);
}
