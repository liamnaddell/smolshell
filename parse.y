%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parsetree.h"

int yylex (void);

void yyerror (Node **n, char *);

%}

%token VAR RUN QUOTE LITERAL IN OUT PIPE NL
%parse-param {Node **n}

%union {
	char *string;
	Node *node;
	Args *args;
}

%token <string> WORD
%type <node> line
%type <args> args

%%

line: 
    %empty { $$ = NULL;}
    | line args WORD RUN NL { $$ = new_node($3,to_argarray($3,$2));*n=$$; YYACCEPT;}
    ;

args:
    %empty {$$ = NULL;}
    | args WORD {$$ = add_arg($$,$2);}
;

%%

#include "parsetree.h"

Node *parse_line(FILE *src) {
	extern FILE *yyin;
	//yylex();
	yyin=src;
	Node *n;
	yyparse(&n);
	return n;
}

void yyerror(Node **n, char *s) {
	//printf("\nError: %s\n",s);
}

#include "lex.yy.c"
