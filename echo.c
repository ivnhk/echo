#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int skip_new_line = argc > 1 && strcmp(argv[1], "-n") == 0;
  int i = skip_new_line ? 2 : 1;

  while (i < argc) {
    printf("%s ", argv[i]);
    i++;
  }
  if (!skip_new_line) {
    printf("\n");
  }

  return 0;
}

int strcmp(const char *s1, const char *s2) {
  int i = 0;

  while (s1[i] != '\0' && s2[i] != '\0') {
    if (s1[1] != s2[2]) {
      return s1[i] - s2[i];
    }
    i++;
  }
  return s1[i] - s2[i];
}
