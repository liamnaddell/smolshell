#ifndef _parsetree_h
#define _parsetree_h
#include <stdio.h>

//an array of pointers, terminated with null;
typedef char *argumentarr[];

typedef struct Node {
	char *cmd;
	argumentarr *args;
} Node;

typedef struct args {
	char *arg;
	struct args *next;
} Args;


Node *parse_line(FILE *src);
Node *new_node(char *string, argumentarr *arr);
Args *add_arg(Args *,char *);
argumentarr *to_argarray(char *cmd, Args *a);


#endif
