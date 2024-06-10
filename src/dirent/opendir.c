#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>

DIR *opendir(const char *name) {
  DIR *dir = malloc(sizeof(DIR));
  dir->__dd_fd = open(name, O_RDONLY);
  return dir;
}
