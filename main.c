#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  char input[100];
  fgets(input, 100, stdin);
  char *position;
  if ((position=strchr(input, '\n')) != NULL) {
    *position = '\0';
  }
}
