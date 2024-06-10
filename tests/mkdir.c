#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/syslimits.h>
#include <unistd.h>

int main(void) {
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
    perror("mkdir");
    return 1;
  }
  i = mkdir("testdir", 0777);
  if (i == -1) {
    puts("mkdir failed");
    perror("mkdir");
    return 1;
  }
  i = rmdir("testdir");
  if (i == -1) {
    puts("rmdir failed");
    perror("rmdir");
    return 1;
  }
  puts("mkdir test passed");
  return 0;
}
