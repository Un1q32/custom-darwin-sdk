#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }
    
    char *env = "TEST_ENV";
    setenv(env, argv[1], 1);
    printf("%s=%s\n", env, getenv(env));
    return 0;
}
