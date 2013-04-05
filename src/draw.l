%{
	#include "draw.tab.h"
%}

%%

[[:digit:]]+ {yylval.dig = atoi(yytext) ; return ENTIER ;}
"(" { return '(' ;}
")" { return ')' ;}
"--" { return DT ;}
"," { return ',' ;}
":" { return ':' ;}
";" { return ';' ;}
\n { return '\n' ;}

"+"|"-" {return MOINSPLUS ;}
"*"|"/" {return DIVISERFOIS ;}


"draw" {return DRAW ;}

" " {}

.|\n { return yytext[0] ;}

%%