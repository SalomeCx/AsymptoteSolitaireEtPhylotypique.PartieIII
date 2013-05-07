#include <stdlib.h>

#include "chemin.h"

typedef struct cell *cell ;

struct cell {
	cell next ;
	int point[2] ;
} ;

struct chemin {
	cell debut ;
	cell curr ;
	cell last ;
} ;

chemin chemin_creer(){
	chemin new = malloc(sizeof(*new)) ;
	new->debut = NULL ;
	new->curr = NULL ;
	new->last = NULL ;
	return new ;
}

void chemin_ajouter(chemin c, int* point ) {
	cell new = malloc(sizeof(*new)) ;
	new->next = NULL ;
	new->point[0] = point[0] ;
	new->point[1] = point[1] ;

	if( c->debut == NULL ) {
		c->debut = new ;
		c->last = new ;
		c->curr = new ;
	}

	else {
		c->last->next = new ;
		c->last = new ;
	}
}

void chemin_detruire(chemin c) {
	chemin_debut(c) ;
	cell tmp = c->debut ;
	while(tmp != NULL) {
		chemin_suivant(c) ;
		free(tmp) ;
		tmp = c->curr ;
	}
	free(c) ;
}

void chemin_debut(chemin c) {
	c->curr = c->debut ;
}

void chemin_fin(chemin c) {
	c->curr = c->last ;
}

int chemin_a_suivant(chemin c) {
	if(c->curr->next == NULL )
		return 0 ;
	return 1 ;
}
void chemin_suivant(chemin c) {
	c->curr = c->curr->next ;
}

int* chemin_get(chemin c) {
	return c->curr->point ;
}

chemin chemin_copie(chemin c) {
	chemin new = chemin_creer() ;
	chemin_debut(c) ;
	chemin_ajouter(new , chemin_get(c) ) ;
	while( chemin_a_suivant(c) ) {
		chemin_suivant(c) ;
		chemin_ajouter(new , chemin_get(c) ) ;
	}
	return new ;
}

void chemin_concatener(chemin c1 , chemin c2) {
	chemin tmp = chemin_copie( c2 ) ;
	c1->last->next = tmp->debut ;
	c1->last = tmp->last ;
	free(tmp) ;
}