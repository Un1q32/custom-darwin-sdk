#include <ctype.h>
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
  char buf[32];
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
    char *ret2 = malloc(strlen(ret) + 2);
    if (ret2) {
      ret2[0] = '-';
      strcpy(ret2 + 1, ret);
    }
    free(ret);
    return ret2;
  } else
    return utoa(num);
}

char *ftoa(long double num, int percision) {
  char buf[32];
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
  free(int_str);
  *p++ = '.';
  while (percision--) {
    num *= 10;
    *p++ = '0' + (int)num;
    num -= (int)num;
  }
  *p = '\0';
  return strdup(buf);
}

char *utox(unsigned long long num) {
  char buf[32];
  char *p = buf + 31;
  *p = '\0';
  do {
    *--p = "0123456789abcdef"[num & 0xf];
    num >>= 4;
  } while (num);
  return strdup(p);
}

char *utoX(unsigned long long num) {
  char buf[32];
  char *p = buf + 31;
  *p = '\0';
  do {
    *--p = "0123456789ABCDEF"[num & 0xf];
    num >>= 4;
  } while (num);
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

unsigned int random_seed;

void srand(unsigned int seed) { random_seed = seed; }

int rand(void) {
  long hi, lo, x;
  if (random_seed == 0)
    random_seed = 123459876;
  hi = random_seed / 127773;
  lo = random_seed % 127773;
  x = 16807 * lo - 2836 * hi;
  if (x < 0)
    x += 0x7FFFFFFF;
  return (random_seed = x) % ((unsigned long)RAND_MAX + 1);
}

static void (*atexit_funcs[32])(void);
static void (**atexit_funcs_extra)(void);
static int atexit_count = 0;

int atexit(void (*func)(void)) {
  if (atexit_count < 32)
    atexit_funcs[atexit_count++] = func;
  else {
    void (**tmp)(void) =
        realloc(atexit_funcs_extra, (atexit_count - 32 + 1) * sizeof(void *));
    if (tmp == NULL)
      return -1;
    atexit_funcs_extra = tmp;
    atexit_funcs_extra[atexit_count++ - 32] = func;
  }
  return 0;
}

void exit(int status) {
  while (atexit_count > 32)
    atexit_funcs_extra[--atexit_count - 32]();
  while (atexit_count > 0)
    atexit_funcs[--atexit_count]();
  fcloseall();
  /* TODO: unlink all files created with tmpfile() */
  _exit(status);
  while (1)
    ;
}

long double strtold(const char *nptr, char **endptr) {
  long double ret = 0;
  int sign = 1;
  while (isspace(*nptr))
    nptr++;
  if (*nptr == '-') {
    sign = -1;
    nptr++;
  } else if (*nptr == '+')
    nptr++;
  if (nptr[0] == '0' && (nptr[1] == 'x' || nptr[1] == 'X')) {
    nptr += 2;
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
      ret = ret * 16 + digit;
      nptr++;
    }
  } else {
    while (1) {
      int digit;
      if (*nptr >= '0' && *nptr <= '9')
        digit = *nptr - '0';
      else
        break;
      ret = ret * 10 + digit;
      nptr++;
    }
  }
  if (*nptr == '.') {
    long double factor = 0.1;
    nptr++;
    while (1) {
      int digit;
      if (*nptr >= '0' && *nptr <= '9')
        digit = *nptr - '0';
      else
        break;
      ret += factor * digit;
      factor *= 0.1;
      nptr++;
    }
  }
  if (endptr)
    *endptr = (char *)nptr;
  return sign * ret;
}

double strtod(const char *nptr, char **endptr) {
  return (double)strtold(nptr, endptr);
}

float strtof(const char *nptr, char **endptr) {
  return (float)strtold(nptr, endptr);
}

int abs(int num) {
  if (num < 0)
    return -num;
  else
    return num;
}

void abort(void) { exit(1); }
