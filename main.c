#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.c"

int main() {
  printf("Opening shell.\n");
  printf("This shell can only take in up to 6 tokens in a single line.\n");
  char input[100];
  char ** output;

  while (output[0] != "exit") {//as long as "exit" isn't entered
    printf("WInSHell >");
    fgets(input, 100, stdin);
    char *position;
    if ((position = strchr(input, '\n')) != NULL) {
      *position = '\0';
    }
    //gets input and replaces newline with null

    char * pointer = &input;
    output = parse_args(pointer);
    char cd[3] = "cd";

    if (strstr(input, &cd) != NULL) {//inputted command has a "cd" in it
      printf("Testing, you have entered \"cd\". I will add code later.\n");
      char ** directory;
      int counter = 0;
      //while ()
    }
    else {
      printf("You entered something else. I will add code later.\n");
      execvp(output[0], output);
    }
  }
  printf("Exiting\n");
  exit(0); //input is equal to "exit", closing the shell
}
