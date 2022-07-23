%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int yylex (void);
void yyerror (char *);
typedef struct Node {
	char *cmd;
} Node;

Node *mkNode(char *string) {
	Node *n = calloc(1,sizeof(Node));
	n->cmd = string;
	return n;
}
Node *parse_tree = NULL;
%}

%token VAR RUN QUOTE LITERAL IN OUT PIPE NL


%union {
	char *string;
	Node *node;
}

%token <string> WORD
%type <node> line

%%

line: 
    %empty { $$ = mkNode("");}
    | line WORD RUN NL { $$ = mkNode($2);parse_tree=$$; YYACCEPT;}
    ;
;

%%
int main( int argc, char **argv) {
	extern FILE *yyin;
	++argv, --argc; /* skip over program name */
	if ( argc > 0 )
		yyin = fopen(argv[0], "r" );
	else
		yyin = stdin;
	//yylex();
	yyparse();
	printf("%s\n",parse_tree->cmd);
}

void yyerror(char *s) {
	printf("\nError: %s\n",s);
}

#include "lex.yy.c"
