#ifndef TABLEAUX_H
#define TABLEAUX_H

typedef struct tableau_t *  tableau;

tableau tableau_creer(void);
void tableau_ajouter(tableau t, char* nom);
int tableau_est_present(tableau t, char* nom);
void tableau_detruire(tableau t);
int tableau_est_initialise(tableau t, char* nom);
void tableau_initialiser(tableau t, char* nom, void* elem);
int tableau_taille(tableau t) ;
void* tableau_get(tableau t, char * nom) ;

#endif