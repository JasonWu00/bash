#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include "parse.h"

char ** parse_args( char * line ) {
  char ** output = calloc(sizeof(char *), 20);
  //printf("test\n");
  int counter = 0;

  while (line != NULL) {
    output[counter] = strsep(&line, " ");
    counter++;
  }
  output[19] = NULL;

  //printf("test 2\n");
  return output;
}

char ** parse_args_semicolon( char * line ) {
  char ** output = calloc(sizeof(char *), 20);
  //printf("test\n");
  int counter = 0;

  while (line != NULL) {
    output[counter] = strsep(&line, ";");
    counter++;
  }
  output[19] = NULL;

  //printf("test 2\n");
  return output;
}

void run_command(char input[100], char ** output) {
    char cd[3] = "cd";
    char leave[5] = "exit";
    const char *cd_p = &cd;
    const char *leave_p = &leave;
    int parentPID = getpid();

    if (strstr(input, cd_p) != NULL) {//input command has a "cd" in it
      chdir(output[1]);
    }
    else if (strstr(input, leave_p) != NULL) {//input command is "exit"
      printf("\nWISH > Exiting shell\nThank you for visiting! Come again soon!\n");
      exit(0);
    }
    else {
      fork();//child process will execvp and end, parent keeps running
      if (getpid() == parentPID) {
        printf("\n");
      }
      wait(NULL);
      if (getppid() == parentPID) {
        //printf("WISH > ");
        int execute_return;
        execute_return = execvp(output[0], output);
        if (execute_return < 0) {
          printf("Error encountered: %i (%s)\n", errno, strerror(errno));
        }
        exit(0);
      }
    }
    printf("\nWISH > ");
}
