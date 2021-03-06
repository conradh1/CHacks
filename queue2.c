/*							     */
/* queue.c 						     */
/* Demo of dynamic data structures in C                      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct listelement {
    char     *dataitem;
    int      number;
    char     *dataitem2;
    struct listelement *link;
} listelement;

listelement * AddItem (listelement * listpointer, char *data, int num, char *data2 );
listelement * RemoveItem (listelement * listpointer);
char *get_msg( int num);
void PrintQueue (listelement * listpointer);
void ClearQueue (listelement * listpointer);
void make_list ( void );
void make_list2 ( void );
main () {
    make_list();
    make_list2();
    make_list();
    make_list2();
    make_list2();
}				/* main */

listelement * AddItem (listelement * listpointer, char *data, int num, char *data2 ) {
    listelement * lp = listpointer;

    if (listpointer != NULL) {
	while (listpointer -> link != NULL)
	    listpointer = listpointer -> link;
	listpointer -> link = (struct listelement  *) malloc (sizeof (listelement));
	listpointer = listpointer -> link;
	listpointer -> link = NULL;
	listpointer -> dataitem = data;
        listpointer -> number = num;
        listpointer -> dataitem2 = data2;
	return lp;
    }
    else {
	listpointer = (struct listelement  *) malloc (sizeof (listelement));
	listpointer -> link = NULL;
	listpointer -> dataitem = data;
        listpointer -> number = num;
        listpointer -> dataitem2 = data2;
	return listpointer;
    }
}

void make_list ( void ) {
    listelement *listpointer= NULL; 
    listpointer = AddItem (listpointer, "hello", 13, "again");
    listpointer = AddItem (listpointer, "there", 15, "boo");
    listpointer = AddItem (listpointer, "people", 16, "one moer try with a long string");

    PrintQueue (listpointer);

    ClearQueue (listpointer);
}

void make_list2 ( void ) {
    listelement *listpointer= NULL; 
    listpointer = AddItem (listpointer, "hello2", 13, "again2");
    listpointer = AddItem (listpointer, "there3", 15, "boo2");
    listpointer = AddItem (listpointer, "people4", 16, "one moer try with a long string3");

    PrintQueue (listpointer);

    ClearQueue (listpointer);
}

listelement * RemoveItem (listelement * listpointer) {

    listelement * tempp;
    tempp = listpointer -> link;
    free (listpointer );
    return tempp;
}

void PrintQueue (listelement * listpointer) {

    if (listpointer == NULL)
	printf ("queue is empty!\n");
    else
	while (listpointer != NULL) {
	    printf ("|%s| |%d| |%s|\n", listpointer -> dataitem,
                                        listpointer -> number,
                                        listpointer -> dataitem2);
	    listpointer = listpointer -> link;
	}
    printf ("\n");
}
char *get_msg( int num) {

  char *msg_str = 0;
  switch ( num ) {
    case 1:
      sprintf(msg_str, "hello");
      break;
    case 2: 
      sprintf(msg_str, "there");
      break;
    case 3:
      sprintf(msg_str, "people");
      break;
  }
  return (msg_str);
}
void ClearQueue (listelement * listpointer) {

    while (listpointer != NULL) {
	listpointer = RemoveItem (listpointer);
    }
}
