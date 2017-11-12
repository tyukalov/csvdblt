/* 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/* Igor Tyukalov <tyukalov@bk.ru> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../csvdblt.h"
int
main(int argc, char **argv)
{
	CSVD csvd;
	char buf[100], buf1[100], *str;
	int col;
	char* strs[] = {"Usage 'test database_name line column'", "The delimiter is used ';'","Error in 'csvinit'... Please, check the file name is correct\n"};
	if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h") )
	  {
	    printf("%s\n%s\n", strs[0], strs[1]);
	    exit(0);
	  }
	if(argc != 4)
	  {
	    printf("%s\n", strs[0]);
	    exit(-1);
	  };
	printf("Testing csvselect...\n");
	csvd = csvinit(argv[1], ';');
	if (!csvd)
	  {
	    printf(strs[2]);
	    exit(-1);
	  }
	col = csvselect(csvd,argv[2],argv[3],buf);
	if(!col) printf("%s\n",buf);
	else printf("Error - %d\n", col);
	/* ---------------------------------------------------------------------------- */
	csvclose(csvd);
	/* ---------------------------------------------------------------------------- */
	return 0;
}
