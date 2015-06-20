#include <math.h>
#include <string.h>
#include <stdio.h>


	

int main(int argc, char *argv[])
{
    char str[100];
    //strcpy(str,"Hello");
    char four= 'f';
    char four2;
    int number = 4;
    int number2;
    FILE *fp = fopen("Binary.txt", "wb");
    fwrite(&number,sizeof(int),1,fp);
    fwrite(&four, sizeof(char), 1, fp);
    //fwrite(str, sizeof(str[0]), sizeof(str)/sizeof(str[0]), fp);
    printf("wrote binary file\n");
    fclose(fp);
    fp = fopen("Binary.txt", "rb");
    printf("reading binary file\n");
    fread(&number2,sizeof(int),1,fp);
    fread(&four2,sizeof(char),1,fp);
    //fread(str, sizeof(str[0]), sizeof(str)/sizeof(str[0]), fp);
    printf("%d\n",number2);
    printf("%c\n",four2);
    //printf("%s\n",str);
    return 0;
}
