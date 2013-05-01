#include <stdio.h>
#include <stdlib.h>

#include "tableaux.h"


tableau creer_tableau(void)
{
	tableau t = malloc(sizeof(*t));
	t->nb = 0;
	t->taille = 10;
	*t->tab = malloc(sizeof(*t->tab) * t->taille);
	return t;
}

void agrandir_tableau(tableau t)
{
	if (t->nb < t->taille)
		return ;
	t->taille *= 2;
	*t->tab = realloc(t->tab, sizeof(*t->tab) * t->taille);

}


void ajouter_element(tableau t, void * nom, void * val)
{
	agrandir_tableau(t);
	
	if (est_present_elem(t, nom) != -1)
		return ;

	t->tab[t->nb][0] = nom;
	t->tab[t->nb][1] = val;
	t->nb++;

}

/* Retourne l'indice de l'élément s'il est présent, -1 sinon. */
int est_present_elem(tableau t, void * elem)
{
	int i = 0;
	for (i; i < t->nb; i++)
		if (t->tab[i][0] == elem)
			return i; //vrai.
	return -1; //faux.
}

void detruire_tableau(tableau t)
{
	free(t->tab);
	free(t);
}

int est_init_elem(tableau t, void * elem)
{
	int indice = est_present_elem(t, elem);
	if (indice == -1)
		return indice;
	if (t->tab[indice][1] == NULL)
		return 0; //non initialisé.
	return 1; //initialisé.
}

/* Ne vérifie pas le cas où un élément est initialisé  à NULL. */
void initialiser_elem(tableau t, void * nom, void * val)
{
	int indice = est_present_elem(t, nom);
	if (indice == -1)
		return ;
	t->tab[indice][1] = val;
}
