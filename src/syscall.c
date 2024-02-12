#include <errno.h>
#include <fcntl.h>
#include <machine/param.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/syslimits.h>
#include <sys/types.h>

long syscall(long number, ...) {
  long ret, args[6];
  va_list va_args;
  va_start(va_args, number);
  int i;
  for (i = 0; i < 6; i++)
    args[i] = va_arg(va_args, long);
  va_end(va_args);
  __asm__ volatile(
#if defined(__arm__)
      "mov r12, %[number];"
      "ldm %[args], {r0-r5};"
      "svc #0x80;"
      "mov %[ret], r0;"
      : [ret] "=r"(ret)
      : [number] "r"(number), [args] "r"(args)
      : "r12", "r0", "r1", "r2", "r3", "r4", "r5"
#else
      ""
#error architecture not supported
#endif
  );
  return ret;
}

int access(const char *path, int mode) {
  int ret = syscall(SYS_access, path, mode);
  if (ret != 0) {
    errno = ret;
    return -1;
  }
  return 0;
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

int openat(int fd, const char *path, int flags, ...) {
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

int close(int fd) { return syscall(SYS_close, fd); }

int mkdir(const char *path, mode_t mode) {
  int ret = syscall(SYS_mkdir, path, mode);
  if (ret != 0) {
    errno = ret;
    return -1;
  }
  return 0;
}

int mkdirat(int fd, const char *path, mode_t mode) {
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
  int ret = syscall(SYS_rmdir, path);
  if (ret != 0) {
    errno = ret;
    return -1;
  }
  return 0;
}

int link(const char *oldpath, const char *newpath) {
  int ret = syscall(SYS_link, oldpath, newpath);
  if (ret != 0) {
    errno = ret;
    return -1;
  }
  return 0;
}

int unlink(const char *path) {
  int ret = syscall(SYS_unlink, path);
  if (ret != 0) {
    errno = ret;
    return -1;
  }
  return 0;
}

int symlink(const char *target, const char *linkpath) {
  int ret = syscall(SYS_symlink, target, linkpath);
  if (ret != 0) {
    errno = ret;
    return -1;
  }
  return 0;
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
  return (void *)syscall(SYS_mmap, addr, length, prot, flags, fd, offset);
}

int munmap(void *addr, size_t length) {
  int ret = syscall(SYS_munmap, addr, length);
  if (ret != 0) {
    errno = ret;
    return -1;
  }
  return 0;
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

int chdir(const char *path) {
  int ret = syscall(SYS_chdir, path);
  if (ret != 0) {
    errno = ret;
    return -1;
  }
  return 0;
}

int fchdir(int fd) {
  int ret = syscall(SYS_fchdir, fd);
  if (ret != 0) {
    errno = ret;
    return -1;
  }
  return 0;
}

pid_t getpid(void) { return syscall(SYS_getpid); }

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

pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage) {
  long ret = syscall(SYS_wait4, pid, status, options, rusage);
  *status >>= 8;
  return ret;
}

int gettimeofday(struct timeval *tv, void *tz) {
  long nothing = 0;
  if (tv != NULL) {
    tv->tv_sec = syscall(SYS_gettimeofday, &nothing, NULL);
    tv->tv_usec = 0;
  }
  if (tz != NULL) {
    struct timezone *tmp_tz = (struct timezone *)tz;
    tmp_tz->tz_minuteswest = 0;
    tmp_tz->tz_dsttime = 0;
  }
  return 0;
}
