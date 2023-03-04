#include "stdio.h"

int main(int argc, char** argv) {
  printf("Number of command line arguments: %d\n", argc);

  // print cmd args
  int i;
  printf("Using pointer arithmetics:\n");
  for (i = 0; i < argc; i++) {
    printf("argv[%d]: %s\n", i, *(argv + i));
  }

  return 0;
}