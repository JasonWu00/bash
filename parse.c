#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char ** parse_args( char * line ) {
  char ** output = calloc(sizeof(char *), 6);
  //printf("test\n");
  int counter = 0;

  while (counter <= 1) {
    output[counter] = strsep(&line, " ");
    counter++;
  }
  output[5] = NULL;

  //printf("test 2\n");
  return output;
}
