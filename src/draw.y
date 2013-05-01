%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tableaux.h"

void yyerror(char* s);

int premier[2] ;

tableau var_points;
tableau var_scalaires;
tableau var_chemins;

%}

%union {
	int dig ;
	int coordonnee[2] ;
	char* str ;
}

%token <dig> ENTIER
%token <str> VARIABLE
%token DRAW FILL 
%token DT 
%token MOINS PLUS DIVISER FOIS 
%token CYCLE 
%token SCALAIRE POINT CHEMIN

%type <dig> num
%type <coordonnee> coord

%left MOINS PLUS
%left DIVISER FOIS

%%

dessin : expr ';' '\n' restedessin { var_points = creer_tableau(); var_scalaires = creer_tableau(); var_chemins = creer_tableau(); } 
		| expr ';'
		;

restedessin : expr ';' '\n' restedessin
			| expr ';'
			;

expr : draw
		| fill
		| declaration
		| initialisation
		;

draw : DRAW chemin { printf("cairo_stroke( cr );\n") ; }
		;

fill : FILL chemin { printf("cairo_line_to ( cr ,%d ,%d);\ncairo_set_line_width ( cr , 10.0);\ncairo_fill( cr );\n" , premier[0] , premier[1] ) ; }
		;

declaration : SCALAIRE VARIABLE {}
			| POINT VARIABLE {}
			| CHEMIN VARIABLE {}
			| SCALAIRE VARIABLE '=' ENTIER {}
			| POINT VARIABLE '=' coord {}
			| CHEMIN VARIABLE '=' chemin {}
			;

initialisation : VARIABLE '=' ENTIER {}
				| VARIABLE '=' chemin {}
				;

chemin : coord { printf("cairo_move_to ( cr ,%d ,%d);\n",$1[0],$1[1]); premier[0] = $1[0] ; premier[1] = $1[1] ; } restechemin
		;

restechemin : DT coord { printf("cairo_line_to( cr ,%d ,%d);\ncairo_set_line_width( cr , 10.0);\n" , $2[0] , $2[1] ) ; } restechemin 
			| DT CYCLE { printf("cairo_line_to( cr ,%d ,%d);\ncairo_set_line_width( cr , 10.0);\n" , premier[0] , premier[1] ) ; } restechemin
			| DT PLUS coord { printf("cairo_rel_line_to( cr ,%d ,%d);\ncairo_set_line_width( cr , 10.0);\n" , $3[0] , $3[1] ) ; } restechemin 
			| 
			;

coord : '(' num ',' num ')' { $$[0] = $2 ; $$[1] = $4 ;}
		| '(' num ':' num ')' { $$[0] = $2 * cos($4) ; $$[1] = $2 * sin($4) ;}
		;

num : ENTIER {$$ = $1 ;}
	| num MOINS num { $$ = $1 - $3 ;}
	| num PLUS num { $$ = $1 + $3 ;}
	| num DIVISER num { $$ = $1 / $3 ;}
	| num FOIS num { $$ = $1 * $3 ;}
	| '(' num ')' { $$ = $2 ;}
	;

%%

void yyerror(char* s){
	perror(s);
	perror("\n");
}



