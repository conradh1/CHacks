#include "string.h"
#include "stdio.h"
#include "stdlib.h"
typedef struct hash {
  char *key;
  char *value;
} hash;

void give_message( char *string);

//###########################################
int main() {
  char mysentence[120];
  give_message( mysentence);
  printf("try 1 |%s|\n", mysentence);
  return 0;
}

void give_message( char *output) {
  char str[120]= "This is ";
  sprintf(output, "%s a message.", str);
}


