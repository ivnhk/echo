#include <stdio.h>

// TODO: re-write using pointers
int strcmp(const char *s1, const char *s2) {
  int i = 0; // TODO: is this ok?

  // NOTE: (unsigned char) cast is used to guarantee consistent comparison
  // across platforms. Otherwise, may give wrong results with extended ASCII or
  // non-ASCII chars
  while (s1[i] != '\0' && s2[i] != '\0') {
    if ((unsigned char)s1[i] != (unsigned char)s2[i]) {
      return (unsigned char)s1[i] - (unsigned char)s2[i];
    }
    i++;
  }
  return (unsigned char)s1[i] - (unsigned char)s2[i];
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
