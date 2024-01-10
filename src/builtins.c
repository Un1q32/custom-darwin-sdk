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

int __udivsi3(unsigned int a, unsigned int b) {
    int ret = 0;
    while (a >= b) {
        a -= b;
        ret++;
    }
    return ret;
}

int __umodsi3(unsigned int a, unsigned int b) {
    while (a >= b) {
        a -= b;
    }
    return a;
}
