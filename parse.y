%{
#include <stdio.h>
int yylex (void);
void yyerror (char *);
%}

%token VAR RUN QUOTE LITERAL IN OUT PIPE NL

%union {
	char *string;
}

%token <string> WORD
%type <string> line

%%
lines:
     %empty 
     | lines line NL { printf("printing line: %s\n",$2);}
;

line: 
    %empty { printf("found emtpy"); $$ = "empteh"; }
    | line WORD RUN { printf("line word run: %s\n",$2); $$ = $2;}
	;

%%
int main( int argc, char **argv) {
	extern FILE *yyin;
	++argv, --argc; /* skip over program name */
	if ( argc > 0 )
		yyin = fopen( argv[0], "r" );
	else
		yyin = stdin;
	//yylex();
	yyparse();
}

void yyerror(char *s) {
	printf("\nError: %s\n",s);
}

#include "lex.yy.c"
