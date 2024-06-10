#ifndef _SYS_SIGNAL_H_
#define _SYS_SIGNAL_H_

#include <sys/types.h>

#define NSIG 32

#define SIGHUP 1
#define SIGINT 2
#define SIGQUIT 3
#define SIGILL 4
#define SIGTRAP 5
#define SIGABRT 6
#define SIGFPE 8
#define SIGKILL 9
#define SIGBUS 10
#define SIGSEGV 11
#define SIGSYS 12
#define SIGPIPE 13
#define SIGALRM 14
#define SIGTERM 15
#define SIGURG 16
#define SIGSTOP 17
#define SIGTSTP 18
#define SIGCONT 19
#define SIGCHLD 20
#define SIGTTIN 21
#define SIGTTOU 22
#define SIGIO 23
#define SIGXCPU 24
#define SIGXFSZ 25
#define SIGVTALRM 26
#define SIGPROF 27
#define SIGWINCH 28
#define SIGINFO 29
#define SIGUSR1 30
#define SIGUSR2 31

#define SIG_DFL (void (*)(int))0
#define SIG_IGN (void (*)(int))1
#define SIG_HOLD (void (*)(int))5
#define SIG_ERR ((void (*)(int)) - 1)

#define SIG_BLOCK 1
#define SIG_UNBLOCK 2
#define SIG_SETMASK 3

#define SA_RESTART 0x0002

typedef void (*sig_t)(int);
typedef unsigned int sigset_t;

union sigval {
  int sival_int;
  void *sival_ptr;
};

typedef struct __siginfo {
  int si_signo;
  int si_errno;
  int si_code;
  pid_t si_pid;
  uid_t si_uid;
  int si_status;
  void *si_addr;
  union sigval si_value;
  long si_band;
  unsigned long __pad[7];
} siginfo_t;

union __sigaction_u {
  void (*__sa_handler)(int);
  void (*__sa_sigaction)(int, struct __siginfo *, void *);
};

struct sigaction {
  union __sigaction_u __sigaction_u;
  sigset_t sa_mask;
  int sa_flags;
};

#define sa_handler __sigaction_u.__sa_handler
#define sa_sigaction __sigaction_u.__sa_sigaction

#define sigmask(m) (1 << ((m) - 1))

#endif
