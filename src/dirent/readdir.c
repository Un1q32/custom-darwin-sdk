#include <dirent.h>
#include <unistd.h>

struct dirent *readdir(DIR *dir) {
  static struct dirent entry;
  int fd = dir->__dd_fd;
  int n = read(fd, &entry, sizeof(struct dirent));
  if (n == sizeof(struct dirent))
    return &entry;
  else
    return NULL;
}
