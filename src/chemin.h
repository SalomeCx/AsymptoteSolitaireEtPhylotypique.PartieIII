#ifndef CHEMIN_H
#define CHEMIN_H

typedef struct chemin *chemin ;

chemin chemin_creer() ;
void chemin_ajouter(chemin c, int* point );
void chemin_detruire(chemin c) ;
void chemin_debut(chemin c) ;
void chemin_fin(chemin c) ;
int chemin_a_suivant(chemin c) ;
void chemin_suivant(chemin c) ;
int* chemin_get(chemin c) ;
int chemin_vide(chemin c) ;
chemin chemin_copie(chemin c) ;
void chemin_concatener(chemin c1 , chemin c2) ;

#endif