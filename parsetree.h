#ifndef _parsetree_h
#define _parsetree_h
#include <stdio.h>

typedef struct Node {
	char *cmd;
} Node;

Node *parse_line(FILE *src);
Node *mkNode(char *string);

#endif
