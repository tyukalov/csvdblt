/* definition for csvdblt
   
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

#define SPACE		' '
#define DQUOTE		'"'
#define TRUE		0x1
#define FALSE		0x0
#define MAX_STRING_SIZE	1024
typedef struct {
	FILE* 	fd;
	char	delimiter;
} *CSVD;

/* Error codes */
#define NOT_FOUND	0x1
#define DATABASE_ERROR	0x2

/* Prototypes of functions */
int csvselect(CSVD csvd, char *str, char *col, char *buf);
/* TODO Implement! 
int csvupdate(CSVD csvd, char *str, char *col, char *buf);
int csvchkdb(CSVD csvd); */
CSVD csvinit(char *name, char delimiter);
void csvclose(CSVD csvd);
