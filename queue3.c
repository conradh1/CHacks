/*							     */
/* queue.c 						     */
/* Demo of dynamic data structures in C                      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_BUFFER 256
#define FILE_NAME_BUFFER 256
#define COLUMN_BUFFER 256
#define CHECKSUM_SIZE 256
#define ROW_BUFFER 10000
#define PATH_BUFFER 1000

/**
 * a structure for everything to be written to the CSV 
 * ready file
 */
typedef struct csv_ready_entry {
  /*@{*/
  char filename[FILE_NAME_BUFFER]; /**<  Name of the csv file. **/
  long  rows; /**<  The number of rows in the file. **/
  char tablename[TABLE_BUFFER]; /**<  the name of the coresponding database table. **/
  char checksum[CHECKSUM_SIZE]; /**<  The checksum of the CSV file **/
  struct csv_ready_entry *next_csv_ready_entry; /**<  pointer to the next csv entry structure. **/
  /*@{*/
} csv_ready_entry;


static csv_ready_entry *add_new_csv_ready_entry (csv_ready_entry *new_csv_ready_entry, 
                                                 char *filename, 
                                                 long rows, 
                                                 char * tablename, 
                                                 char *checksum);
static csv_ready_entry *remove_csv_ready_entry( csv_ready_entry *csv_ready_entry_obj);
void clear_csv_ready_list( csv_ready_entry *csv_ready_entry_obj);
void print_csv_ready(csv_ready_entry *csv_ready_list);
csv_ready_entry *csv_ready_list = NULL;

 char *hello = "hello";
    char *goodbye = "goodbye";

char csv_file_name[FILE_NAME_BUFFER]; //name of csv file
char table_name[TABLE_BUFFER]; //table name
char md5sum[TABLE_BUFFER];

main () {
    sprintf(csv_file_name, "1 %s", hello);
    strcat(table_name, "table");
    strcat(md5sum, "md5sum");
    csv_ready_list = add_new_csv_ready_entry( csv_ready_list, 
                                       csv_file_name, 
                                       1,
                                       table_name, 
                                       md5sum);
    *csv_file_name = 0;
    sprintf(csv_file_name, "1 %s", hello);

    csv_ready_list = add_new_csv_ready_entry( csv_ready_list, 
                                       csv_file_name, 
                                       1,
                                       table_name, 
                                       md5sum);

    print_csv_ready( csv_ready_list);
    clear_csv_ready_list( csv_ready_list);

    csv_ready_list = add_new_csv_ready_entry( csv_ready_list, 
                                       csv_file_name, 
                                       1,
                                       table_name, 
                                       md5sum);

    *csv_file_name = 0;
    sprintf(csv_file_name, "1 %s", hello);

    csv_ready_list = add_new_csv_ready_entry( csv_ready_list, 
                                       csv_file_name, 
                                       1,
                                       table_name, 
                                       md5sum);

    print_csv_ready( csv_ready_list);
    clear_csv_ready_list( csv_ready_list);
} /* main */

/** ********************************************************************
 * This function returns a group of csv_ready_entry structures
 ***********************************************************************/
static csv_ready_entry *add_new_csv_ready_entry (csv_ready_entry *new_csv_ready_entry, 
                                                 char *filename, 
                                                 long rows, 
                                                 char *tablename,
                                                 char *checksum) {

    csv_ready_entry *tmp_csv_ready_entry = new_csv_ready_entry;

    //find last node in structure list
    if (new_csv_ready_entry != NULL) {
	while (new_csv_ready_entry -> next_csv_ready_entry != NULL) {
	    new_csv_ready_entry = new_csv_ready_entry -> next_csv_ready_entry;
        }
	new_csv_ready_entry -> next_csv_ready_entry = (struct csv_ready_entry  *) malloc (sizeof (csv_ready_entry));
	new_csv_ready_entry = new_csv_ready_entry -> next_csv_ready_entry;
	new_csv_ready_entry -> next_csv_ready_entry = NULL;
        //assign details from FITS file
	strcpy(new_csv_ready_entry -> filename, filename);
        new_csv_ready_entry -> rows = rows;
        strcpy(new_csv_ready_entry -> tablename, tablename);
        strcpy(new_csv_ready_entry -> checksum, checksum);
	return tmp_csv_ready_entry;
    }
    //add first stucture
    else {
	new_csv_ready_entry = (struct csv_ready_entry  *) malloc (sizeof (csv_ready_entry));
	new_csv_ready_entry -> next_csv_ready_entry = NULL;
	//assign details in XML file
        strcpy(new_csv_ready_entry -> filename, filename);
        new_csv_ready_entry -> rows = rows;
        strcpy(new_csv_ready_entry -> tablename, tablename);
        strcpy(new_csv_ready_entry -> checksum, checksum);
	return new_csv_ready_entry;
    }
} //add_new_csv_ready_entry
/** ***********************************************************
 * Removes a single element structure in a CSV Ready Entry List
***************************************************************/
static csv_ready_entry *remove_csv_ready_entry( csv_ready_entry *csv_ready_entry_obj) {

    csv_ready_entry *csv_ready_temp;
    csv_ready_temp = csv_ready_entry_obj -> next_csv_ready_entry;
    free (csv_ready_entry_obj);
    return csv_ready_temp;
}

/** ***********************************************************
 * Clears element structures in a CSV Ready Entry List
***************************************************************/
void clear_csv_ready_list( csv_ready_entry *csv_ready_entry_obj) {
    while ( csv_ready_entry_obj != NULL) {
         printf("Delete %s, %ld, %s, %s\n", 
              csv_ready_entry_obj -> filename, 
              csv_ready_entry_obj -> rows,
              csv_ready_entry_obj -> tablename,
              csv_ready_entry_obj -> checksum);
	csv_ready_entry_obj = remove_csv_ready_entry( csv_ready_entry_obj);
    }
}
/** ***************************************************************/
void print_csv_ready(csv_ready_entry *csv_ready_list) {
  if ( csv_ready_list == NULL) {
    printf("CSV Ready entries are empty.");
    return;
  }
  else {
    printf("########### CSV Ready List #############\n");
    while ( csv_ready_list != NULL) {
      printf("%s, %ld, %s, %s\n", 
              csv_ready_list -> filename, 
              csv_ready_list -> rows,
              csv_ready_list -> tablename,
              csv_ready_list -> checksum);

      csv_ready_list = csv_ready_list -> next_csv_ready_entry;
    } //while
  } //else
} //print_csv_ready
