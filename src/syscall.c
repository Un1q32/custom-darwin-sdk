#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/types.h>

long syscall(long number, ...) {
    long ret;
    long args[6];
    va_list va_args;
    va_start(va_args, number);
    int i;
    for (i = 0; i < 6; i++)
        args[i] = va_arg(va_args, long);
    va_end(va_args);
    __asm__ __volatile__ (
#if defined(__thumb__)
        "mov r12, %[number];"
        "ldm %[args], {r0-r5};"
        "svc #0x80;"
        "mov %[ret], r0;"
        : [ret] "=r"(ret)
        : [number] "r"(number), [args] "r"(args)
        : "r12", "r0", "r1", "r2", "r3", "r4", "r5"
#else
#error "syscall not implemented for this architecture"
#endif
    );
    return ret;
}

int open(const char *path, int flags, ...) {
    mode_t mode = 0;
    if (flags & O_CREAT) {
        va_list va_args;
        va_start(va_args, flags);
        mode = va_arg(va_args, int);
        va_end(va_args);
    }

    return syscall(SYS_open, path, flags, mode);
}

int openat(int fd, const char* path, int flags, ...) {
    mode_t mode = 0;
    if (flags & O_CREAT) {
        va_list va_args;
        va_start(va_args, flags);
        mode = va_arg(va_args, int);
        va_end(va_args);
    }

#ifdef SYS_openat
    return syscall(SYS_openat, fd, path, flags, mode);
#else
    if (fd == AT_FDCWD || path[0] == '/')
        return open(path, flags, mode);

    char fdpath[PATH_MAX];
    if (fcntl(fd, F_GETPATH, fdpath) == -1)
        return -1;

    char new_path[strlen(fdpath) + strlen(path) + 2];
    strcpy(new_path, fdpath);
    strcat(new_path, "/");
    strcat(new_path, path);
    return syscall(SYS_open, new_path, flags, mode);
#endif
}

int close(int fd) {
    return syscall(SYS_close, fd);
}

int mkdir(const char *path, mode_t mode) {
    return syscall(SYS_mkdir, path, mode);
}

int mkdirat(int fd, const char* path, mode_t mode) {
#ifdef SYS_mkdirat
    return syscall(SYS_mkdirat, fd, path, mode);
#else
    if (fd == AT_FDCWD || path[0] == '/')
        return mkdir(path, mode);

    char fdpath[PATH_MAX];
    if (fcntl(fd, F_GETPATH, fdpath) == -1)
        return -1;

    char new_path[strlen(fdpath) + strlen(path) + 2];
    strcpy(new_path, fdpath);
    strcat(new_path, "/");
    strcat(new_path, path);
    return mkdir(new_path, mode);
#endif
}

int rmdir(const char *path) {
    return syscall(SYS_rmdir, path);
}

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
    return (void *)syscall(SYS_mmap, addr, length, prot, flags, fd, offset);
}

int munmap(void *addr, size_t length) {
    return syscall(SYS_munmap, addr, length);
}

ssize_t read(int fd, void *buf, size_t count) {
    return syscall(SYS_read, fd, buf, count);
}

ssize_t write(int fd, const void *buf, size_t count) {
    return syscall(SYS_write, fd, buf, count);
}

int fcntl(int fd, int cmd, ...) {
    va_list va_args;
    va_start(va_args, cmd);
    long arg = va_arg(va_args, long);
    va_end(va_args);
    return syscall(SYS_fcntl, fd, cmd, arg);
}

void _exit(int status) {
    syscall(SYS_exit, status);
    while (1) {}
}

int chdir(const char *path) {
    return syscall(SYS_chdir, path);
}

int fchdir(int fd) {
    return syscall(SYS_fchdir, fd);
}

pid_t getpid(void) {
    return syscall(SYS_getpid);
}

pid_t fork(void) {
    pid_t child = syscall(SYS_fork);
    pid_t me = getpid();
    if (me == child)
        return 0;
    return child;
}

int execve(const char *filename, char *const argv[], char *const envp[]) {
    return syscall(SYS_execve, filename, argv, envp);
}

int execv(const char *filename, char *const argv[]) {
    return syscall(SYS_execve, filename, argv);
}

int execl(const char *filename, const char *arg, ...) {
    va_list va_args;
    va_start(va_args, arg);
    char *argv[1024];
    argv[0] = (char *)arg;
    int i;
    for (i = 1; i < 1024; i++) {
        argv[i] = va_arg(va_args, char *);
        if (argv[i] == NULL)
            break;
    }
    va_end(va_args);
    return syscall(SYS_execve, filename, argv);
}

int execle(const char *filename, const char *arg, ...) {
    va_list va_args;
    va_start(va_args, arg);
    char *argv[1024];
    argv[0] = (char *)arg;
    int i;
    for (i = 1; i < 1024; i++) {
        argv[i] = va_arg(va_args, char *);
        if (argv[i] == NULL)
            break;
    }
    char *envp[1024];
    for (i = 0; i < 1024; i++) {
        envp[i] = va_arg(va_args, char *);
        if (envp[i] == NULL)
            break;
    }
    va_end(va_args);
    return syscall(SYS_execve, filename, argv, envp);
}
