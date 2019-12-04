#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.c"

int main() {
  printf("Opening shell.\n");
  printf("This shell can only take in up to 6 tokens in a single line.\n");
  printf("If you enter a nonexistent command, the shell will not execute it.\n");
  char input[100];
  char ** output;
  int parentPID = getpid();

  while (output[0] != "exit") {//as long as "exit" isn't entered
    printf("\n");
    fgets(input, 100, stdin);
    char *position;
    if ((position = strchr(input, '\n')) != NULL) {
      *position = '\0';
    }
    //gets input and replaces newline with null

    char * pointer = &input;
    output = parse_args(pointer);
    char cd[3] = "cd";
    char leave[5] = "exit";

    if (strstr(input, &cd) != NULL) {//inputted command has a "cd" in it
      printf("Testing, you have entered \"cd\". I will add code later.\n");
      //char ** directory = calloc(sizeof(char *), 6);
      int counter = 1;
      /*while (counter < 6) {
        directory[counter] = output[counter];
      }*/
      //chdir(directory);
    }
    else if (strstr(input, &leave) != NULL) {
      printf("Exiting shell\n");
      exit(0);
    }
    else {
      fork();//child process will execvp and end, parent keeps running
      if (getppid() == parentPID) {
        execvp(output[0], output);
        exit(0); //in case execvp doesn't work out
      }
    }
  }
}
