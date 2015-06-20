#include <stdio.h>
#include <string.h>

int main()
{
   float pi = 3.141596;
   char halfpie[30];
   char *str_ptr = "Hello";
   pi/=2;
 
   sprintf(halfpie, "%f", pi);
   printf("Here is the result: %s\n", halfpie);
   printf("%s\n", str_ptr);
   str_ptr = "Goodbye";
   printf("%s\n", str_ptr);
   str_ptr = halfpie;
   printf("%s\n", str_ptr);
   sprintf(str_ptr, "PI %f", pi);
   printf("%s\n", str_ptr);

   return 0;
}
