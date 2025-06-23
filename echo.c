#include <stdio.h>
#include <stdlib.h>
// TODO: I need to implement the following flags:
// -e
// -E (default)
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

void print_help() {
  printf("Usage: echo [SHORT-OPTION]... [STRING]...\n");
  printf("   or: echo LONG-OPTION\n");
  printf("Echo the STRING(s) to standard output.\n");
  printf("-n        do not output the trailing newline\n");
  printf("-e        enable interpretation of backslash escapes\n");
  printf("-E        disable interpretation of backslash escapes (default)\n");
  printf("--help    display this help and exit\n");
  printf("--version output version information and exist\n");
}

void parse_flags(int argc, char *argv[], echo_flags *flags) {
  flags->no_newline = 0;
  flags->first_arg_index = 1;

  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];

    // Handles repeated "-n" like real `echo`
    if (my_strcmp(arg, "-n") == 0) {
      flags->no_newline = 1;
    } else if (my_strcmp(arg, "--help") == 0) {
      print_help();
      exit(0);
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
