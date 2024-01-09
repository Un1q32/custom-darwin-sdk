#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char **array = NULL;
    int array_size = 0;
    int i;
    for (i = 1; i < argc; i++)
        if (argv[i][0] == 'a') {
            array = realloc(array, ++array_size * sizeof(char *));
            array[array_size - 1] = argv[i];
        }

    for (i = 0; i < array_size; i++)
        puts(array[i]);

    return 0;
}
