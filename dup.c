#include <stdio.h>
int main(void) {

  char logfile[] = "error_log";

  FILE *fp = freopen(logfile, "w", stdout);
  close(2); // close stderr
  dup(1); // dup stdout, so stderr now points to stdout
  fprintf(stdout, "Hello there stdout\n");
  fflush(stdout);
  fprintf(stderr, "Hello there stderr\n");
  return 0;
}
