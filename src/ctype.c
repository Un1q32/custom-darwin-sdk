int islower(int c) { return c >= 'a' && c <= 'z'; }

int isupper(int c) { return c >= 'A' && c <= 'Z'; }

int isalpha(int c) { return islower(c) || isupper(c); }

int isdigit(int c) { return c >= '0' && c <= '9'; }

int isalnum(int c) { return isalpha(c) || isdigit(c); }

int isascii(int c) { return c >= 0 && c <= 127; }

int isblank(int c) { return c == ' ' || c == '\t'; }

int isspace(int c) {
  return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
         c == '\v';
}

int isxdigit(int c) {
  return isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

int iscntrl(int c) { return (c >= 0 && c <= 31) || c == 127; }

int isgraph(int c) { return c >= 33 && c <= 126; }

int isprint(int c) { return c >= 32 && c <= 126; }

int ispunct(int c) { return isgraph(c) && !isalnum(c); }
