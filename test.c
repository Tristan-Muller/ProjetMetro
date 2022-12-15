#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "coord.h"
#include "station.h"
#include "truc.h"
#include "liste.h"
#include "ligne.h"
#include "abr_type.h"
#include "truc.c"
#include "abr.c"

// Test fonction exercice 1 //
int main(void) 
{
	Un_truc *truc1 ;
	Un_truc *truc2 ;
	Un_truc *truc3 ;
	char *nom1 = "Station 1";
	char *nom2 = "Station 2";
	char *nom3 = "Station 3";
	Tdata data1;
	Tdata data2;
	Tdata data3;
	Une_coord coord1;
	Une_coord coord2;
	data1.sta.nom = nom1;
	data1.sta.tab_con = NULL;
	data1.sta.con_pcc = NULL;
	data1.sta.nb_con = 0;
	coord1.lon = 10;
	coord1.lat = 1;
	truc1 = creer_truc(coord1, STA, data1, 0.0);
	printf("%s\n", truc1->data.sta.nom);
	data1.sta.nom = nom2;
	data1.sta.nb_con = 0;
	coord1.lon = 20;
	coord1.lat = 2;
	truc2 = creer_truc(coord1, STA, data1, 0.0);
	printf("%s\n", truc2->data.sta.nom);	
	data1.sta.nom = nom3;
	data1.sta.nb_con = 0;
	coord1.lon = 30;
	coord1.lat = 3;
	truc3 = creer_truc(coord1, STA, data1, 0.0);
	printf("%s\n", truc3->data.sta.nom);
	Un_elem *liste = NULL, *tmp;
	liste = inserer_liste_trie(liste, truc1);
	liste = inserer_liste_trie(liste, truc2);
	liste = inserer_liste_trie(liste, truc3);
	tmp = liste;
	while (tmp != NULL) {
		printf("%s\n", tmp->truc->data.sta.nom);
		tmp = tmp->suiv;	
	}
	detruire_liste_et_truc(liste);
	printf("liste supprimée\n");
	return 0;
}
/*
//Test Fonction lire_stations
int main(void)
{
	Un_elem *liste = NULL, *tmp = NULL;
	liste = lire_stations("type2.csv");
	tmp = liste;
	while (tmp != NULL) {
		printf("%s\n", tmp->truc->data.sta.nom);
		tmp = tmp->suiv;
	}
	detruire_liste_et_truc(liste);
	return 0;
}
//Test fonction inserer_arb
	Un_nabr *abr=creer_nabr(liste->truc), *noeud=creer_nabr(liste->suiv->truc);
	printf("%s\n", abr->truc->data.sta.nom);
	abr = inserer_abr(abr, noeud);
	if (abr->g !=NULL) {
		printf("Fils gauche: %s\n", abr->g->truc->data.sta.nom);
	}
	if (abr->d !=NULL) {
		printf("Fils droit: %s\n", abr->d->truc->data.sta.nom);
	}




//Test exo 2
Un_elem *liste = NULL, *tmp = NULL;
	liste = lire_stations("type.csv");
	tmp = liste;
	while (tmp != NULL) {
		printf("%s\n", tmp->truc->data.sta.nom);
		tmp = tmp->suiv;
	}
	FILE *fic=fopen("liste.csv", "w");
	ecrire_liste(fic, liste);
	printf("\n");
	Un_nabr *racine = construire_abr(liste);
	Un_truc *chose;
	char* nom="Pont de Levallois Bécon";
	chose = chercher_station(racine, nom);
	if (chose==NULL) {
		printf("\nNon trouvée %s\n", nom);
	}
	else {
		printf("\nYes: %s\n", chose->data.sta.nom);
	}
	detruire_abr(racine);
	detruire_liste_et_truc(liste);

// Test inserer_deb_liste

	Un_elem *liste = NULL;
	liste = lire_stations("test.csv");

	// Creation d'une ligne
	Une_ligne *ligne = (Une_ligne*) malloc(sizeof(Une_ligne));
	ligne->code = (char*) malloc(sizeof(char)*100);
	ligne->color = (char*) malloc(sizeof(char)*100);
	strcpy(ligne->code, "1");
	strcpy(ligne->color, "#00FF00");
	ligne->vitesse = 12.0;
	ligne->intervalle = 100;
	ligne->suiv = NULL;


	// Creation de deux connexions
	Une_connexion con1, con2;
	con1.sta_dep = liste->truc;
	con1.sta_arr = liste->suiv->truc;
	con1.ligne = ligne;
	con2.sta_dep = liste->suiv->truc;
	con2.sta_arr = liste->suiv->suiv->truc;
	con2.ligne = ligne;
	
	// Creation des deux trucs
	Un_truc *truc1, *truc2;
	Une_coord coord1;
	Une_coord coord2;
	coord1.lat = 10;
	coord1.lon = 01;
	coord2.lat = 20;
	coord2.lon = 02;
	Tdata data1, data2;
	data1.con = con1;
	data2.con = con2;
	truc1 = creer_truc(coord1, CON, data1, 0.0);
	truc2 = creer_truc(coord2, CON, data2, 0.0);

	printf("Dep: %s , Arr: %s , Ligne: %s \n",con1.sta_dep->data.sta.nom, con1.sta_arr->data.sta.nom, con1.ligne->code );
	printf("Dep: %s , Arr: %s , Ligne: %s \n",con2.sta_dep->data.sta.nom, con2.sta_arr->data.sta.nom, con2.ligne->code );

	printf("Dep: %s , Arr: %s  \n",truc1->data.con.sta_dep->data.sta.nom, truc1->data.con.sta_arr->data.sta.nom  );
	printf("Dep: %s , Arr: %s \n",truc2->data.con.sta_dep->data.sta.nom, truc2->data.con.sta_arr->data.sta.nom );




	Un_elem *liste_con=NULL;
	liste_con = inserer_deb_liste(liste_con, truc1);
	liste_con = inserer_deb_liste(liste_con, truc2);
	Un_elem *tmp = liste_con;
	while (tmp != NULL) {
		printf("%s ; %s \n", tmp->truc->data.con.sta_dep->data.sta.nom, tmp->truc->data.con.sta_arr->data.sta.nom);
		tmp = tmp->suiv;
	}


	detruire_liste_et_truc(liste);

// Test lire ligne
	Une_ligne *liste = NULL;
	liste = lire_lignes("ligne.csv");
	
	Une_ligne *tmp=liste;
	while (tmp !=NULL) {
		printf("%s ; %f ; %f ; %s\n", tmp->code, tmp->vitesse, tmp->intervalle, tmp->color);
		tmp = tmp->suiv;
	}
	Une_ligne *ligne1=NULL;
	ligne1 = chercher_ligne(liste, "1");
	printf("%s", ligne1->code);
	detruire_lignes(liste);

*/