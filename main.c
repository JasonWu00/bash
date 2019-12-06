#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include "parse.h"

int main() {
  printf("Opening shell.\n");
  printf("This shell can only take in up to 6 tokens in a single line.\n");
  printf("If you enter a nonexistent command, the shell will not execute it.\n");
  printf("Type \"exit\" to close the shell.\n");
  char input[100];
  char ** output;
  int parentPID = getpid();
  printf("WISH > ");

  while (1) {//as long as "exit" isn't entered
    fgets(input, 100, stdin);
    char *position;
    if ((position = strchr(input, '\n')) != NULL) {
      *position = '\0';
    }
    //gets input and replaces newline with null

    if(strchr(input,';') != NULL) {
      char *inptr = input;
      char *indcmd;
      char *commandArray[100];
      int q = 0;
      while((indcmd = strsep(&inptr,";")) != NULL) {
        commandArray[q] = indcmd;
        q++;
      }
    }

    char * pointer = &input;
    output = parse_args(pointer);
    char cd[3] = "cd";
    char leave[5] = "exit";
    const char *cd_p = &cd;
    const char *leave_p = &leave;

    if (strstr(input, cd_p) != NULL) {//inputted command has a "cd" in it
      chdir(output[1]);
      printf("\nWISH > ");
    }
    else if (strstr(input, leave_p) != NULL) {
      printf("\nWISH > Exiting shell\n");
      exit(0);
    }
    else {
      fork();//child process will execvp and end, parent keeps running
      if (getpid() == parentPID) {
        printf("\n");
      }
      wait(NULL);
      if (getppid() == parentPID) {
        printf("WISH > ");
        int execute_return;
        execute_return = execvp(output[0], output);
        if (execute_return < 0) {
          printf("Error encountered: %i (%s)\n", errno, strerror(errno));
        }
        exit(0);
      }
      printf("\nWISH > ");
    }
  }
}
