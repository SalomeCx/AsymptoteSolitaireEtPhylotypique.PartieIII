#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tableaux_variables.h"

struct tableau_t{
	void** valeurs ;
	char** noms ;
	int nb; // Le nombre d'éléments dans le tableau.
	int taille; // La taille effective du tableau.
};

void tableau_agrandir(tableau t)
{
	if (t->nb < t->taille)
		return ;
	t->taille *= 2;
	t->valeurs = realloc(t->valeurs, sizeof(*t->valeurs) * t->taille);
	t->noms = realloc(t->noms, sizeof(*t->noms) * t->taille);

}

tableau tableau_creer(void)
{
	tableau t = malloc(sizeof(*t));
	t->nb = 0;
	t->taille = 10;
	t->valeurs = malloc(sizeof(*t->valeurs) * t->taille);
	t->noms = malloc(sizeof(*t->noms) * t->taille);
	return t;
}

void tableau_ajouter(tableau t, char* nom)
{
	tableau_agrandir(t);
	
	if (tableau_est_present(t, nom) != -1)
		return ;

	t->noms[t->nb] = nom ;
	t->valeurs[t->nb] = NULL ;
	t->nb++;
}

/* Retourne l'indice de l'élément s'il est présent, -1 sinon. */
int tableau_est_present(tableau t, char* nom)
{
	int i ;
	for (i = 0 ; i < t->nb; i++)
		
		if ( strcmp(t->noms[i],nom) == 0 ) {
			return i; //vrai.
		}
	return -1; //faux.
}

void tableau_detruire(tableau t)
{
	free(t->valeurs);
	free(t->noms);
	free(t);
}

int tableau_est_initialise(tableau t, char* nom)
{
	int indice = tableau_est_present(t, nom);
	if (indice == -1 || t->valeurs[indice] == NULL)
		return 0; //non initialisé.
	return 1; //initialisé.
}

void tableau_initialiser(tableau t, char* nom, void* elem)
{
	int indice = tableau_est_present(t, nom);
	if (indice == -1)
		return ;
	t->valeurs[indice] = elem;
}

int tableau_taille(tableau t) {
	return t->nb ;
}

void* tableau_get(tableau t, char* nom) {
	int tmp = tableau_est_present(t, nom) ;
	if(tmp == -1)
		return NULL ;
	return t->valeurs[tmp] ;
}
