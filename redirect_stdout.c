/* freopen example: redirecting stdout */
#include <stdio.h>

int main ()
{
  FILE *fp = freopen("myfile.txt", "w", stdout);
  printf("Directed to file\n");
  fclose(fp);
  stdout = fdopen(1, "w");
  printf("Back on screen!!\n");
}
