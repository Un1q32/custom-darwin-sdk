#include <errno.h>
#include <fcntl.h>
#include <machine/param.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/syslimits.h>
#include <sys/types.h>
#include <unistd.h>

long syscallret = 0;

long syscall(long number, ...) {
  va_list va_args;
  va_start(va_args, number);
  long ret, args[6];
  int i;
  for (i = 0; i < 6; i++)
    args[i] = va_arg(va_args, long);
  va_end(va_args);
  bool error = false;
  __asm__ volatile(
#if defined(__arm__)
      "ldr r12, %[number];"   /* load syscall number into r12 */
      "ldm %[args], {r0-r5};" /* load arguements into r0-r5 */
      "svc 0x80;"             /* make syscall */
      "mov %[ret], r0;"       /* save return value if carry clear */
      "mov %[ret2], r1;"      /* save 2nd return value if carry clear */
      "it cs;"                /* if carry set, set error flag */
      "movcs %[error], #1;"   /* if carry set, set error flag */
      : [ret] "=r"(ret), [ret2] "=r"(syscallret), [error] "=r"(error)
      : [number] "m"(number), [args] "r"(args)
      : "r0", "r1", "r2", "r3", "r4", "r5", "r12", "memory", "cc"
#else
      ""
#error architecture not supported
#endif
  );
  if (error) {
    errno = ret;
    ret = -1;
  }
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
  return syscall(SYS_mkdir, path, mode);
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
    long ret = syscall(SYS_gettimeofday, &nothing, NULL);
    if (ret != -1) {
      tv->tv_sec = ret;
      tv->tv_usec = syscallret;
    } else
      return -1;
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
