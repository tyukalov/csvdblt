#include <stdio.h>
#include "csvdblt.h"
void main()
{
	CSVD csvd;
	char buf[100], buf1[100], *str;
	int col;
	printf("Testing csvselect...\n");
	csvd = csvinit("test.csv", ',');
	col = csvselect(csvd,"0.25","0.5",buf);
	if(!col) printf("%s\n",buf);
	else printf("Error - %d\n", col);
	/* ---------------------------------------------------------------------------- */
	csvclose(csvd);
	/* ---------------------------------------------------------------------------- */
}
