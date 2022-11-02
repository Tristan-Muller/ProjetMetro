#include <stdlib.h>
#include <stdio.h>
#include "coord.h"
#include "station.h"
#include "truc.h"
#include "liste.h"
#include "truc.c"


Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc);
void ecrire_liste(FILE *flux, Un_elem *liste);
void detruire_liste(Un_elem *liste);
void detruire_liste_et_truc(Un_elem *liste);
Un_elem *lire_stations(char *station);
void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se);


Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc){
	Un_elem *tmp = (Un_elem*)malloc(sizeof(Un_elem));
	tmp->truc=truc;
	tmp->suiv=NULL;

	//Si problème d'allocation 
	if(tmp==NULL){
		printf("erreur d'allocation de tmp");
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
	float lon,lat;
	char* nom_stat;
	FILE* fichier = NULL;
	fichier = fopen("flux.csv","w");
	while(liste!=NULL){
		printf("Longitude : ");
		scanf("%f", &lon);
		printf("Latitude : ");
		scanf("%f", &lat);
		printf("Nom de la station : ");
		scanf("%s", nom_stat);
		fprintf(fichier,"%f;%f;%s\n", lon,lat,nom_stat); //A verif, Je ne sais pas quoi mettre dedans car ils disent d'écrire mais d'afficher alors...
	}
	fclose(fichier);
}



void detruire_liste(Un_elem* liste){
	if(liste->suiv==NULL){
		detruire_truc(liste->truc);
		return;
	}
	detruire_truc(liste->truc);
	detruire_liste(liste->suiv);
}



Un_elem *lire_stations(char *station){
	Un_elem* new_stat = (Un_elem*)malloc(sizeof(Un_elem));
	char* new_float_lon;
	char* new_float_lat;
	char* new_char;
	int k = 0;
	int j = 0;

	for (int i = 0; station[i]=!'\0'; ++i){
		if(station[i]==';'){
			if((station[i-1]=='0')||(station[i-1]=='1')||(station[i-1]=='2')||(station[i-1]=='3')||(station[i-1]=='4')||(station[i-1]=='5')||(station[i-1]=='6')||(station[i-1]=='7')||(station[i-1]=='8')||(station[i-1]=='9')){
				if(k==0){
					new_stat->truc->coord.lon = strtof(new_float_lon, '\0');
				}if(k==1){
					new_stat->truc->coord.lat = strtof(new_float_lat, '\0');
				}
			}else{
				new_stat->truc->data.sta.nom = new_char;
			}
			k++;
	}if(station[i]!=';'){
		if(k==0){
			new_float_lon[j] = station[i];
		}if(k==1){
			new_float_lat[j] = station[i];
		}
	}if(station[i]=='\0'){
		new_char[j] = station[i];
	}
	j++;
}
return new_stat;
}



void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se){
	if((liste->truc->coord.lon<limite_no->lon)||(liste->truc->coord.lon>limite_se->lon)||(liste->truc->coord.lat<limite_se->lat)||(liste->truc->coord.lat>limite_no->lat)){
		printf("La station ou connexion sort de la delimitation, impossible de créer cette station ou connexion");
	}
}




int main(){
	Un_elem* station = lire_stations("-1.711154;48.121348;J.F Kennedy");	//A tester !
	free(station);
	return 0;
}

/* Exercice 1 à terminer, qq fonction à verif et à mettre dans le main */