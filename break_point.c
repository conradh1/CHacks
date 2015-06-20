/*							     */
/* break_point.c 						     */
/* Demo of dynamic data structures in C                      */

#include <stdio.h>

void break_point ( int *status, int state );

main () {
  int status = 0;

  break_point(&status, 0);
  break_point(&status, 1);

  return(0);
}				/* main */



void break_point ( int *status, int state ) {
    printf("I am here\n");
    if (state) {
      *status = 1;
      return;
    }
    
    printf("Can I make it?\n");
}



