#ifndef LISTE_H
#define LISTE_H

#include "truc.h"
#include "coord.h"
#include "connexion.h"
#include "abr_type.h"
#include "ligne.h"



// Ce module contient la définition de la structure Un_elem, utilisée dans les listes de truc


typedef struct _un_elem {
	Un_truc *truc; //Une station ou une connexion
	struct _un_elem *suiv;
} Un_elem;

Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc);
void ecrire_liste(FILE *flux, Un_elem *liste);
void detruire_liste(Un_elem *liste);
void detruire_liste_et_truc(Un_elem *liste);
void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se);
Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc);
Un_elem *lire_stations(char *nom_du_fichier);
Un_elem *lire_connexions(char* nom_fichier, Un_nabr* abr);
void affiche_station(Un_elem* liste);
void affiche_prefixe(Un_nabr* abr);
Un_truc* extraire_deb_liste(Un_elem* liste);
Un_truc* extraire_liste(Un_elem* liste, Un_truc* truc);
void dijkstra(Un_elem* liste_sta, Un_truc* sta_dep);
int sta_dans_liste (Un_elem *liste, char *sta);

#endif
