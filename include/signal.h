#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <sys/cdefs.h>
#include <sys/signal.h>

typedef int sig_atomic_t;

__BEGIN_DECLS
extern sig_t signal(int, sig_t);
extern int kill(pid_t, int);
extern int sigaction(int, const struct sigaction *, struct sigaction *);
extern int sigemptyset(sigset_t *);
extern int sigismember(const sigset_t *, int);
__END_DECLS

#endif
