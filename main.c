#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parse.h"

int main() {
  printf("Opening shell.\n");
  printf("This shell can only take in up to 6 tokens in a single line.\n");
  printf("If you enter a nonexistent command, the shell will not execute it.\n");
  printf("Type \"exit\" to close the shell.\n");
  char input[100];
  char ** output;
  int parentPID = getpid();

  while (1) {//as long as "exit" isn't entered
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
      chdir(output[1]);
    }
    else if (strstr(input, &leave) != NULL) {
      printf("Exiting shell\n");
      exit(0);
    }
    else {
      int execute_return;
      fork();//child process will execvp and end, parent keeps running
      if (getppid() == parentPID) {
        execute_return = execvp(output[0], output);
      }
      //printf("%i\n", execute_return);
      if(execute_return < 0) {
        printf("Error encountered: %i (%s)\n", errno, strerror(errno));
      }
      exit(0); //if user types in invalid command
    }
  }
}
