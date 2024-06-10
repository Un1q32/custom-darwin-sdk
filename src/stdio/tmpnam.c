#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *tmpnam(char *name) {
  static char tmpname[L_tmpnam];
  if (name == NULL)
    name = tmpname;

  char template[] = P_tmpdir "/tmp.0.XXXXXX";
  strcpy(name, template);
  _random_alnum(name + sizeof(template) - 7, 6);
  while (!(readlink(name, NULL, 0) == -1 && errno == ENOENT))
    _random_alnum(name + sizeof(template) - 7, 6);
  return name;
}
