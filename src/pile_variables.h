#ifndef PILE_VARIABLES_H
#define PILE_VARIABLES_H

typedef struct pile *pile ;

pile pile_creer() ;
void pile_empiler(pile p) ;
void pile_depiler(pile p) ;
void pile_ajouter(pile p, char* nom) ;
int pile_est_present_global(pile p, char* nom) ;
int pile_est_present_local(pile p, char* nom) ;
int pile_est_initialise(pile p, char* nom) ;
void pile_initialiser(pile p, char* nom, void* elem) ;
void* pile_get(pile p, char* nom) ;
void pile_detruire(pile p) ;

#endif