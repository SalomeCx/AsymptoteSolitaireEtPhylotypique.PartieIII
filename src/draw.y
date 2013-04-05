%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(char* s);

%}

%union {
	int dig ;
}

%token <dig> ENTIER
%token DRAW DT MOINSPLUS DIVISERFOIS

%left MOINSPLUS
%left DIVISERFOIS

%%

dessin : expr ';' \n' restedessin {}
		| expr ';'
		;

restedessin : expr ';' '\n' restedessin
			| 
			;

expr : draw
		;

draw : DRAW optdraw

optdraw : coord resteoptdraw
		;

resteoptdraw : DT coord resteoptdraw
			|
			;

coord : '(' num ',' num ')'
		| '(' num ':' num ')'
		;

num : ENTIER
	| num MOINSPLUS num
	| num DIVISERFOIS num
	| '(' num ')'

%%

void yyerror(char* s){
	printf("%s\n",s);
}

int main() {
	yyparse();
	return EXIT_SUCCESS;
}