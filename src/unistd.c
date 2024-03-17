#include <errno.h>
#include <fcntl.h>
#include <paths.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syslimits.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

char *getcwd(char *buf, size_t size) {
  int fd = open(".", O_RDONLY);
  if (fd == -1)
    return NULL;

  char tmp[PATH_MAX];
  if (fcntl(fd, F_GETPATH, tmp) == -1)
    return NULL;

  size_t len = strlen(tmp);
  if (len >= size && buf != NULL) {
    errno = ERANGE;
    return NULL;
  }

  if (buf == NULL)
    buf = malloc(len + 1);

  strcpy(buf, tmp);
  return buf;
}

int execv(const char *filename, char *const argv[]) {
  return execve(filename, argv, NULL);
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
  return execv(filename, argv);
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
  return execve(filename, argv, envp);
}

int usleep(useconds_t usec) {
  struct timespec ts;
  ts.tv_sec = usec / 1000000;
  ts.tv_nsec = (usec % 1000000) * 1000;
  return nanosleep(&ts, NULL);
}

unsigned int sleep(unsigned int seconds) {
  struct timespec ts;
  ts.tv_sec = seconds;
  ts.tv_nsec = 0;
  return nanosleep(&ts, NULL);
}

int isatty(int fd) {
  struct termios dummy;
  return tcgetattr(fd, &dummy) == 0;
}

bool _search_path(const char *path, const char *filename, char *buf) {
  if (path == NULL || filename == NULL)
    return false;

  char *p = strtok((char *)path, ":");
  while (p != NULL) {
    snprintf(buf, PATH_MAX, "%s/%s", p, filename);
    if (access(buf, F_OK) == 0)
      return true;
    p = strtok(NULL, ":");
  }
  return false;
}

int execvPe(const char *filename, const char *path, char *const argv[],
            char *const envp[]) {
  char buf[PATH_MAX];
  if (!_search_path(path, filename, buf)) {
    errno = ENOENT;
    return -1;
  }

  return execve(buf, argv, envp);
}

int execvP(const char *filename, const char *path, char *const argv[]) {
  return execvPe(filename, path, argv, NULL);
}

int execvpe(const char *filename, char *const argv[], char *const envp[]) {
  char *path = getenv("PATH");
  if (path == NULL)
    path = _PATH_DEFPATH;

  return execvPe(filename, path, argv, envp);
}

int execvp(const char *filename, char *const argv[]) {
  return execvpe(filename, argv, NULL);
}

int execlp(const char *filename, const char *arg, ...) {
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
  return execvp(filename, argv);
}
