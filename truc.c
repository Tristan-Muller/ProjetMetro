#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "coord.h"
#include "station.h"
#include "truc.h"


//Fonctions définies dans ce module

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv);
void detruire_truc(Un_truc *truc);



//Définition des fonctions

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv){
	/*Fonction qui crée un truc, station ou connexion*/

	Un_truc* new = (Un_truc*)malloc(sizeof(Un_truc));
	if (new==NULL){
		printf("Erreur d'allocation\n");
		return NULL;
	}

	new->data.sta.nom = (char*)malloc(50*sizeof(char));
	if (new->data.sta.nom==NULL){
		printf("Erreur d'allocation du nom de la station\n");
		return NULL;
	}

	//Mise en place du truc
	new->coord = coord;
	new->data = data;
	new->type = type;
	new->user_val = uv;
	return new;
}



void detruire_truc(Un_truc *truc){
	/*Fonction qui détruit un truc, en désallouant sa mémoire*/

	if (!truc) return;

	if(truc->type == STA){
		free(truc->data.sta.nom);
		
		int i = 0;
		while((truc->data.sta.tab_con[i])!=NULL){
			free(truc->data.sta.tab_con[i]);
			i++;
		}

		free(truc->data.sta.tab_con);
		free(truc->data.sta.con_pcc);
		free(truc);

	}

	else
		free(truc);

	printf("Mem Truc Désalouée\n");
}


//Main test fonction

/*

int main(){

	Une_coord coordonnee;
	coordonnee.lon = 24.312;
	coordonnee.lat = 10.7;

	//Test pour une station

	Tdata data;
	char* nom = (char*)malloc(50*sizeof(char));
	strcpy(nom,"Austerlitz");
	data.sta.nom = nom;
	data.sta.nb_con = 6;
	Un_truc** tab_con = (Un_truc**)malloc(6*sizeof(Un_truc*));
	data.sta.tab_con = tab_con;

	for (int i = 0; i < (data.sta.nb_con); ++i){
		data.sta.tab_con[i] = malloc(3*sizeof(Un_truc));
	}
	data.sta.con_pcc = NULL;

	double uv = 35.124;

	Un_truc* new = creer_truc(coordonnee, STA, data, uv);

	printf("Longitude = %f ; Latitude = %f ; Nom = %s\n", new->coord.lon, new->coord.lat, new->data.sta.nom);

	detruire_truc(new);

	//Test pour une connexion

	Tdata data_con;


	Un_truc *connexion = creer_truc(coordonnee, CON, data_con, uv);

	detruire_truc(connexion);


	printf("Fin main()\n");
	return 0;
}

*/