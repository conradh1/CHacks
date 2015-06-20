#include <math.h>
#include <string.h>
#include <stdio.h>

char mask[4800][4800];
char header[2880], extra[16000];
int scratch, nother;

main()
{
    int ifile, nbytes, ix0, iy0, ix1, iy1, ix, iy, iopt;
    float slope, y;
    
    for(ix = 0; ix < 4800; ix++) {
        for(iy = 0; iy < 4800; iy++) {
            mask[iy][ix] = 0;
        }
    }
    while(1) {
        printf(" Enter type of defect to create\n");
        printf(" 0: None, write out the image\n");
        printf(" 1: column defect\n");
        printf(" 2: rectangular defect\n");
        printf(" 3: linear defect\n");
        printf(" >> ");
        scanf("%d", &iopt);
        if(iopt == 0) {
            ifile = creat("mask.fits",0777);
            fitshd(ifile,8,4800,4800,1.0,0.0);
            nbytes = 4800*4800;
            write(ifile,mask,nbytes);
            close(ifile);
            break;
        }
        else if(iopt == 1) {
            printf("Enter number for bad column: ");
            scanf("%d", &iy0);
            printf("Enter the width: ");
            scanf("%d", &ix0);
            iy0--;
            int w;
            for(ix = 0; ix < 4800; ix++) {
              for(w= 0; w < ix0; w++) {
                mask[ix][iy0+w] = 1;
              }
            }
        }
        else if(iopt == 2) {
            printf("Enter pixel of 1st corner ");
            scanf("%d %d", &ix0, &iy0);
            printf("Enter pixel of 2nd corner ");
            scanf("%d %d", &ix1, &iy1);
            if(ix1 < ix0) {
                ix = ix0;
                ix0 = ix1;
                ix1 = ix;
            }
            if(iy1 < iy0) {
                iy = iy0;
                iy0 = iy1;
                iy1 = iy;
            }
            ix0--;
            iy0--;
            for(ix = ix0; ix < ix1; ix++) {
                for(iy = iy0; iy < iy1; iy++) {
                    mask[iy][ix] = 1;
                }
            }
        }
        else if(iopt == 3) {
            printf("Enter iy0, slope ");
            scanf("%d %f", &iy0, &slope);
            iy0--;
            for(ix = 0; ix < 4800; ix++) {
                y = (float) iy0 + slope * (float) ix;
                iy = (int) y;
                if((iy >= 0) && (iy < 4800)) {
                    mask[iy][ix] = 1;
                }
            }
        }
    }
}

/*	setup a minimal fits header for output on file	and send it to disk	*/


fitshd(file,nbits,ncol,nrow,bscale,bzero)
int file, nbits, ncol, nrow;
double bscale, bzero;
{
	extern char header[2880], extra[16000];
	extern int scratch, nother;
	char *p;
	int i, ncard, nextra;
	
/*	fill the header with blanks	*/

	for(i = 0; i < 2880; i++)
		header[i] = ' ';


/*	SIMPLE keyword			*/

	p = &header[0];
	strcpy(p, "SIMPLE  =                    T  /");
	
/*	BITPIX keyword			*/
	
	p = &header[80];
	sprintf(p,"BITPIX  = %20d  /",nbits);
	
/*	NAXIS keyword			*/

	p = &header[160];
	strcpy(p, "NAXIS   =                    2  /");

/*	NAXIS1 keyword			*/

	p = &header[240];
	sprintf(p, "NAXIS1  = %20d  /",ncol);
	
/*	NAXIS 2 keyword			*/

	p = &header[320];
	sprintf(p, "NAXIS2  = %20d  /",nrow);
	
	ncard = 5;

/*	if it's not floating point fits output BZERO and BSCALE keywords	*/

	if(nbits != -32) {
		
		p += 80;
		sprintf(p, "BSCALE  = %20.7e  /",bscale);
		p += 80;
		sprintf(p, "BZERO   = %20.7e  /",bzero);
		ncard += 2;
		}

/*	eliminate any nulls that manged to get into the header 	*/

	for(i = 0; i < 2880; i++)
		if(header[i] == 0)
			header[i] = ' ';

/*	now write out the card images that have been generated up to
	this point							*/
	
	write(file, header, 80*ncard);
	
/*	now read back any additional header cards that have been saved
	from the input fits files and add them to the output record	*/

	if(nother > 0) {
		p = &extra[0];
		while(nother--) {
			write(file,p, 80);
			p += 80;
			ncard++;
			}
		}
	
/*	now add the END to finish off the record		*/
	
	sprintf(header,"END");
	for(i = 3; i < 80; i++)
		header[i] = ' ';
	write(file, header, 80);
	ncard++;

	if((ncard % 36) == 0)
		return;
		
/*	now write pad the header record		*/

	for(i = 0; i < 2880; i++)
		header[i] = ' ';

	if((ncard / 36) < 0)	
		write(file, header, 80*(36 - ncard));
	else {
		nextra = 36*(1 + (ncard/36)) - ncard;
		write(file, header, 80*nextra);
		}

}
