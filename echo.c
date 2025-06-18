#include <stdio.h>

int strcmp(const char *s1, const char *s2) {
  while (*s1 && *s2) {
    if (*s1 != *s2) {
      return (unsigned char)*s1 - (unsigned char)*s2;
    }
    s1++;
    s2++;
  }

  return (unsigned char)*s1 - (unsigned char)*s2;
}

// TODO: add documentation
// TODO: add quoting, special chars and escape sequence handling (check how echo
// behaves)
int main(int argc, char *argv[]) {
  int no_newline = argc > 1 && strcmp(argv[1], "-n") == 0;
  int i = no_newline ? 2 : 1;

  while (i < argc) {
    printf("%s", argv[i]);
    if (i != argc - 1) {
      printf(" ");
    }
    i++;
  }
  if (!no_newline) {
    printf("\n");
  }

  return 0;
}
