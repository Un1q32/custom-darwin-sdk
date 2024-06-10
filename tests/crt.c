#include <stdio.h>

int main(int argc, const char *argv[], const char *envp[], const char *apple[]) {
  printf("argc: %d\n", argc);
  int i;
  for (i = 0; i < argc; i++)
    printf("argv[%d]: %s\n", i, argv[i]);
  for (i = 0; envp[i] != NULL; i++)
    printf("envp[%d]: %s\n", i, envp[i]);
  for (i = 0; apple[i] != NULL; i++)
    printf("apple[%d]: %s\n", i, apple[i]);
  return 0;
}
