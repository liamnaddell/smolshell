#ifndef _parsetree_h
#define _parsetree_h
#include <stdio.h>

typedef char *argumentarr[];

typedef struct Node {
	char *cmd;
	argumentarr *args;
} Node;


Node *parse_line(FILE *src);
Node *new_node(char *string, argumentarr *arr);
argumentarr *add_arg(argumentarr *,char *);


#endif
