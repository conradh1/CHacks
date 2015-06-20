#include "string.h"
#include "stdio.h"
#include "stdlib.h"
typedef struct hash {
  char *key;
  char *value;
} hash;

int give_number( void );
void give_null ( void );
//###########################################
int main() {
  printf("number %d\n", give_number());
  give_null();
     
  return 0;
}

int give_number( void  ) {
   return(1);
   return(0); 
}

void give_null( void ) {
  printf("before return\n");
  return;
  printf("after return\n");
}



