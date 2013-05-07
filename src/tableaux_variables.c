#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tableaux_variables.h"

/* Cette structure de données permettra de manipuler des tableaux de variables dans lesquels 
on stocke le nom et la valeur de celles-ci. */

struct tableau_t{
	void** valeurs ; // Le tableau des valeurs des variables.
	char** noms ; // Le tableau des noms des variables.
	int nb; // Le nombre d'éléments dans le tableau.
	int taille; // La taille effective du tableau.
};


/* Agrandir la taille du tableau s'il n'y a plus de place. */
void tableau_agrandir(tableau t)
{
	if (t->nb < t->taille)
		return ;
	t->taille *= 2;
	t->valeurs = realloc(t->valeurs, sizeof(*t->valeurs) * t->taille);
	t->noms = realloc(t->noms, sizeof(*t->noms) * t->taille);
}


/* Créer un tableau vide. */
tableau tableau_creer(void)
{
	tableau t = malloc(sizeof(*t));
	t->nb = 0;
	t->taille = 10;
	t->valeurs = malloc(sizeof(*t->valeurs) * t->taille);
	t->noms = malloc(sizeof(*t->noms) * t->taille);
	return t;
}

/* Ajouter la variable nom au tableau. */
void tableau_ajouter(tableau t, char* nom)
{
	tableau_agrandir(t);
	
	if (tableau_est_present(t, nom) != -1)
	{
		fprintf(stderr, "Erreur: variable déjà déclarée.\n");
		exit(1) ;
	}

	t->noms[t->nb] = nom ;
	t->valeurs[t->nb] = NULL ;
	t->nb++;
}

/* Retourner l'indice de l'élément s'il est présent, -1 sinon. */
int tableau_est_present(tableau t, char* nom)
{
	int i ;
	for (i = 0 ; i < t->nb; i++)
		
		if ( strcmp(t->noms[i],nom) == 0 ) {
			return i; // Vrai.
		}
	return -1; // Faux.
}

/* Supprimer un tableau. */
void tableau_detruire(tableau t)
{
	free(t->valeurs);
	free(t->noms);
	free(t);
}

/* Connaître l'état d'une variable. (Initialisée ou non?) */
int tableau_est_initialise(tableau t, char* nom)
{
	int indice = tableau_est_present(t, nom);
	if (indice == -1 || t->valeurs[indice] == NULL)
		return 0; //non initialisé.
	return 1; //initialisé.
}

/* Initialiser un variable, ou si elle a déjà une valeur, la remplacer. */
void tableau_initialiser(tableau t, char* nom, void* elem)
{
	int indice = tableau_est_present(t, nom);
	if (indice == -1)
	{
		fprintf(stderr, "Erreur: variable non déclarée.\n");
		exit(1) ;
	}
	t->valeurs[indice] = elem;
}

/* Récupérer le nombre d'éléments dans le tableau. */
int tableau_taille(tableau t) {
	return t->nb ;
}

/* Récupérer la valeur de la variable nom. */
void* tableau_get(tableau t, char* nom) {
	int tmp = tableau_est_present(t, nom) ;
	if(tmp == -1)
		return NULL ;
	return t->valeurs[tmp] ;
}
