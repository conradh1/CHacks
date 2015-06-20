#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

inline

char *strtoupper(char *org_str) {
  int i;

  for(i=0; i < strlen( org_str); i++)  {
    org_str[i] = toupper(org_str[i]);
  }
  return org_str;
} //strtoupperhar 

main(int argc, char *argv[]) {
   char str[25] = "makeupper";

   printf("before upper:|%s|\n", str);
   strtoupper( str);
   printf("after uppper:|%s|\n", str); 
   
   
}
