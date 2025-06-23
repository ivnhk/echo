#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: warn about unknown flags (and ignore them)
typedef struct {
  int no_newline;
  int first_arg_index;
  int interpret_escapes;
} echo_flags;

int strcmp_learn(const char *s1, const char *s2) {
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
  printf("--version output version information and exit\n");
}

void print_version() {
  printf("echo (clone) 0.1\n");
  printf("written by Ivan Hrekov\n");
}

// TODO: refactor flag parsing to something a bit more sophisticated
// 1. Detect if it's a flag. If it is - then parse it, and act accordingly
// 2. If not, then notify user about it.
// Q: can there be multiple flags combined like -eEn
void parse_flags(int argc, char *argv[], echo_flags *flags) {
  flags->no_newline = 0;
  flags->first_arg_index = 1;
  flags->interpret_escapes = 0; // default -E behavior

  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];

    // Handles repeated "-n" like real `echo`
    if (strcmp_learn(arg, "-n") == 0) {
      flags->no_newline = 1;
    } else if (strcmp_learn(arg, "--help") == 0) {
      print_help();
      exit(0);
    } else if (strcmp_learn(arg, "--version") == 0) {
      print_version();
      exit(0);
    } else if (strcmp_learn(arg, "-e") == 0) {
      flags->interpret_escapes = 1;
    } else if (strcmp_learn(arg, "-E") == 0) {
      flags->interpret_escapes = 0;
    } else {
      flags->first_arg_index = i;
      return;
    }
  }
}

int hex_to_int(char c) {
  if (c >= '0' && c <= '9')
    return c - '0';
  else if (c >= 'a' && c <= 'f')
    return 10 + (c - 'a');
  else if (c >= 'A' && c <= 'F')
    return 10 + (c - 'A');
  else
    return -1; // Invalid hex digit
}

void print_escaped(const char *s) {
  while (*s) {
    if (*s == '\\') {
      s++;
      if (!*s) {
        exit(0);
      }
      switch (*s) {
      case 'a':
        putchar('\a');
        break;
      case 'b':
        putchar('\b');
        break;
      case 'c':
        exit(0); // I see it as a correct behavior
        break;
      case 'e':
        putchar('\x1B');
        break;
      case 'f':
        putchar('\f');
        break;
      case 'n':
        putchar('\n');
        break;
      case 'r':
        putchar('\r');
        break;
      case 't':
        putchar('\t');
        break;
      case 'v':
        putchar('\v');
        break;
      case '\\':
        putchar('\\');
        break;
      case '0': {
        int val = 0, count = 0;
        s++;
        while (*s >= '0' && *s <= '7' && count < 3) {
          val = val * 8 + (*s - '0');
          s++;
          count++;
        }
        putchar(val);
        s--; // Q: should it be here?
      } break;
      case 'x': {
        int val = 0, count = 0;
        s++;
        while (count < 2 && isxdigit(*s)) {
          val = val * 16 + hex_to_int(*s);
          s++;
          count++;
        }
        putchar(val);
      } break;
      default:
        putchar('\\');
        putchar(*s);
        break;
      }
    } else {
      putchar(*s);
    }
    s++;
  }
}

// Q: should I add examples in order to show how to use the thing
int main(int argc, char *argv[]) {
  if (argc == 1) {
    return 0;
  }
  echo_flags flags;
  parse_flags(argc, argv, &flags);

  int i = flags.first_arg_index;
  while (i < argc) {
    const char *arg = argv[i];
    if (flags.interpret_escapes) {
      print_escaped(arg);
    } else {
      printf("%s", arg);
    }
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
