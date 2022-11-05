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
	}

	Un_elem* deb = NULL;
	Un_elem* tete = NULL;

	char new[50];
	int i=0;
	int j=0;
	int compt=0;

	while(fgets(new,50,flux)!=NULL){

		Un_elem* liste = (Un_elem*)malloc(sizeof(Un_elem));

		float lon, lat;
		char* nom = (char*)malloc(50*sizeof(char));

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

		sscanf(new,"%f;%f;",&lon,&lat);
		printf("Longitude = %f ; Latitude = %f ; Nom = %s\n", lon,lat,nom);
		

		liste->truc->coord.lon = lon;
		liste->truc->coord.lat = lat;
		strcpy(liste->truc->data.sta.nom, nom);
		free(nom);
		//Problème : segmentation fault

		if(deb==NULL){
			deb=liste;
			tete=liste;
		}else{
			tete->suiv=liste;
			tete=liste;
		}

		i=0;
		j=0;
		compt=0;
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

Un_elem *lire_connexions(char *nom_fichier, Une_ligne *liste_ligne, Un_nabr *abr_sta){
	
}



int main(){
	lire_stations("flux.csv");	//A tester !
	return 0;
}

/* Exercice 1 à terminer, qq fonction à verif et à mettre dans le main */