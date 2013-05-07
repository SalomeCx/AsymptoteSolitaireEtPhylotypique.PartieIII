%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "pile_variables.h"
#include "chemin.h"

void yyerror(char* s);
chemin rotation(chemin c , int pt[2] , int a) ;
int verifier_type(char* nom) ;

chemin new_chemin ;

extern int yylineno ;

pile var_points;
pile var_scalaires;
pile var_chemins;

%}

%union {
	int dig ;
	int coordonnee[2] ;
	char str[256] ;
	struct chemin *ch ;
}

%token <dig> ENTIER
%token <str> VARSCAL VARPT VARCHEM
%token INFEGAL SUPEGAL
%token DRAW FILL
%token ROTATE TRANSLATE
%token DT 
%token MOINS PLUS DIVISER FOIS 
%token CYCLE 
%token SCALAIRE POINT CHEMIN


%type <dig> num
%type <coordonnee> coord
%type <ch> chemins

%left MOINS PLUS
%left DIVISER FOIS
%nonassoc NEG

%%

dessin : { var_points = pile_creer(); pile_empiler(var_points) ; var_scalaires = pile_creer(); pile_empiler(var_scalaires) ; var_chemins = pile_creer(); pile_empiler(var_chemins) ;} expr ';' restedessin { pile_detruire(var_points) ; pile_detruire(var_scalaires) ; pile_detruire(var_chemins) ;}
		;

restedessin : expr ';' restedessin
			| 
			;

expr : draw
		| fill
		| declaration
		| initialisation
		;

draw : DRAW chemins { chemin_debut($2) ; int* tmp = chemin_get($2) ; printf("cairo_move_to(cr , %d , %d) ;", tmp[0] , tmp[1] ) ; while(chemin_a_suivant($2)) { chemin_suivant($2) ; tmp = chemin_get($2) ; printf("cairo_line_to(cr , %d , %d) ;", tmp[0] , tmp[1] ) ; } ; printf("cairo_stroke( cr );\n") ; }
		;

fill : FILL chemins { chemin_debut($2) ; int* tmp = chemin_get($2) ; printf("cairo_move_to(cr , %d , %d) ;", tmp[0] , tmp[1] ) ; while(chemin_a_suivant($2)) { chemin_suivant($2) ; tmp = chemin_get($2) ; printf("cairo_line_to(cr , %d , %d) ;", tmp[0] , tmp[1] ) ; } ; chemin_debut($2) ; tmp = chemin_get($2) ; printf("cairo_line_to(cr , %d , %d) ;", tmp[0] , tmp[1] ) ; printf("cairo_fill( cr );\n") ; }
		;

declaration : SCALAIRE VARSCAL { if(verifier_type($2) != 3) { perror("Scalaire déjà déclaré.\n") ; exit(1) ;} pile_ajouter(var_scalaires,$2) ;}
			| POINT VARPT { if(pile_est_present_local(var_points , $2)) { perror("Point déjà déclaré.\n") ; exit(1) ;} pile_ajouter(var_points , $2) ;}
			| CHEMIN VARCHEM { if(pile_est_present_local(var_chemins , $2)) { perror("Chemin déjà déclaré.\n") ; exit(1) ;} pile_ajouter(var_chemins , $2) ;}
			;

initialisation : VARSCAL '=' num { pile_initialiser(var_scalaires , $1 , (void*) $3) ; }
				| VARPT '=' coord {int tmp[2] ; tmp[0] = $3[0] ; tmp[1] = $3[1] ; pile_initialiser(var_points, $1, (void*) tmp ); }
				| VARCHEM '=' chemins { if (pile_est_initialise(var_chemins, $1)) { chemin_detruire(pile_get(var_chemins, $1)); } pile_initialiser(var_chemins, $1, (void*) $3); }
				;

