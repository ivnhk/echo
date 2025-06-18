#include <stdio.h>

// TODO: I need to implement the following flags:
// -e
// -E (default)
// --help
// --version

// TODO: warn about unknown flags (or ignore them)
typedef struct {
  int no_newline;
  int first_arg_index;
} echo_flags;

int my_strcmp(const char *s1, const char *s2) {
  while (*s1 && *s2) {
    if (*s1 != *s2) {
      return (unsigned char)*s1 - (unsigned char)*s2;
    }
    s1++;
    s2++;
  }

  return (unsigned char)*s1 - (unsigned char)*s2;
}

void parse_flags(int argc, char *argv[], echo_flags *flags) {
  flags->no_newline = 0;
  flags->first_arg_index = 1;

  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];

    // Handles repeated "-n" like real `echo`
    if (my_strcmp(arg, "-n") == 0) {
      flags->no_newline = 1;
    } else {
      flags->first_arg_index = i;
      return;
    }
  }
}

// TODO: add documentation
// TODO: add quoting, special chars and escape sequence handling (check how echo
// behaves)
int main(int argc, char *argv[]) {
  echo_flags flags;
  parse_flags(argc, argv, &flags);
  int i = flags.first_arg_index;

  while (i < argc) {
    printf("%s", argv[i]);
    if (i != argc - 1) {
      printf(" ");
    }
    i++;
  }
  if (!flags.no_newline) {
    printf("\n");
  }

  return 0;
}
