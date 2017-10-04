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
int csvupdate(CSVD csvd, char *str, char *col, char *buf);
int csvchkdb(CSVD csvd);
CSVD csvinit(char *name, char delimiter);
void csvclose(CSVD csvd);
