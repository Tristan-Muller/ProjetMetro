#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "coord.h"
#include "station.h"
#include "truc.h"

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv);
void detruire_truc(Un_truc *truc);



Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv){
	Un_truc* new = (Un_truc*)malloc(sizeof(Un_truc));
	
	//Cas où problème d'allocation
	if(new==NULL){
		printf("Erreur d'allocation");
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
	if(truc->type == STA){
		printf("toto\n");
		
		//Problème pour free le nom et le tab_con ! A revoir !! (on rentre bien dans la fonction)
		
		free(truc->data.sta.nom);

		for (int i = 0; i < truc->data.sta.nb_con; ++i){
			free(truc->data.sta.tab_con[i]);
		}

		free(truc->data.sta.tab_con);
		free(truc);

	}
	if(truc->type == CON){
		free(truc);
	}
}

//Main test fonction
/*int main(){

	Une_coord coordonnee;
	coordonnee.lon = 24.3;
	coordonnee.lat = 10.7;

	Tdata data;
	char* nom = (char*)malloc(10*sizeof(char));
	nom = "Austerlitz";
	data.sta.nom = nom;
	data.sta.nb_con = 6;
	Un_truc** tab_con = (Un_truc**)malloc(sizeof(Un_truc*));
	data.sta.tab_con = tab_con;
	for (int i = 0; i < data.sta.nb_con; ++i){
		data.sta.tab_con[i] = (Un_truc*)malloc(sizeof(Un_truc));
	}

	double uv = 35.124;

	Un_truc* new = creer_truc(coordonnee, STA, data, uv);

	printf("Longitude = %f ; Latitude = %f ; Nom = %s\n", new->coord.lon, new->coord.lat, new->data.sta.nom);
	
	detruire_truc(new); 

	printf("Tout a bien été désalloué !\n");
	return 0;
}*/