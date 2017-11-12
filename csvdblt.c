/* csvdblt - a miniature library for accessing data in .csv format
   
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

#include <stdlib.h>
#include <string.h>
#include "csvdblt.h"


#define INVERT(A) { if(A) A=FALSE; else A=TRUE;}
#define RETPOS(A,B) fseek(A,B,SEEK_SET)
#define BEGIN(A) fseek(A, 0, SEEK_SET)


/* Internal functions */
static int numcol(CSVD csvd);
static int numstr(CSVD csvd);
static int strnumcol(char*, char);
static int selectcol(char *src, char *dst, int numcol, char delimiter);
static int findcol(CSVD csvd, char *ptrn);
static int findsubstr(char *str, char *pattern, char delimiter, int length, int flag);
static int ifdelimiter(char *str, char delimiter);
static int ifstrname(char *str, char *ptrn, char delimiter);
static void dellinebreak(char *str);

/* Returns the number of columns in a row */
static int 
strnumcol(char *str, char delimiter)
{
	int result=0;
	int len=0;
	int flag = FALSE;
	char ch;
	while(ch=*str++)
	{
		len++;
		if(ch==delimiter)
		{
			if(flag) continue;
			result++;
		}
		else if (ch==DQUOTE) INVERT(flag);
	}
	if(len) result++;
	return result;
}

/* Copies from src column at the number numcol in dst */
static int 
selectcol(char *src, char *dst, int numcol, char delimiter)
{
	char ch;
	int count 	= 0;
	int flag	= FALSE;
	if(numcol)		/* Если столбец не нулевой */
	{
		while(ch=*src++)
		{
			if(ch==DQUOTE) INVERT(flag);
			if((ch==delimiter) && (!flag))
			{
				count++;
				if(count == numcol) break;
			};
		};
	}
	if(count == numcol)
	{
		while(ch=*src++)
		{
			if(ch==DQUOTE)
			{
				INVERT(flag);
				continue;
			};
			if(ch==delimiter && !flag) break;
			else *dst++=ch;
		};
		*dst = 0;
		return count;
	}
	return -1;
}

/* Return the number of column containing ptrn */
static int 
findcol(CSVD csvd, char *ptrn)
{
	char buf[MAX_STRING_SIZE], *ptr;
	int result 	= 0;
	char ch;
	int len, flag;
	long oldpos;
	ptr		= buf;
	len		= strlen(ptrn);
	if(!len) return -1;
	oldpos 		= ftell(csvd->fd);
	BEGIN(csvd->fd);
	if(fgets(ptr, MAX_STRING_SIZE, csvd->fd))
	{
		dellinebreak(ptr);
		ptr 		= buf;
		flag		= ifdelimiter(ptrn, csvd->delimiter);
		/* Частный случай - проверка нулевого столбца */
		if(findsubstr(ptr, ptrn, csvd->delimiter, len, flag)) 
		{
			RETPOS(csvd->fd, oldpos);
			return result;
		}
		while(ch=*ptr)
		{
			if(ch==csvd->delimiter)
			{
				result++;
				if(findsubstr((ptr+1), ptrn, csvd->delimiter, len, flag)) 
				{
					RETPOS(csvd->fd, oldpos);
					return result;
				}
			};
			ptr++;
		};
		RETPOS(csvd->fd, oldpos);
		return -1;
	}
}

static int 
findsubstr(char *ptr, char *ptrn, char delimiter, int len, int flag)
{
	if(flag && *ptr==DQUOTE && *(ptr + len + 1))
	{
		if(!strncmp((ptr+1), ptrn, len)) return TRUE;
	}
	if(!flag && (*(ptr + len)==delimiter || *(ptr+len)==0))
	{
		if(!strncmp(ptr, ptrn, len)) return TRUE;
	}
	return FALSE;
}

static int 
ifdelimiter(char *str, char delimiter)
{
	char ch;
	while(ch = *str++)
	{
		if(ch == delimiter) return TRUE;
	}
	return FALSE;
}

/* Compares the first column with the sample */
static int 
ifstrname(char *str, char *ptrn, char delimiter)
{
	int flag, len;
	flag	= ifdelimiter(ptrn, delimiter);
	len	= strlen(ptrn);
	return findsubstr(str, ptrn, delimiter, len, flag);
}

/* Replaces the newline character with a null */
static void 
dellinebreak(char *str)
{
	char ch;
	while(ch=*str)
	{
		if(ch=='\n' || ch=='\r')
		{
			*str = 0;
			break;
		}
		str++;
	}
}


/* Interface Functions */

CSVD 
csvinit(char *name, char dlmtr)
{
	FILE* 	hd;
	CSVD	result;
	hd			= fopen(name, "rw");
	if(!hd) return NULL;
	result			= (CSVD)malloc(sizeof(CSVD));
	result -> fd		= hd;
	result -> delimiter	= dlmtr;
	return result;
}

void 
csvclose(CSVD csvd)
{
	fclose(csvd->fd);
	free(csvd);
	csvd = NULL;
}

int 
csvselect(CSVD csvd, char *str, char *col, char *dst)
{
	long oldpos;
	int column;
	char line[MAX_STRING_SIZE], ch;
	oldpos		= ftell(csvd->fd);
	BEGIN(csvd->fd);
	column		= findcol(csvd, col);
	if(column==-1)
	{
		RETPOS(csvd->fd, oldpos);
		return DATABASE_ERROR;
	}
	while(fgets(line, MAX_STRING_SIZE, csvd->fd))
	{
		dellinebreak(line);
		if(ifstrname(line, str, csvd->delimiter))
		{
			if(selectcol(line, dst, column, csvd->delimiter) == -1)
			{
				RETPOS(csvd->fd, oldpos);
				return DATABASE_ERROR;
			}
			else
			{
				RETPOS(csvd->fd, oldpos);
				return 0;
			}
		}
	}
	RETPOS(csvd->fd, oldpos);
	return NOT_FOUND;
}

/* ========================================================================================== */
