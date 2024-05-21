#include "../include/InputReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *ReadInput() {
  size_t bufferSize = 10;
  char *buffer = malloc(bufferSize);

  if(!buffer) {
    fprintf(stderr, "Memory allocation failed");
    exit(1);
  }

  size_t len = 0;
  int ch;


  while((ch = getchar()) != '\n' && ch != EOF) {
    if(len + 1 >= bufferSize) {
      bufferSize *= 2;
      char * newBuffer = realloc(buffer, bufferSize);

      if(!newBuffer) {
        free(buffer);
        fprintf(stderr, "Memory allocation failed");
        exit(1);
      }

      buffer = newBuffer;
    }
    buffer[len++] = (char)ch;
  }

  buffer[len] = '\0';
  return buffer;
}
