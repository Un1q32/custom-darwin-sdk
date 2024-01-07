char *strcat(char *dest, const char *src) {
    char *p = dest;
    while (*p) p++;
    while (*src) *p++ = *src++;
    *p = '\0';
    return dest;
}

char *strcpy(char *dest, const char *src) {
    char *ret = dest;
    while ((*dest++ = *src++) != '\0')
        ;
    return ret;
}

char *stpcpy(char *dest, const char *src) {
    while ((*dest++ = *src++) != '\0')
        ;
    return dest - 1;
}
