#include <stdio.h>
#include "csvdblt.h"
void main(int argc, char **argv)
{
	CSVD csvd;
	char buf[100], buf1[100], *str;
	int col;
	if(argc != 4)
	  {
	    printf("Usage 'test database_name line column'\n");
	    return;
	  }
	printf("Testing csvselect...\n");
	csvd = csvinit(argv[1], ';');
	col = csvselect(csvd,argv[2],argv[3],buf);
	if(!col) printf("%s\n",buf);
	else printf("Error - %d\n", col);
	/* ---------------------------------------------------------------------------- */
	csvclose(csvd);
	/* ---------------------------------------------------------------------------- */
}
