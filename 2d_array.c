/* illustration of dynamically allocated 2D array */
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int i; /* general purpose variable used for loop index */
  int j; /* general purpose variable used for loop index */

  char **a;     /* this is the array name */
  int size_x; /* this variable will be used for the first  dimension */
  int size_y; /* this variable will be used for the second dimension */

  /* suppose we want an array of int: a[5][3] */
  size_x = 5;
  size_y = 3;

  /*  allocate storage for an array of pointers */
  a = malloc(size_x * sizeof(char *));

  /* for each pointer, allocate storage for an array of ints */
  for (i = 0; i < size_x; i++) {
    a[i] = malloc(size_y * sizeof(char));
  }

  /* just for kicks, show the addresses (note: not all sequential) */
  /* assign an arbitrary value to each element        */
  for (i = 0; i < size_x; i++) {
    for (j = 0; j < size_y; j++) {
      printf("&a[%d][%d] = %p\n", i, j, &a[i][j]); /* show the addresses */
      a[i][j] = atoi(i * size_y + j); /* just some unique number for each element */
    }
    printf ("\n");
  }

  /* now show the contents that were assigned */
  for (i = 0; i < size_x; i++) {
    for (j = 0; j < size_y; j++) {
      printf("a[%d][%d] = %2c\n", i, j, a[i][j]);
    }
    printf ("\n");
  }

  /* now for each pointer, free its array of ints */
  for (i = 0; i < size_y; i++) {
    free(a[i]);
  }
  /* now free the array of pointers */
  free(a);

  return 0;
}
