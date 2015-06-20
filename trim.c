#include <stdio.h>
#include <string.h>
#include <assert.h>

char *trim_right( char *org_str, char trim_char );
char *trim_left( char *org_str, char trim_char );
//...
int main(int argc, char *argv[])
{
char under[] = "__12345_____";
char space[] = " trim space  "; 
printf("Before trim: |%s|\n", under);
printf("Before right trim: |%s|\n", space);
//under = trim_left(under, '_');
//space = trim_right(space, ' ');
printf("After left trim: |%s|\n", trim_left(under, '_'));
printf("After right trim: |%s|\n", trim_right(space, ' '));

//printf("\nAfter left trim: |%s|\n", trim_left(under, '_'));
//printf("\nAfter right space trim: |%s|\n", trim_right(space, ' '));
//printf("\nAfter right trim: |%s|\n", trim_right(under, '_'));
//printf("\nAfter left space trim: |%s|\n", trim_left(space,' '));
printf("\nOriginals |%s| |%s|\n", under,space);
}


/** **********************************************************
/* Trims all characters that equal trim_char left of a string
*************************************************************/
char *trim_left( char *org_str, char trim_char )
{
  char *pszBOS = 0;

  // Set pointer to character before terminating NULL
  pszBOS = org_str;

  // iterate backwards until non ' ' is found
  while(*pszBOS == trim_char)
    *pszBOS++;

  return pszBOS;

} //trim_left

/**
/* Trims all characters that equal trim_char right of a string
*/
char *trim_right( char *org_str, char trim_char )
{
  char *pszEOS = 0;

  // Set pointer to character before terminating NULL
  pszEOS = org_str + strlen( org_str ) - 1;

  // iterate backwards until non char is found
  while( (pszEOS >= org_str) && (*pszEOS == trim_char) ) {
    //fprintf(stderr, "char at 0x%x: %c\n", pszEOS, *pszEOS);
    *(pszEOS--) = '\0';
  }

  return org_str;
} //trim_right
