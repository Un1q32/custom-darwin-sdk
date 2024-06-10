#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

int closedir(DIR *dir) {
  int fd = dir->__dd_fd;
  free(dir);
  return close(fd);
}
