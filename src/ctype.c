int isdigit(int c) {
    return c >= '0' && c <= '9';
}

int isspace(int c) {
    switch (c) {
        case ' ':
        case '\f':
        case '\n':
        case '\r':
        case '\t':
        case '\v':
            return 1;
        default:
            return 0;
    }
}
