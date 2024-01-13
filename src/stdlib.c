#include <ctype.h>
#include <unistd.h>

long strtol(const char *nptr, char **endptr, int base) {
    long ret = 0;
    int sign = 1;
    while (isspace(*nptr)) nptr++;
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
        *endptr = (char *) nptr;
    return sign * ret;
}

int atoi(const char *nptr) {
    return (int)strtol(nptr, NULL, 10);
}

char *utoa(unsigned long long num) {
    static char buf[32];
    char *p = buf + 31;
    *p = '\0';
    do {
        *--p = '0' + num % 10;
        num /= 10;
    } while (num);
    return p;
}

char *itoa(long long num) {
    if (num < 0) {
        char *ret = utoa(-num);
        char *p = ret - 1;
        *p = '-';
        return p;
    } else
        return utoa(num);
}

char *ftoa(long double num) {
    int ipart = (int)num;
    long double fpart = num - (long double)ipart;
    char *ret = itoa(ipart);
    char *p = ret;
    while (*p) p++;
    *p++ = '.';
    int i;
    for (i = 0; i < 6; i++) {
        fpart *= 10;
        int digit = (int)fpart;
        *p++ = '0' + digit;
        fpart -= (long double)digit;
    }
    *p = '\0';
    return ret;
}

void exit(int status) {
    /* TODO: call functions registered with atexit() */
    /* fcloseall(); */
    /* TODO: unlink all files created with tmpfile() */
    _exit(status);
    while (1) {}
}
