#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"

void main() {
  char input[100] = "";

  while (strcmp(input, "exit") != 0) {
    fgets(input, 100, stdin);
    char *position;
    if ((position = strchr(input, "\n")) != NULL) {
      *position = "\0";
    }
  }
  exit(0); //input is equal to "exit", closing the shell
}
