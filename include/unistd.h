#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <stddef.h>
#include <sys/types.h>

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

extern void _exit(int);
extern ssize_t read(int, void *, size_t);
extern ssize_t write(int, const void *, size_t);
extern long syscall(long, ...);
extern int chdir(const char *);
extern int fchdir(int);
extern int rmdir(const char *);
extern int link(const char *, const char *);
extern int unlink(const char *);
extern int close(int);
extern char *getcwd(char *, size_t);
extern pid_t fork(void);
extern pid_t getpid(void);
extern int execve(const char *, char *const [], char *const []);
extern int execv(const char *, char *const []);
extern int execl(const char *, const char *, ...);
extern int execle(const char *, const char *, ...);

#endif
