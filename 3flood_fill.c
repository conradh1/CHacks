#include <math.h>
#include <string.h>
#include <stdio.h>


//the floodfill algorithms
void floodFill8Stack(int x, int y, int newColor, int oldColor);
void findEdges(int x, int y, int newColor, int oldColor);
void printMatrix(); 
int pop(int *x, int *y);
int push(int x, int y);
int beenThere(int x, int y);
void emptyStack();
//the auxiliary functions
void clearScreenBuffer();

//the stack
#define stackSize 167
int stack[stackSize];
int stackPointer;
int width = 8;
int height = 8;


//the graphics buffer
#define screenW 8
#define screenH 8
int screenBuffer[screenW][screenH] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0, 0, 1, 1, 1, 1, 0,
                                       0, 0, 0, 1, 1, 1, 1, 0,
                                       0, 0, 0, 1, 1, 1, 1, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0 };


struct BadPixel
{
  int type;
  int coords[1];
  char shape[20];
};	

int main(int argc, char *argv[])
{

    printMatrix();
    int i, j;

    //floodFillScanlineStack(5, 5, 0, 1);
    for (i = 0; i < screenW; i++                      ) {
      for (j = 0; j < screenH; j++) {
        if (screenBuffer[i][j] != 0)
        {
           printf("############# found bad region {%d, %d}################\n",i,j);
           //findEdges(i, j, 0, screenBuffer[i][j]);
           floodFill8Stack(i, j, 0, screenBuffer[i][j]);
        }
      } 
    }
    printMatrix();
    printf("Done!\n");
    return 0;
}
//###############################################################
void floodFill8Stack(int x, int y, int newColor, int oldColor)
{
    if(newColor == oldColor) return; //avoid infinite loop
    emptyStack();
    char direction= 'C';

    printf("##########First Edge: {%d, %d} #############\n", x, y);
    if(!push(x, y)) return;
    int found = 0; 
    while(pop(&x, &y))
    {
        screenBuffer[x][y] = newColor; 
        printf("scanning {%d, %d}\n", x, y);
        found = 0;
        if(y + 1 < height && screenBuffer[x][y + 1] == oldColor && !found)
        {
            printf("RIGHT %d, %d\n", x , y);
            if(!push(x, y + 1)) return;
            if (direction != 'R')
              printf("found edge\n");
            direction = 'R';
            found = 1;
        }
        if(x + 1 < width && screenBuffer[x + 1][y] == oldColor && !found)
        {
            printf("DOWN %d, %d\n", x , y);
            if(!push(x + 1, y)) return;
            if (direction != 'D')
              printf("found edge\n");
            direction = 'D';
            found = 1;
        }
        if(y - 1 >= 0 && screenBuffer[x][y - 1] == oldColor && !found) 
        {
            printf("LEFT %d, %d\n", x , y);
            if(!push(x, y - 1)) return;
           if (direction != 'L')
              printf("found edge\n");
            direction = 'L';
            found = 1;
        }
        if(x - 1 >= 0 && screenBuffer[x - 1][y] == oldColor  && !found)
        {
            printf("UP %d, %d\n", x , y);
            if(!push(x - 1, y)) return;
            if (direction != 'U')
              printf("found edge\n");
            direction = 'U';
            found = 1;
        }
        /*if(x + 1 < width && y + 1 < height && screenBuffer[x + 1][y + 1] == oldColor)
        {
            printf("DOWN RIGHT %d, %d\n", x , y);
            if(!push(x + 1, y + 1)) return;
        }
        if(x + 1 < width && y - 1 >= 0 && screenBuffer[x + 1][y - 1] == oldColor)
        {
            printf("DOWN LEFT %d, %d\n", x , y);
            if(!push(x + 1, y - 1)) return;
        } 
        if(x - 1 >= 0 && y + 1 < height && screenBuffer[x - 1][y + 1] == oldColor)
        {
            printf("UP RIGHT %d, %d\n", x , y);
            if(!push(x - 1, y + 1)) return;
        }
        if(x - 1 >= 0 && y - 1 >= 0 && screenBuffer[x - 1][y - 1] == oldColor)
        {
            printf("UP LEFT %d, %d\n", x , y);
            if(!push(x - 1, y - 1)) return;
        }*/
        
    } //while
}
//###############################################################
void findEdges(int x, int y, int newColor, int oldColor)
{
  //assign first positions
  int last_direction= 0;
  emptyStack();
  
  //do first case
  //go right 
  if (y + 1 != newColor) 
    y++;
  //go down
  else if ( x + 1 != newColor)
    x++;
  //go left
  else if ( y - 1 != newColor)
    y--;
  //go up
  else if (x -1 != newColor)
    x--;
  
  
  while (!beenThere(x, y))
  {
    printf("hello\n");
    //go right
    if (y + 1 != newColor) 
      y++;
    //go down
    else if ( x + 1 != newColor)       
      x++;
    //go left
    else if ( y - 1 != newColor) 
      y--;
    //go up
    else if (x -1 != newColor)
      x--;
    else
      printf("found edge {%d %d}\n", x, y);
    push(x, y);
  }
} //findEdges
//*****************************************
int beenThere(int x, int y)
{
  int stackNumber = height * x + y;
  int i = 0;
  for (i = 0; i <= stackPointer; i++)
  {
    if (stack[i] == stackNumber)
      return 1;
  }
  return 0;
} //beenThere

//###############################################################
void printMatrix()
{
  int i, j;
  for (i = 0; i < height; i++)
  {
    for (j = 0; j < width; j++)
    {
      printf("%d, ", screenBuffer[i][j]);
    }
    printf("\n");
  }
}
////////////////////////////////////////////////////////////////////////////////
//Stack Functions                                                             //
////////////////////////////////////////////////////////////////////////////////

int pop(int *x, int *y)
{
    if(stackPointer > 0)
    {
        int p = stack[stackPointer];
        *x = p / height;
        *y = p % height;
        stackPointer--;
        return 1;
    }    
    else
    {
        return 0;
    }   
}   
 
int push(int x, int y)
{
    if(stackPointer < stackSize - 1)
    {
        stackPointer++;
        stack[stackPointer] = height * x + y;
        return 1;
    }    
    else
    {
        return 0;
    }   
}    

void emptyStack()
{
    int x, y;
    while(pop(&x, &y));
}

