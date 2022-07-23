%{ 
#include <stdio.h>
#include <string.h>
#include "parse.tab.h"
%}
%%
$[a-zA-Z0-9]+  { return VAR; }
[a-zA-Z0-9]+ { yylval.string=strdup(yytext);return WORD; }
[$] { return RUN; }
[\"] { return QUOTE; }
[\'] { return LITERAL; }
[<] { return IN; }
[>] { return OUT; }
[|] { return PIPE; }
[\n] { return NL; } 
[ \t]+	{ /*ignored */ }
%%
int yywrap() {};
