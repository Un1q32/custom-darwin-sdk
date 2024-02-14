#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

long long strtoll(const char *nptr, char **endptr, int base) {
  long long ret = 0;
  int sign = 1;
  while (isspace(*nptr))
    nptr++;
  if (*nptr == '-') {
    sign = -1;
    nptr++;
  } else if (*nptr == '+')
    nptr++;
  if (base == 0 || base == 16) {
    if (nptr[0] == '0') {
      if (nptr[1] == 'x' || nptr[1] == 'X') {
        base = 16;
        nptr += 2;
      } else if (base == 0)
        base = 8;
    } else if (base == 0)
      base = 10;
  }

  while (1) {
    int digit;
    if (*nptr >= '0' && *nptr <= '9')
      digit = *nptr - '0';
    else if (*nptr >= 'a' && *nptr <= 'z')
      digit = *nptr - 'a' + 10;
    else if (*nptr >= 'A' && *nptr <= 'Z')
      digit = *nptr - 'A' + 10;
    else
      break;
    if (digit >= base)
      break;
    ret = ret * base + digit;
    nptr++;
  }
  if (endptr)
    *endptr = (char *)nptr;
  return sign * ret;
}

long strtol(const char *nptr, char **endptr, int base) {
  return (long)strtoll(nptr, endptr, base);
}

unsigned long long strtoull(const char *nptr, char **endptr, int base) {
  unsigned long long ret = 0;
  while (isspace(*nptr))
    nptr++;
  if (base == 0 || base == 16) {
    if (nptr[0] == '0') {
      if (nptr[1] == 'x' || nptr[1] == 'X') {
        base = 16;
        nptr += 2;
      } else if (base == 0)
        base = 8;
    } else if (base == 0)
      base = 10;
  }

  while (1) {
    int digit;
    if (*nptr >= '0' && *nptr <= '9')
      digit = *nptr - '0';
    else if (*nptr >= 'a' && *nptr <= 'z')
      digit = *nptr - 'a' + 10;
    else if (*nptr >= 'A' && *nptr <= 'Z')
      digit = *nptr - 'A' + 10;
    else
      break;
    if (digit >= base)
      break;
    ret = ret * base + digit;
    nptr++;
  }
  if (endptr)
    *endptr = (char *)nptr;
  return ret;
}

unsigned long strtoul(const char *nptr, char **endptr, int base) {
  return (unsigned long)strtoull(nptr, endptr, base);
}

int atoi(const char *nptr) { return (int)strtol(nptr, NULL, 10); }

char *utoa(unsigned long long num) {
  static char buf[32];
  char *p = buf + 31;
  *p = '\0';
  do {
    *--p = '0' + num % 10;
    num /= 10;
  } while (num);
  return strdup(p);
}

char *itoa(long long num) {
  if (num < 0) {
    char *ret = utoa(-num);
    char *p = ret - 1;
    *p = '-';
    return strdup(p);
  } else
    return utoa(num);
}

char *ftoa(long double num, int percision) {
  static char buf[32];
  char *p = buf;
  if (num < 0) {
    *p++ = '-';
    num = -num;
  }
  unsigned long long integer = num;
  num -= integer;
  char *int_str = utoa(integer);
  strcpy(p, int_str);
  p += strlen(int_str);
  *p++ = '.';
  while (percision--) {
    num *= 10;
    *p++ = '0' + (int)num;
    num -= (int)num;
  }
  *p = '\0';
  return strdup(buf);
}

char *utox(unsigned long long num, unsigned char len) {
  char buf[len + 1];
  char *p = buf + len;
  *p = '\0';
  do {
    *--p = "0123456789abcdef"[num & 0xf];
    num >>= 4;
  } while (p > buf);
  return strdup(p);
}

char *utoX(unsigned long long num, unsigned char len) {
  char buf[len + 1];
  char *p = buf + len;
  *p = '\0';
  do {
    *--p = "0123456789ABCDEF"[num & 0xf];
    num >>= 4;
  } while (p > buf);
  return strdup(p);
}

char *getenv(const char *name) {
  int i;
  for (i = 0; environ[i] != NULL; i++) {
    char *p = strchr(environ[i], '=');
    if (!strncmp(name, environ[i], p - environ[i]))
      return p + 1;
  }
  return NULL;
}

int setenv(const char *name, const char *value, int overwrite) {
  if (name == NULL || value == NULL || name[0] == '\0' ||
      strchr(name, '=') != NULL) {
    errno = EINVAL;
    return -1;
  }

  int i;
  for (i = 0; environ[i] != NULL; i++) {
    char *p = strchr(environ[i], '=');
    if (!strncmp(name, environ[i], p - environ[i])) {
      if (overwrite)
        break;
      else
        return 0;
    }
  }

  char *tmp = malloc(strlen(name) + strlen(value) + 2);
  if (tmp) {
    free(environ[i]);
    environ[i] = tmp;
  } else
    return -1;
  strcpy(environ[i], name);
  strcat(environ[i], "=");
  strcat(environ[i], value);
  environ[i + 1] = NULL;
  return 0;
}

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

void exit(int status) {
  /* TODO: call functions registered with atexit() */
  fcloseall();
  /* TODO: unlink all files created with tmpfile() */
  _exit(status);
  while (1)
    ;
}
