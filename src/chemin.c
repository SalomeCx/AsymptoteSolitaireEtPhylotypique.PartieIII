#include <stdlib.h>

#include "chemin.h"


/* Les variables chemin ont besoin d'une structure de données.
Elles sont donc implémentées ici sous forme de listes simplement chaînées. */

typedef struct cell *cell ;

struct cell {
	cell next ;
	int point[2] ;
} ;

struct chemin {
	cell first ;
	cell curr ;
	cell last ;
} ;

/* Créer un chemin vide. */
chemin chemin_creer(){
	chemin new = malloc(sizeof(*new)) ;
	new->first = NULL ;
	new->curr = NULL ;
	new->last = NULL ;
	return new ;
}

/* Ajouter un point à la fin d'un chemin déjà existant. */
void chemin_ajouter(chemin c, int* point ) {
	cell new = malloc(sizeof(*new)) ;
	new->next = NULL ;
	new->point[0] = point[0] ;
	new->point[1] = point[1] ;

	if( c->first == NULL ) {
		c->first = new ;
		c->last = new ;
		c->curr = new ;
	}

	else {
		c->last->next = new ;
		c->last = new ;
	}
}

/* Supprimer un chemin existant. */
void chemin_detruire(chemin c) {
	chemin_debut(c) ;
	cell tmp = c->first ;
	while(tmp != NULL) {
		chemin_suivant(c) ;
		free(tmp) ;
		tmp = c->curr ;
	}
	free(c) ;
}

/* Déplacer le curseur au début du chemin. */
void chemin_debut(chemin c) {
	c->curr = c->first ;
}

/* Déplacer le curseur à la fin du chemin. */
void chemin_fin(chemin c) {
	c->curr = c->last ;
}

/* Tester si le curseur est à la fin ou non du chemin. */
int chemin_a_suivant(chemin c) {
	if(c->curr->next == NULL )
		return 0 ;
	return 1 ;
}

/* Bouger le curseur à la cellule suivante. */
void chemin_suivant(chemin c) {
	c->curr = c->curr->next ;
}

/* Récupérer le point situé au niveau du curseur. */
int* chemin_get(chemin c) {
	return c->curr->point ;
}

/* Renvoyer une copie du chemin. */
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

/* Concaténer le chemin c2 à la fin du chemin c1. */
void chemin_concatener(chemin c1 , chemin c2) {
	chemin tmp = chemin_copie( c2 ) ;
	c1->last->next = tmp->first ;
	c1->last = tmp->last ;
	free(tmp) ;
}