#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

inline
char *trim_left_n(char *str, unsigned n) {
   int i, len;

   len = strlen(str);

   for (i = n; i < len; ++i) {
       str[i-n] = str[i];
   }

   str[len-n] = '\0';

   return str;
}

char *trim_left(char *str, char trim) {
   char *p;
   unsigned n = 0;

   p = str;

   while (*(p++) == trim) { // safe unless *str = trim = '\0'
       ++n;
   }

   fprintf(stderr, "n=%d\n", n);

   return trim_left_n(str, n);
}

int main(int argc, char *argv[]) {
   char *instr, c;

   assert(argc == 3);

   instr = strdup(argv[1]);
   c = argv[2][0];

   assert(c != 0x0 || *instr != 0x0);

   printf("%s ltrim '%c' -> ", instr, c);

   trim_left(instr, c);

   printf("%s\n", instr);

   free(instr);
}
