#include <stdio.h>
#include <stdlib.h>
#define ROWS 5
#define COLS 5

int main (void)
{
  int i = 0;
  int j = 0;

  int *array1D = malloc( ROWS * sizeof(int ));
  int **array2D = malloc( ROWS * sizeof(int *));


  for(i = 0; i < ROWS; i++)
	array2D[i] = malloc( COLS * sizeof(int));


  printf("Assigning 1D array\n");
  for ( i = 0; i < ROWS; i++) {
    array1D[i] = i;
  }
  
  printf("Printing 1D arrray\n");
   for ( i = 0; i < ROWS; i++) {
    printf("%d, ", array1D[i]);
  }
  printf("\n");

  printf("Assigning 2D arrray\n");

  for ( i = 0; i < ROWS; i++) {
    for ( j = 0; j < COLS; j++) {
      array2D[i][j] = i+j;
    }
  }
 
  for ( i = 0; i < ROWS; i++) {
    for ( j = 0; j < COLS; j++) {
      printf("{%d }", array2D[i][j]);
    }
    printf("\n");
  }
  
  return 0;
}

