#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "parsetree.h"
#include "parse.tab.h"

const unsigned E_NOCMD = 1;

char *which(char *cmd, char *PATH[], int pathlen) {
	//absolute or relative path specified
	if (strchr(cmd,'/') != NULL) {
		return strdup(cmd);
	}
	char *dest;
	for (int i = 0; i < pathlen; i++) {
		dest = calloc(strlen(PATH[i])+strlen(cmd),sizeof(char));
		strcat(dest,PATH[i]);
		strcat(dest,cmd);
		struct stat statbuf;
		if (stat(dest,&statbuf) == 0 && (S_ISREG(statbuf.st_mode) || S_ISLNK(statbuf.st_mode))) {
			//valid file
			return dest;
		} else {
			printf("which: %s did not match\n", dest);
			free(dest);
		}
	}
	return NULL;
}

int run_builtin(Node *n) {
	if (strcmp(n->cmd,"which") == 0) {
		puts("whiching");
		return 0;
	}
	return 1;
}

int run_cmd(Node *n, int *exit_status, char *PATH[], int pathlen) {
	int r = fork();
	if (r < 0) {
		perror("fork :(");
	} else if (r == 0) {
		//child
		if (run_builtin(n) != 0) {
			char *full_cmd=which(n->cmd,PATH,pathlen);
			if (full_cmd == NULL) {
				return E_NOCMD;
			}
			int res = execl(full_cmd,full_cmd,NULL);
			if (res == -1) {
				return E_NOCMD;
			} else {
				puts("unreachable main.c");
				//program should have exited by now
			}
		}
	} else {
		//parent
		return 0;
	}
}

int main(int argc, char **argv) {
	++argv, --argc; /* skip over program name */
	FILE *src;
	if ( argc > 0 )
		src=fopen(argv[0], "r" );
	else
		src=stdin;

	char *PATH[]={"/bin/","/usr/bin/"};

	while (true) {
		Node *n = parse_line(src);

		if (n == NULL) {
			fprintf(stderr,"invalid command");
		}

		//async function, can't access exit_status until child exits;
		int exit_status;
		int result = run_cmd(n,&exit_status,PATH,2);
		if (result != 0) {
			fprintf(stderr,"error with %d\n", result);
		} else {
			wait(NULL);
			printf("command exited with %d\n",exit_status);
		}
	}
}
