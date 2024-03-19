#include <unistd.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  int ret = write(STDOUT_FILENO, "Hello, world!\n", 14);
  if (ret != 14)
    return 1;
  return 0;
}
