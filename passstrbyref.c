#include "string.h"
#include "stdio.h"
#include "stdlib.h"
typedef struct hash {
  char *key;
  char *value;
} hash;

char *give_hello( void );
void add_goodbye( char *string); 
void add_hello( char *string); 
void a_num( int *num);
char *give_goodbye ( char *ptr_messg );
int assign_hash ( hash *myhash );
//###########################################
int main() {
  char *mysentence;
  //mysentence = give_hello();
  //printf("Give hello: %s\n", mysentence);
  //mysentence = give_goodbye( mysentence );
  //printf("give goodbye: |%s|\n", mysentence);
  *mysentence = 0;

  int number = 0;
  a_num( &number);
  printf("Number is %d\n", number); 
  //char *string2;
  //here or in string_concat? or both?
  //add_goodbye( string2 );

  //printf("add goodbye: %s\n", string2);
  //add_hello( string2);
  //printf("add hello: %s\n", string2);
  
  struct hash myhash;      
  int results = assign_hash( &myhash );
  printf("hash: %s %s \n",myhash.key, myhash.value);
   
  return 0;
}

char *give_hello( void  ) {
   //write in string something, need a realloc?
   return("hello");
}

void a_num( int *num) {
  (*num)++;
  printf("num is %d\n", *num);
}
char *give_goodbye ( char *ptr_messg ) {
  sprintf(ptr_messg, "give goodbye");
  return(ptr_messg);
}
void add_goodbye( char *string) {
  *string = 0;
  char *test = "GOODBYE";
  sprintf(string, test);
}

void add_hello( char *string) {
  char *test = "HELLO";
  sprintf(string, test);
}


int assign_hash ( hash *myhash ) {
  myhash->key = "hello";
  myhash->value = "goodbye";
  return (1);
}