chemins : coord { new_chemin = chemin_creer(); chemin_ajouter(new_chemin, $1); } restechemin { $$ = new_chemin ; }
		| VARCHEM { if( pile_est_initialise(var_points , $1) ) { new_chemin = chemin_creer(); chemin_ajouter(new_chemin, pile_get(var_points , $1)) ; } else if( pile_est_initialise(var_chemins , $1 ) ) { new_chemin = chemin_copie(pile_get(var_chemins , $1 )) ; } else { perror( "Variable non initialise\n") ; exit(1) ; } } restechemin { $$ = new_chemin ; }
		| TRANSLATE '(' chemins ',' coord ')' { $$ = chemin_creer() ; chemin_debut($3) ; int* tmp ; tmp = chemin_get($3) ; tmp[0] += $5[0] ; tmp[1] += $5[1] ; chemin_ajouter($$ , tmp) ; while( chemin_a_suivant($3) ) { chemin_suivant($3) ; int* tmp ; tmp = chemin_get($3) ; tmp[0] += $5[0] ; tmp[1] += $5[1] ; chemin_ajouter($$ , tmp) ; } }
		| ROTATE '(' chemins ',' coord ',' num ')' { $$ = rotation($3 , $5 , $7) ; }
   
restechemin : DT coord { chemin_ajouter(new_chemin, $2); } restechemin 
			| DT CYCLE { chemin_debut(new_chemin) ; chemin_ajouter(new_chemin , chemin_get(new_chemin)) ;} restechemin
			| DT PLUS coord { chemin_fin(new_chemin) ; int* tmp = chemin_get(new_chemin) ; tmp[0] += $3[0] ; tmp[1] += $3[1] ; chemin_ajouter(new_chemin , tmp) ; } restechemin 
			| DT VARCHEM { if( pile_est_initialise(var_chemins , $2 ) ) {chemin_concatener(new_chemin , pile_get(var_chemins , $2 ) ) ;} else { perror( "Variable non initialise\n") ; exit(1) ; } } restechemin 
			|
			;

coord : '(' num ',' num ')' { $$[0] = $2 ; $$[1] = $4 ;}
		| '(' num ':' num ')' { $$[0] = $2 * cos($4) ; $$[1] = $2 * sin($4) ;}
		| VARPT { if( pile_est_initialise( var_points , $1 ) ) { int* tmp = pile_get( var_points , $1 ) ; $$[0] = tmp[0] ; $$[1] = tmp[1] ; } else { perror(" Variable non initialise_n") ; exit(1) ; } }
		| TRANSLATE '(' coord ',' coord ')' { $$[0] = $3[0] + $5[0] ; $$[1] = $3[1] + $5[1] ; }
		;

num : ENTIER {$$ = $1 ;}
	| num MOINS num { $$ = $1 - $3 ;}
	| num PLUS num { $$ = $1 + $3 ;}
	| num DIVISER num { $$ = $1 / $3 ;}
	| num FOIS num { $$ = $1 * $3 ;}
	| '(' num ')' { $$ = $2 ;}
	| MOINS num %prec NEG { $$ = - $2 ; }
	| VARSCAL { if( pile_est_initialise( var_scalaires , $1 ) ) { $$ = (int) pile_get( var_scalaires , $1 ) ; } else { yyerror(" Variable non initialise_n") ; exit(1) ; } }
	;

%%

chemin rotation(chemin c , int pt[2] , int a) {
	float angle = a * M_PI / 180 ;

	chemin new = chemin_creer() ;

	chemin_debut(c) ;

	int new_point[2] ;

	int* old_point = chemin_get(c) ; 

	new_point[0] = cos(angle) * (old_point[0] - pt[0]) - sin(angle) * (old_point[1] - pt[1]) + pt[0] ; 
	new_point[1] = sin(angle) * (old_point[0] - pt[0]) + cos(angle) * (old_point[1] - pt[1]) + pt[1] ; 

	chemin_ajouter(new , new_point) ; 

	while( chemin_a_suivant(c) ) { 
		chemin_suivant(c) ; 

		old_point = chemin_get(c) ;

		new_point[0] = cos(angle) * (old_point[0] - pt[0]) - sin(angle) * (old_point[1] - pt[1]) + pt[0] ; 
		new_point[1] = sin(angle) * (old_point[0] - pt[0]) + cos(angle) * (old_point[1] - pt[1]) + pt[1] ; 

		chemin_ajouter(new , new_point) ; 
	}

	return new ;
}

int verifier_type(char* nom) {
	if(pile_est_present_global(var_scalaires, nom))
		return 0;
	else if(pile_est_present_global(var_points, nom)) 
		return 1 ;
	 else if(pile_est_present_global(var_chemins, nom)) 
	 	return 2; 
	 else {
	 	return 3 ;
	 }
}

void yyerror(char* s){
	fprintf(stderr , "%s : line %d.\n" , s , yylineno ) ;
}



