#include "parsetree.h"
#include <stdlib.h>

Node *mkNode(char *string) {
	Node *n = calloc(1,sizeof(Node));
	if (n == NULL) {
		perror("calloc: ");
		exit(1);
	}
	n->cmd = string;
	return n;
}
