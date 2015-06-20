#include <math.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  //close(2); // close stderr
  //dup(2); // dup stderr
  //close(1); //close stdout
  FILE *error_file = freopen("error_log", "w", stderr);
  FILE *log_file = freopen("file_log", "w", stdout);
    
  fprintf(stderr, "Hello stderr.\n");
   //fclose(fp);
  printf("write to file!\n");
  fprintf(stdout, "Goodbye stdout\n");

  //fflush(stdout);
  FILE *tp;
  /* line of data from unix command*/
  char command[] = "ww";
  char line[256];
  char output[1256];
  // make output string is clear
  output[0] = '\0';

  // Issue the command
  tp = popen(command,"r");

 /* the results should be a single line*/
 while (fgets( line, sizeof line, tp))
  strcat(output, line);
 //send error case 
 if (strlen(output) == 0) {
   printf("command failed.\n");
 }
 else {
   fprintf(stdout, "Command results: %s\n", output);
 }

 pclose(tp); //close result set


 return 0;
}
