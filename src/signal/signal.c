#include <signal.h>

sig_t signal(int sig, sig_t func) {
  struct sigaction sa_old;
  struct sigaction sa = {
      .sa_handler = func,
      .sa_flags = 0,
  };

  sigemptyset(&sa.sa_mask);
  if (!sigismember(&sa.sa_mask, sig))
    sa.sa_flags |= SA_RESTART;

  if (sigaction(sig, &sa, &sa_old) < 0)
    return SIG_ERR;

  return sa_old.sa_handler;
}
