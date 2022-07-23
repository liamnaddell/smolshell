#include "parsetree.h"
#include <stdlib.h>
#include<string.h>

Node *new_node(char *string, argumentarr *arr) {
	Node *n = calloc(1,sizeof(Node));
	if (n == NULL) {
		perror("calloc: ");
		exit(1);
	}
	n->cmd = string;
	n->args = arr;
	return n;
}

argumentarr *add_arg(argumentarr *oldarr,char *n) {
	if (oldarr == NULL) {
		argumentarr *newarr = (argumentarr*) calloc(strlen(n)*1,sizeof(char));
		return newarr;
	}
	return NULL;

}
