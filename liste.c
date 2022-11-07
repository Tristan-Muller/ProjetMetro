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

/*Exercice 1 */
Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc);
void ecrire_liste(FILE *flux, Un_elem *liste);
void detruire_liste(Un_elem *liste);
void detruire_liste_et_truc(Un_elem *liste);
void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se);

/*Exercice 4*/
Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc);



Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc){
	Un_elem *tmp = (Un_elem*)malloc(sizeof(Un_elem));
	tmp->truc=truc;
	tmp->suiv=NULL;

	//Si problème d'allocation 
	if(tmp==NULL){
		printf("Erreur d'allocation de tmp");
	}

	//Cas si la liste est NULL
	if(liste==NULL){
		return tmp;
	}

	Un_elem *precedent = liste;
	Un_elem *element = liste->suiv;

	//Cas où user_val du truc à ajouter est inférieur à la 1ère valeur user_val de la liste
	if((liste->truc->user_val)>(tmp->truc->user_val)){
		tmp->suiv = liste;
		return tmp;
	}

	//Cas général
	while(((element->truc->user_val)<(tmp->truc->user_val))&&(element!=NULL)){
		precedent = precedent->suiv;
		element = element->suiv;
	}

	//Cas où la liste ne contient qu'un seul terme
	if(element==NULL){
		precedent->suiv = tmp;
		return precedent; 
	}

	precedent->suiv = tmp;
	tmp->suiv = element;
	return liste;
}



void ecrire_liste(FILE *flux, Un_elem *liste){
	Un_elem* tete = liste;
	flux = fopen("flux","w");
	if(flux==NULL){
		printf("Le document n'existe pas");
		return;
	}

	while(tete!=NULL){
		fprintf(flux,"%f;%f;%s\n", liste->truc->coord.lon,liste->truc->coord.lat,liste->truc->data.sta.nom); //A verif, Je ne sais pas quoi mettre dedans car ils disent d'écrire mais d'afficher alors...
		tete = tete->suiv;
	}

	fclose(flux);
}



void detruire_liste(Un_elem* liste){
	if(liste->suiv==NULL){
		detruire_truc(liste->truc);
		return;
	}
	detruire_truc(liste->truc);
	detruire_liste(liste->suiv);
}


//A terminer !
Un_elem* lire_stations(char *nom_fichier){

	FILE* flux = NULL;
	flux = fopen(nom_fichier,"r");
	if(flux==NULL){
		printf("Erreur\n");
		return NULL;
	}

	Un_elem* deb = NULL;
	Un_elem* tete = NULL;
	
	char* nom;
	char new[50];

	while(fgets(new,50,flux)!=NULL){

		Un_elem* liste = (Un_elem*)malloc(sizeof(Un_elem));
		Une_coord coord;
		Tdata data;
		float lon, lat;
		nom = (char*)malloc(50*sizeof(char));
		int i=0;
		int j=0;
		int compt=0;

		//On va au 1er caractère du nom de la station (on sait qu'avant ça il y a 2 ';')
		while(compt!=2){
			if(new[i]==';'){
				compt++;
			}
			i++;
		}

		//On ecrit dans new ce qu'il y a dans le fichier à partir de l'indice qu'on a d'avant
		while(new[i]!='\n'){
			nom[j]=new[i];
			j++;
			i++;
		}

		sscanf(new,"%f;%f",&lon,&lat);
		printf("Longitude = %f ; Latitude = %f ; Nom = %s\n", lon,lat,nom);
		
		coord.lon = lon;
		coord.lat = lat;
		data.sta.nom = nom;
		Un_truc* truc = creer_truc(coord, STA, data, 0.0); //User_val = 0 ?? 
		liste->truc = truc;
		free(nom);

		if(deb==NULL){
			deb=liste;
			tete=liste;
		}else{
			tete->suiv=liste;
			tete=liste;
		}
	}

	fclose(flux);
	return deb;
}


void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se){
	if((liste->truc->coord.lon<limite_no->lon)||(liste->truc->coord.lon>limite_se->lon)||(liste->truc->coord.lat<limite_se->lat)||(liste->truc->coord.lat>limite_no->lat)){
		printf("La station ou la connexion sort de la delimitation, impossible de créer cette station ou connexion");
	}
}

/* Exercice 4 : CONNEXION */
Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc){
	Un_elem* deb = (Un_elem*)malloc(sizeof(Un_elem));
	deb->truc = truc;
	deb->suiv = liste;
	return deb;
}

void *lire_connexions(char *nom_fichier){
	
	FILE* flux = NULL;
	flux = fopen(nom_fichier,"r");
	if(flux==NULL){
		printf("Erreur\n");
	}

	char new[100];

	while(fgets(new,100,flux)!=NULL){

		char* stat_dep = (char*)malloc(100*sizeof(char));
		char* stat_arr = (char*)malloc(100*sizeof(char));
		char code;
		char* temp = (char*)malloc(100*sizeof(char));
		char* endPtr;
		int i=0;
		int compt=0;
		int x=0;
		int y=0;
		int z=0;
		int w=0;

		while(new[i]!='\n'){

			if(new[i]==';'){
				compt++;
				i++;
			}

			if(compt==0){
				code=new[i];
				x++;
			}

			if(compt==1){
				stat_dep[y]=new[i];
				y++;
			}

			if(compt==2){
				stat_arr[z]=new[i];
				z++;

			}

			if(compt==3){
				temp[w]=new[i];
				w++;
			}

			i++;
		}

		//sscanf(";;;%f\n", &temp);
		printf("Ligne=%c : Station de depart = %s \n          Station d'arrivée = %s \n          Durée=%f\n", code, stat_dep, stat_arr, strtof(temp, &endPtr));
		
		free(stat_dep);	//Problème lors du free pour quelques gares rajoute 'ité' à la fin
		free(stat_arr);
		free(temp);
	}
	fclose(flux);
}




int main(){
	lire_stations("flux.csv");	//A tester !

	printf("\nFIN STATION\n\n");

	lire_connexions("connexion.csv");

	printf("\nFIN CONNEXION\n\n");
	return 0;
}

/* Exercice 1 à terminer, qq fonction à verif et à mettre dans le main */