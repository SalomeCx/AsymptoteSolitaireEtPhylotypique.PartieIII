#include <stdlib.h>
#include <string.h>

#include "pile_variables.h"
#include "tableaux_variables.h"

/* La structure pile a été implémentée pour représenter les blocs imbriqués dans le fichier lu. 
Plus on est au début de la pile, plus les variables sont globales. */

struct pile {
	tableau* tab ;
	int nb; // Le nombre d'éléments dans la pile.
	int taille; // La taille effective de la pile.
} ;

/* Agrandir la pile. */
void pile_agrandir(pile p)
{
	if (p->nb < p->taille)
		return ;
	p->taille *= 2;
	p->tab = realloc(p->tab, sizeof(*p->tab) * p->taille);
}

/* Créer une pile vide. */
pile pile_creer() {
	pile new = malloc(sizeof(*new)) ;
	new->nb = 0 ;
	new->taille = 10 ;
	new->tab = malloc(sizeof(*new->tab) * new->taille) ;
	return new ;
}

/* Empiler un nouveau bloc dans la pile. */
void pile_empiler(pile p) {
	pile_agrandir(p);
	p->tab[p->nb] = tableau_creer() ; 
	p->nb++ ;
}

/* Déclarer une nouvelle variable dans le bloc présent (= le haut de la pile.) */
void pile_ajouter(pile p, char* nom) {
	tableau_ajouter(p->tab[p->nb - 1], nom) ;
}

/* Dépiler un bloc de la pile. */
void pile_depiler(pile p) {
	if(p->nb < 1)
		return ;

	tableau_detruire(p->tab[p->nb-1]);
	p->nb-- ;
}

/* Vérifier si une variable est présente globalement (= dans un des blocs de la pile). */
int pile_est_present_global(pile p, char* nom) {
	int i ;
	for ( i = p->nb - 1 ; i >= 0 ; i-- ) {
		if( tableau_est_present(p->tab[i], nom ) != -1 )
			return 1 ;
	}
	return 0 ;
}

/* Vérifier si une variable est présente localement (= dans le dernier bloc de la pile). */
int pile_est_present_local(pile p, char* nom) {
	if( tableau_est_present(p->tab[p->nb - 1], nom ) != -1 )
			return 1 ;
	return 0 ;
}

/* Vérifier si une variable est ou non initialisée. */
int pile_est_initialise(pile p, char* nom) {
	int i ;
	for ( i = p->nb - 1 ; i >= 0 ; i-- )
		if( tableau_est_initialise(p->tab[i], nom ) )
			return 1 ;
	return 0 ;
}

/* Initialiser la variable nom de la pile, en commençant par les blocs les plus locaux. */
void pile_initialiser(pile p, char* nom, void* elem) {
	int i ;
	for ( i = p->nb - 1 ; i >= 0 ; i-- )
		if(tableau_est_present(p->tab[i], nom) != -1) {
			tableau_initialiser(p->tab[i], nom, elem) ;
			return ;
		}
}

/* Récupérer la valeur d'une variable de la pile, en commençant par les blocs les plus locaux. */
void* pile_get(pile p, char* nom) {
	int i ;
	for ( i = p->nb - 1 ; i >= 0 ; i-- ) {
		void* tmp = tableau_get(p->tab[i], nom ) ;

		if( tmp != NULL ) {
			return tmp ;
		}
	}
	return NULL ;	 
}

/* Détruire la pile. */
void pile_detruire(pile p) {
	int i ;
	for( i = 0 ; i < p->nb ; i++ )
		tableau_detruire( p->tab[i] ) ;
	free(p->tab) ;
	free(p) ;
}