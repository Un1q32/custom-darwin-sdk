#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <stddef.h>
#include <sys/types.h>
#include <sys/unistd.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

extern void _exit(int);
extern int access(const char *, int);
extern ssize_t read(int, void *, size_t);
extern ssize_t write(int, const void *, size_t);
extern long syscall(long, ...);
extern int chdir(const char *);
extern int fchdir(int);
extern int rmdir(const char *);
extern int link(const char *, const char *);
extern int unlink(const char *);
extern int symlink(const char *, const char *);
extern int close(int);
extern char *getcwd(char *, size_t);
extern pid_t fork(void);
extern pid_t getpid(void);
extern uid_t getuid(void);
extern int execve(const char *, char *const[], char *const[]);
extern int execv(const char *, char *const[]);
extern int execvp(const char *, char *const[]);
extern int execvpe(const char *, char *const[], char *const[]);
extern int execlp(const char *, const char *, ...);
extern int execvP(const char *, const char *, char *const[]);
extern int execvPe(const char *, const char *, char *const[], char *const[]);
extern int execl(const char *, const char *, ...);
extern int execle(const char *, const char *, ...);
extern int usleep(useconds_t);
extern unsigned int sleep(unsigned int);
extern off_t lseek(int, off_t, int);
extern int isatty(int);
extern int dup(int);
extern int pipe(int[2]);
extern int tcsetpgrp(int, pid_t);
extern pid_t getpgrp(void);

#endif
