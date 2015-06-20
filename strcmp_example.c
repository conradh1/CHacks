/* strncmp example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[][25] = { "Error: bad syntax" , "No Error" , "Hello", "Error: wrong type." };
  int n;
  puts ("Looking for R2 astromech droids...");
  for (n=0 ; n < 4 ; n++)
    printf("String: |%s| |%d|\n",str[n], strncmp (str[n],"Error:", 6));
  return 0;
}
