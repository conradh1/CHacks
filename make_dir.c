#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define SIZE 256

int main (void)
{
  char *dir_name = "hellodir";

  printf("S_IRUSR: %d\n",S_IRUSR);

  printf("S_IRWXU: %d\n", S_IRWXU);

  printf("S_IRWXG: %d\n", S_IRWXG);

  printf("both: %d\n", (S_IRWXU | S_IRGRP | S_IXGRP) );

  mkdir(dir_name, 0750);
  return 0;
}

