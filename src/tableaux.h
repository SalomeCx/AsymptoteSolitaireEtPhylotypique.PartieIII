#ifndef TABLEAUX_H
#define TABLEAUX_H


struct tableau_t{
	void ** tab[2];
	int nb; // Le nombre d'éléments dans le tableau.
	int taille; // La taille effective du tableau.
};

typedef struct tableau_t *  tableau;

tableau creer_tableau(void);
void agrandir_tableau(tableau t);
void ajouter_element(tableau t, void * nom);
int est_present_elem(tableau t, void * elem);
void detruire_tableau(tableau t);
int est_init_elem(tableau t, void * elem);
void initialiser_elem(tableau t, void * nom);

#endif