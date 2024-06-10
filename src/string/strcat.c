char *strcat(char *dst, const char *src) {
  char *p = dst;
  while (*p)
    p++;
  while (*src)
    *p++ = *src++;
  *p = '\0';
  return dst;
}
