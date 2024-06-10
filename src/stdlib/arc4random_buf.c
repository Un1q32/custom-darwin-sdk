#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void arc4random_buf(void *buf, size_t n) {
  /* TODO: Apple's man page says their implementation works in chroot */
  /* ours should too */

  int fd = open("/dev/urandom", O_RDONLY);
  if (fd == -1)
    abort();
  if (read(fd, buf, n) != (ssize_t)n)
    abort();
  close(fd);
}
