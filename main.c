#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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

    int numCommands;
    char *inptr = input;//pointer to input string
    char *commandArray[100];
    if(strchr(input,';') != NULL) {//check if semicolon in input
      char *indcmd;
      int q = 0;
      while((indcmd = strsep(&inptr,";")) != NULL) {
        commandArray[q] = indcmd;
        q++;
      }
      numCommands = q;
    }
    else {
      commandArray[0] = inptr;
      numCommands = 1;
    }

    char cd[3] = "cd";
    char leave[5] = "exit";
    char lessthan[2] = "<";
    char morethan[2] = ">";

    const char *cd_p = &cd;
    const char *leave_p = &leave;
    const char *less_p = &lessthan;
    const char *more_p = &morethan;
    for(int q = 0; q < numCommands; q++) {//for every command entered
	  char * pointer = commandArray[q];
      int last_token = 0;
      int * last_p = &last_token;
      struct parse_output outstruct;
      outstruct = parse_args(pointer, last_p);
      printf("DEBUG: your cmd: %s, last_token: %i\n", commandArray[q], last_token);
      if (strstr(commandArray[q], cd_p) != NULL) {//input command has a "cd" in it
        chdir(outstruct.output[1]);
        printf("\nWISH > ");
      }
      else if (strstr(commandArray[q], leave_p) != NULL) {//input command is "exit"
        printf("\nWISH > Exiting shell\nThank you for visiting! Come again soon!\n\n");
        exit(0);
      }
      else {
        if (strstr(commandArray[q], less_p) != NULL) {
          if (access(outstruct.output[outstruct.lastToken], F_OK) == -1) {//file does not exist
            //create a file
            int filedesc = open(outstruct.output[outstruct.lastToken],O_RDWR | O_CREAT);
          }
          return 0;
        }
        fork();//child process will execvp and end, parent keeps running
        if (getpid() == parentPID) {
          printf("\n");
        }
        wait(NULL);
        if (getppid() == parentPID) {
          //printf("WISH > ");
          int execute_return;
          execute_return = execvp(outstruct.output[0], outstruct.output);
          if (execute_return < 0) {
            printf("Error encountered: %i (%s)\n", errno, strerror(errno));
          }
          exit(0);
        }
      }
    }
    printf("\nWISH > ");
  }
}
