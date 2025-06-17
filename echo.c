#include <stdio.h>

// TODO: if second argument is "-n":
// 1. Start iterating from the third argument
// 2. Omit printing the newline
int main(int argc, char *argv[]) {
  int i = 1;
  while (i < argc) {
    printf("%s ", argv[i]);
    i++;
  }
  printf("\n");

  return 0;
}
