%{
	#include "draw.tab.h"
%}

%%

[[:digit:]]+ {yylval.dig = atoi(yytext) ; return ENTIER ;}
"(" {return '(' ;}
")" {return ')' ;}
"--" {return DT ;}
"," {return ',' ;}
":" {return ':' ;}
";" {return ';' ;}
\n {return '\n' ;}

"+" {return PLUS ;}
"-" {return MOINS ;}
"*" {return FOIS ;}
"/" {return DIVISER ;}


"cycle" {return CYCLE ;}
"draw" {return DRAW ;}
"fill" {return FILL ;}

"scalaire" {return SCALAIRE ;}
"point" {return POINT ;}
"chemin" {return CHEMIN ;}

[[:alpha:]_][[:alphanum:]_]* {yylval.str = yytext ; return VARIABLE ;}

" " {}

.|\n {return yytext[0] ;}

%%