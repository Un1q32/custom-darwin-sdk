int __modsi3(int a, int b) {
    while (a >= b) {
        a -= b;
    }
    return a;
}

int __divsi3(int a, int b) {
    int ret = 0;
    while (a >= b) {
        a -= b;
        ret++;
    }
    return ret;
}
