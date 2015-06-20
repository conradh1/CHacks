#include <stdio.h>
#include <stdlib.h>

int main ()
{
  int i;
  char str[256];

  printf ("Enter a long number: ");
  scanf ("%s", str );
  i = atol ( str );
  printf ("i = %d, its double = %d\n", i, i * 2 );
  str[0] = '\0';
  i = atol ( str );
  printf("i = %d \n",i);
 
  return 0;
}
