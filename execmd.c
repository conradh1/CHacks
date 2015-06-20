#include <stdio.h>
int main(void) {
  FILE *fp;
   /* line of data from unix command*/
  char line[256];
  
 // Issue the command
  fp = popen("ls -l","r");

  /* the results should be a single line*/
  while (fgets( line, sizeof line, fp))
    printf(line);

  pclose(fp); //close result set
 
  return 0;
}
