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

    //splits each individual command entered into commandArray
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
    printf("%s\n",commandArray[0]);
    /*
    for(int w = 0; commandArray[w] != NULL; w++) {
      printf("%s\n",commandArray[w]);
    }*/

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
      struct parse_output outstruct;
      outstruct = parse_args(pointer);
      outstruct.lastToken--;

      printf("DEBUG: your cmd: %s, last_token: %i\n", commandArray[q], outstruct.lastToken);
      printf("Command has > sign: %i, 0 if DNE\n", strstr(outstruct.output[outstruct.lastToken-1], more_p) != NULL);
      if (strstr(commandArray[q], cd_p) != NULL) {//input command has a "cd" in it
        chdir(outstruct.output[1]);
        printf("\nWISH > ");
      }
      else if (strstr(commandArray[q], leave_p) != NULL) {//input command is "exit"
        printf("\nWISH > Exiting shell\nThank you for visiting! Come again soon!\n\n");
        exit(0);
      }
      else if (strstr(outstruct.output[outstruct.lastToken-1], more_p) != NULL) {
        printf("DEBUG: value of last token: %s\n", outstruct.output[outstruct.lastToken]);
        int fd_redirectedFile = open(outstruct.output[outstruct.lastToken], O_RDWR);//to see if file exists
        if (fd_redirectedFile == -1) {//if no such file
          //create a file
          printf("DEBUG: file DNE\n");
          printf("DEBUG: fd_redir has this value: %i\n", fd_redirectedFile);
          fd_redirectedFile = open(outstruct.output[outstruct.lastToken], O_RDWR | O_CREAT);
          //int filedesc = open(outstruct.output[outstruct.lastToken],O_RDWR | O_CREAT);
          exit(0);
        }
        else {//file exists
          printf("DEBUG: file exists\n");
          printf("DEBUG: fd_redir has this value: %i\n", fd_redirectedFile);
          //int filedesc = open(outstruct.output[outstruct.lastToken],O_RDWR);
          exit(0);
        }
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
