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

Args *add_arg(Args *a,char *n) {
	Args *b = (Args *)calloc(1,sizeof(Args));
	b->arg=n;
	if (b == NULL) {
		perror("calloc :(");
		exit(1);
	}
	if (a == NULL) {
		return b;
	} else {
		Args *cur = a;
		while (cur->next != NULL) {
			cur=cur->next;
		}
		cur->next = b;
		return a;
	}

}

unsigned argsize(Args *a) {
	int i=0;
	while (a != NULL) {
		a=a->next;
		i++;
	}
	return i;
}

argumentarr *to_argarray(char *cmd, Args *a) {
	unsigned size = argsize(a);
	//we need 2 extra pointers, one for NULL, one for cmd
	//make sure to dup cmd to avoid double free
	
	argumentarr *args = (argumentarr *) calloc(size+2,sizeof(char *));
	(*args)[0] = strdup(cmd);

	int i;
	for (i = 1; i < size+1; i++) {
		(*args)[i]=a->arg;
		a=a->next;
	}
	(*args)[i] = NULL;
	return args;
}
