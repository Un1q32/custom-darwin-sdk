#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  char *msg = "Hello, world!\n";
  int nbytes = strlen(msg);
  int ret = write(STDOUT_FILENO, msg, nbytes);
  if (ret != nbytes)
    return 1;
  return 0;
}
