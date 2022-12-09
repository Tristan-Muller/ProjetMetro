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

	if(truc->type != 0){
		printf("Le truc n'est pas une station");
		return NULL;
	}

	if(truc==NULL){
		printf("Le truc à inserer n'existe pas");
		return NULL;
	}

	Un_elem *tmp = (Un_elem*)malloc(sizeof(Un_elem));

	tmp->truc=truc;
	tmp->suiv=NULL;

	//printf("%f", tmp->truc->user_val);

	//Si problème d'allocation
	if(tmp==NULL){
		printf("Erreur d'allocation de l'element\n");
		return NULL;
	}

	//Cas si la liste est NULL
	if(liste==NULL){
		return tmp;
	}

	Un_elem *maillon = liste;

	
	//Cas où la liste ne contient qu'un seul terme
	if((maillon->truc->user_val)<(tmp->truc->user_val)){
		tmp->suiv = maillon;
		return tmp;
	}


	//Cas général
	while((maillon->suiv!=NULL) && ((maillon->suiv)->truc->user_val)<(tmp->truc->user_val)){

		maillon = maillon->suiv;
	}

	if(maillon->suiv == NULL){
		maillon->suiv = tmp;
		return liste;
	}

	tmp->suiv = maillon->suiv;
	maillon->suiv = tmp;
	return liste;
}



void ecrire_liste(FILE *liste_station, Un_elem *liste){
	Un_elem* tete = liste;
	if(liste==NULL){
		printf("Aucune liste à déchiffrer");
		return;
	}

	while(tete!=NULL){
		fprintf(liste_station,"%f;%f;%s\n", tete->truc->coord.lon, tete->truc->coord.lat, tete->truc->data.sta.nom);
		tete = tete->suiv;
	}
}



void detruire_liste(Un_elem* liste){
	free(liste);
	return;
}


void detruire_liste_et_truc(Un_elem* liste){
	if(liste->suiv==NULL){
		detruire_truc(liste->truc);
		detruire_liste(liste);
		return;
	}

	detruire_truc(liste->truc);
	detruire_liste_et_truc(liste->suiv);
}


/*
Un_elem* lire_stations_marche_pas(char *nom_fichier){

	FILE* flux = NULL;
	flux = fopen(nom_fichier,"r");
	if(flux==NULL){
		printf("Erreur d'ouverture du fichier\n");
		return NULL;
	}

	char new[200];

	Un_elem* liste = NULL;


	while(fgets(new,200,flux)!=NULL){

		Une_coord coord;
		Tdata data;
		float lon, lat;
		char* nom = (char*)malloc(50*sizeof(char));
		int i=0;
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
		nom[j]='\0';
		

		strcpy(nom,new +i);
		printf("%s",nom);
		sscanf(new, "%f;%f", &lon,&lat);

		coord.lon = lon;
		coord.lat = lat;


		printf("%s",nom);
		Un_truc* truc = creer_truc(coord, STA, data, coord.lat);
		printf("%s",nom);
		strcpy(truc->data.sta.nom, nom);
		liste = inserer_liste_trie(liste, truc);

		printf("Longitude = %f ; Latitude = %f ; Nom = %s\n", liste->truc->coord.lon,liste->truc->coord.lat, liste->truc->data.sta.nom);

		i=0;
		compt=0;
		free(nom);
	}

	fclose(flux);
	return liste;
}
*/



Un_elem *lire_stations(char *nom_du_fichier){

    FILE *flux = fopen(nom_du_fichier, "r");
    if (flux == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }else{
        Un_elem *liste = NULL;
        char ligne[100];
        int i = 0;
        int compt = 0;
        
        while (fgets(ligne, 100, flux) != NULL){
            float lon, lat;
            char *nom = (char *)malloc(100 * sizeof(char));
            sscanf(ligne, "%f ; %f ; ", &lon, &lat);

            for (i = 0; i < strlen(ligne); i++){
                if (ligne[i] == ';'){
                    compt++;
                }if (compt == 2){
                    strcpy(nom, ligne + i + 1);
                    nom[strlen(nom)-1] = '\0';
                    break;
                }
            }

            Un_truc *truc = (Un_truc *)malloc(sizeof(Un_truc));
            truc->type = STA;
            truc->data.sta.nom = (char *)malloc(100 * sizeof(char));
            truc->coord.lon = lon;
            truc->coord.lat = lat;
            strcpy(truc->data.sta.nom, nom);
            truc->user_val = lat;
            truc->data.sta.tab_con = (Un_truc **)malloc(10 * sizeof(Un_truc *));
            truc->data.sta.nb_con = 0;
            truc->data.sta.con_pcc = (Un_truc *)malloc(10 * sizeof(Un_truc));

            liste = inserer_liste_trie(liste, truc);
			//printf("Longitude = %f ; Latitude = %f ; Nom = %s\n", liste->truc->coord.lon,liste->truc->coord.lat, liste->truc->data.sta.nom);

            compt = 0;
        }
        fclose(flux);

        return liste;
    }
}

//A changer
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

Un_elem lire_connexions(char* nom_fichier){
	
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

		stat_dep[y]='\0';
		stat_arr[z]='\0';
		temp[w]='\0';

		printf("Ligne=%c : Station de depart = %s \n          Station d'arrivée = %s \n          Durée=%f\n", code, stat_dep, stat_arr, strtof(temp, &endPtr));

		free(stat_dep);	
		free(stat_arr);
		free(temp);
	}

	fclose(flux);
}


//Fonction supplementaire pour vérification
void affiche_station(Un_elem* liste){
	Un_elem* tmp = NULL;
	if(liste==NULL){
		printf("Liste vide");
	}else{
		tmp = liste;
		while(tmp != NULL){
			//printf("%f\n", tmp->truc->coord.lat);
			//printf("%f\n", tmp->truc->coord.lon);
			printf("%s\n", tmp->truc->data.sta.nom);
			tmp = tmp->suiv;
		}
	}
}

int main(){

	Un_elem* new = lire_stations("flux.csv");

	//Regarde si la liste est bien triée selon user val et s'il n'y a pas de problème au niveau des stations
	affiche_station(new);

	FILE* fic = fopen("liste_station.csv","w");
	ecrire_liste(fic,new);
	fclose(fic);

	detruire_liste_et_truc(new);
	printf("Tout a bien été désalloué !");


	printf("\nFIN STATION\n\n");

	lire_connexions("connexion.csv");

	printf("\nFIN CONNEXION\n\n");
	return 0;
}

/* Exercice 1 à terminer, qq fonction à verif et à mettre dans le main */