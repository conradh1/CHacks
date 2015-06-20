#include <time.h>
#include <stdio.h>

#define SIZE 256

int main (void)
{
  char buffer[256];
  time_t curtime;
  struct tm *loctime;

  /* Get the current time. */
  curtime = time (NULL);

  /* Convert it to local time representation. */
  loctime = localtime (&curtime);

  /* Print out the date and time in the standard format. */
  fputs (asctime (loctime), stdout);

  /* Print it out in a nice format. */
  //strftime (buffer, SIZE, "%Y-%m-%d %T\n", loctime);
  strftime (buffer, SIZE, "%Z", loctime);

  printf("%s",&buffer);
  //strftime (buffer, SIZE, "The time is %I:%M %p.\n", loctime);
  fputs (buffer, stdout);

  return 0;
}

