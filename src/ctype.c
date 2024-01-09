int isascii(int c) {
    return c >= 0 && c <= 127;
}

int isblank(int c) {
    return c == ' ' || c == '\t';
}

int isdigit(int c) {
    return c >= '0' && c <= '9';
}

int islower(int c) {
    return c >= 'a' && c <= 'z';
}

int isspace(int c) {
    return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v';
}

int isupper(int c) {
    return c >= 'A' && c <= 'Z';
}
