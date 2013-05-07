%{
	#include "draw.tab.h"
	#include "pile_variables.h"
	#include <string.h>
%}

%x SCAL
%x PT
%x CHEM

%option stack
%option yylineno

%%

[[:digit:]]+ {yylval.dig = atoi(yytext) ; return ENTIER ;}
"(" {return '(' ;}
")" {return ')' ;}
"--" {return DT ;}
"," {return ',' ;}
":" {return ':' ;}
";" {return ';' ;}
"<" { return '<' ;}
"<=" { return INFEGAL ; }
">" { return '>' ;}
">=" { return SUPEGAL ; }
"|" { return '|' ;}
"&" { return '&' ;}


"+" {return PLUS ;}
"-" {return MOINS ;}
"*" {return FOIS ;}
"/" {return DIVISER ;}


"cycle" {return CYCLE ;}
"draw" {return DRAW ;}
"fill" {return FILL ;}

"rotate" {return ROTATE ;}
"translate" {return TRANSLATE ;}

"scalaire " {yy_push_state(SCAL); return SCALAIRE ;}
"point " {yy_push_state(PT); return POINT ;}
"chemin " {yy_push_state(CHEM); return CHEMIN ;}

<SCAL>[[:alpha:]_][[:alnum:]_]* { strcpy(yylval.str , yytext) ; yy_pop_state(); return VARSCAL ;}
<PT>[[:alpha:]_][[:alnum:]_]* { strcpy(yylval.str , yytext) ; yy_pop_state(); return VARPT ;}
<CHEM>[[:alpha:]_][[:alnum:]_]* { strcpy(yylval.str , yytext) ; yy_pop_state(); return VARCHEM ;}
[[:alpha:]_][[:alnum:]_]* { strcpy(yylval.str , yytext) ; int tmp = verifier_type(yytext) ; switch(tmp) { case 0 : return VARSCAL ; case 1 : return VARPT ; case 2 : return VARCHEM ; } perror("Variable non declaree ou du mauvais type."); exit(1) ;} 
"=" {return '=' ;}

" "|\n {}

. {return yytext[0] ;}

%%
