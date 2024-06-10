#include <sys/wait.h>
#include <unistd.h>

int system(const char *command) {
  if (command == NULL) {
    if (access("/bin/sh", X_OK) == 0)
      return 1;
    else
      return 0;
  }
  int pid = fork();
  if (pid == 0) {
    execl("/bin/sh", "sh", "-c", command, NULL);
    return 127;
  } else if (pid > 0) {
    int status;
    waitpid(pid, &status, 0);
    return status;
  }
  return -1;
}
