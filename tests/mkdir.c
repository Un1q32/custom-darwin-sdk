#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  char pathtoolong[PATH_MAX + 1];
  int i;
  for (i = 0; i < PATH_MAX; i++)
    pathtoolong[i] = 'a';
  pathtoolong[PATH_MAX] = '\0';
  i = mkdir(pathtoolong, 0777);
  if (i != -1) {
    puts("mkdir should have failed");
    return 1;
  }
  if (errno != ENAMETOOLONG) {
    puts("mkdir should have set errno to ENAMETOOLONG");
    printf("errno was %d\n", errno);
    return 1;
  }
  i = mkdir("testdir", 0777);
  if (i == -1) {
    puts("mkdir failed");
    printf("errno was %d\n", errno);
    return 1;
  }
  i = rmdir("testdir");
  if (i == -1) {
    puts("rmdir failed");
    printf("errno was %d\n", errno);
    return 1;
  }
  return 0;
}
