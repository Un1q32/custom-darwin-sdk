#include <errno.h>
#include <fcntl.h>
#include <machine/param.h>
#include <poll.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/syslimits.h>
#include <unistd.h>

long syscallret2 = 0;

long _syscall_error(long err, long ret2) {
  errno = err;
  syscallret2 = ret2;
  return -1;
}

long _syscall_success(long ret, long ret2) {
  syscallret2 = ret2;
  return ret;
}

int access(const char *path, int mode) {
  return syscall(SYS_access, path, mode);
}

int open(const char *path, int flags, ...) {
  mode_t mode = 0;
  if (flags & O_CREAT) {
    va_list va_args;
    va_start(va_args, flags);
    mode = va_arg(va_args, int);
    va_end(va_args);
  }
  bool cloexec = false;
  if (flags & O_CLOEXEC) {
    flags &= ~O_CLOEXEC;
    cloexec = true;
  }
  int fd = syscall(SYS_open, path, flags, mode);
  if (cloexec && fd != -1)
    fcntl(fd, F_SETFD, FD_CLOEXEC);
  return fd;
}

int openat(int fd, const char *path, int flags, ...) {
  mode_t mode = 0;
  if (flags & O_CREAT) {
    va_list va_args;
    va_start(va_args, flags);
    mode = va_arg(va_args, int);
    va_end(va_args);
  }

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
}

int close(int fd) { return syscall(SYS_close, fd); }

int mkdir(const char *path, mode_t mode) {
  return syscall(SYS_mkdir, path, mode);
}

int mkdirat(int fd, const char *path, mode_t mode) {
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
}

int rmdir(const char *path) { return syscall(SYS_rmdir, path); }

int link(const char *oldpath, const char *newpath) {
  return syscall(SYS_link, oldpath, newpath);
}

int unlink(const char *path) { return syscall(SYS_unlink, path); }

int symlink(const char *target, const char *linkpath) {
  return syscall(SYS_symlink, target, linkpath);
}

void *mmap(void *addr, size_t length, int prot, int flags, int fd,
           off_t offset) {
  if ((offset & PAGE_MASK) ||
      (((flags & MAP_PRIVATE) != MAP_PRIVATE) &&
       ((flags & MAP_SHARED) != MAP_SHARED)) ||
      (length == 0)) {
    errno = EINVAL;
    return MAP_FAILED;
  }
  long ret = syscall(SYS_mmap, addr, length, prot, flags, fd, offset);
  return ((ret == -1) ? MAP_FAILED : (void *)ret);
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
  while (1)
    ;
}

int chdir(const char *path) { return syscall(SYS_chdir, path); }

int fchdir(int fd) { return syscall(SYS_fchdir, fd); }

pid_t getpid(void) { return syscall(SYS_getpid); }

uid_t getuid(void) { return syscall(SYS_getuid); }

pid_t fork(void) {
  pid_t child = syscall(SYS_fork);
  if (child == -1)
    return -1;
  pid_t me = getpid();
  if (me == child)
    return 0;
  return child;
}

int execve(const char *filename, char *const argv[], char *const envp[]) {
  return syscall(SYS_execve, filename, argv, envp);
}

pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage) {
  long ret = syscall(SYS_wait4, pid, status, options, rusage);
  if (ret == -1)
    return -1;
  *status >>= 8;
  return ret;
}

int gettimeofday(struct timeval *tv, void *tz) {
  if (tv != NULL) {
    long ret = syscall(SYS_gettimeofday, tv, 0);
    if (ret == -1)
      return -1;
    else if (ret != 0) {
      tv->tv_sec = ret;
      tv->tv_usec = syscallret2;
    }
  }
  if (tz != NULL) {
    struct timezone *tmp_tz = (struct timezone *)tz;
    tmp_tz->tz_minuteswest = 0;
    tmp_tz->tz_dsttime = 0;
  }
  return 0;
}

off_t lseek(int fd, off_t offset, int whence) {
  return syscall(SYS_lseek, fd, offset, whence);
}

int ioctl(int fd, unsigned long request, ...) {
  va_list va_args;
  va_start(va_args, request);
  long arg = va_arg(va_args, long);
  va_end(va_args);
  return syscall(SYS_ioctl, fd, request, arg);
}

int stat(const char *path, struct stat *buf) {
  return syscall(SYS_stat64, path, buf);
}

int stat64(const char *path, struct stat64 *buf) {
  return syscall(SYS_stat64, path, buf);
}

int poll(struct pollfd *fds, nfds_t nfds, int timeout) {
  return syscall(SYS_poll, fds, nfds, timeout);
}

int kill(pid_t pid, int sig) { return syscall(SYS_kill, pid, sig); }

int pipe(int pipefd[2]) { return syscall(SYS_pipe, pipefd); }

pid_t getpgrp(void) { return syscall(SYS_getpgrp); }

int setuid(uid_t uid) { return syscall(SYS_setuid, uid); }

int setgid(gid_t gid) { return syscall(SYS_setgid, gid); }

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  return syscall(SYS_bind, sockfd, addr, addrlen);
}

int dup(int oldfd) { return syscall(SYS_dup, oldfd); }

int dup2(int oldfd, int newfd) { return syscall(SYS_dup2, oldfd, newfd); }

int shutdown(int sockfd, int how) { return syscall(SYS_shutdown, sockfd, how); }

int listen(int sockfd, int backlog) {
  return syscall(SYS_listen, sockfd, backlog);
}

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
  return syscall(SYS_accept, sockfd, addr, addrlen);
}

int socket(int domain, int type, int protocol) {
  return syscall(SYS_socket, domain, type, protocol);
}

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  return syscall(SYS_connect, sockfd, addr, addrlen);
}

int getsockopt(int sockfd, int level, int optname, void *optval,
               socklen_t *optlen) {
  return syscall(SYS_getsockopt, sockfd, level, optname, optval, optlen);
}

int setsockopt(int sockfd, int level, int optname, const void *optval,
               socklen_t optlen) {
  return syscall(SYS_setsockopt, sockfd, level, optname, optval, optlen);
}

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen) {
  return syscall(SYS_recvfrom, sockfd, buf, len, flags, src_addr, addrlen);
}

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags) {
  return syscall(SYS_recvmsg, sockfd, msg, flags);
}

int futimes(int fd, const struct timeval times[2]) {
  return syscall(SYS_futimes, fd, times);
}

int utimes(const char *filename, const struct timeval times[2]) {
  return syscall(SYS_utimes, filename, times);
}
