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



//Fonctions définies dans ce module : 

	/*Exercice 1 */
void afficher_liste(Un_elem *liste);
Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc);
void ecrire_liste(FILE *flux, Un_elem *liste);
void detruire_liste(Un_elem *liste);
void detruire_liste_et_truc(Un_elem *liste);
void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se);

	/*Exercice 4*/
Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc);



//Définition des fonctions



void afficher_liste(Un_elem *liste){
	//Affiche une liste de trucs
	if (!liste) printf("### End of the List ###\n"); 
	else {
		if (liste->truc->type == STA)
			printf("STA : \tLon= %f ;\t Lat = %f ;\t Nom = %s\n", liste->truc->coord.lon,liste->truc->coord.lat,liste->truc->data.sta.nom);
		else 
			printf("CON : \tstation de départ : %s\n", liste->truc->data.con.sta_dep->data.sta.nom);
		
		if (liste->suiv)
			afficher_liste(liste->suiv);
	}
}



Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc){
	//Ajoute un truc dans une liste triée de truc

	if(!truc){
		printf("Le truc à inserer n'existe pas");
		return NULL;
	}

	if(truc->type != 0){
		printf("Le truc n'est pas une station");
		return liste;
	}

	Un_elem *tmp = (Un_elem*)malloc(sizeof(Un_elem));
	if (!tmp) {					//Si problème d'allocation 
		printf("ERREUR\n");
		return liste;
	}

	tmp->truc=truc;
	tmp->suiv=NULL;


	//Cas si la liste est NULL
	if(!liste){
		return tmp;
	}

	Un_elem *maillon = liste;

	//Cas où le 1er élément de la liste est déjà supérieur
	if((maillon->truc->user_val)>(tmp->truc->user_val)){
		tmp->suiv = maillon;
		return tmp;
	}


	//Cas général
	while((maillon->suiv) && ((maillon->suiv->truc->user_val)<(tmp->truc->user_val))){
		maillon = maillon->suiv;
	}

	if(!maillon->suiv)					//Si on arrive au bout de la liste, on ajoute tmp ou bout
		maillon->suiv = tmp;
	else {								//Sinon, on ajoute tmp dans la liste après maillon
		tmp->suiv = maillon->suiv;
		maillon->suiv = tmp;
	}

	return liste;
}



void ecrire_liste(FILE *liste_station, Un_elem *liste){
	//Ecrit une liste de stations dans un fichier
	
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
	//Détruit une liste de trucs

	if (!liste)							//Si la liste est vide, RAS
		return;
		
	free(liste);

}

void detruire_liste_et_truc(Un_elem* liste){
	Un_elem* tete = liste;
	while(liste!=NULL){
		liste = liste->suiv;
		detruire_truc(tete->truc);
		detruire_liste(tete);
		tete = liste;
	}
}



Un_elem *lire_stations(char *nom_du_fichier){
	//Crée une liste de stations à partir d'un fichier .csv

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
                if (ligne[i] == ';')
                    compt++;
                if (compt == 2){
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
            truc->user_val = 0.0;
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



void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se){
	Un_elem* tete = liste;
	limite_no->lon = liste->truc->coord.lon;
	limite_no->lat = liste->truc->coord.lat;
	limite_se->lon = liste->truc->coord.lon;
	limite_se->lat = liste->truc->coord.lat;
	tete = tete->suiv;

	while(tete!=NULL){

		if((tete->truc->coord.lon)>(limite_se->lon)){
			limite_se->lon = tete->truc->coord.lon;
		}

		if((tete->truc->coord.lat)<(limite_se->lat)){
			limite_se->lat = tete->truc->coord.lat;
		}

		if((tete->truc->coord.lon)<(limite_no->lon)){
			limite_no->lon = tete->truc->coord.lon;
		}

		if((tete->truc->coord.lat)>(limite_no->lat)){
			limite_no->lat = tete->truc->coord.lat;
		}

		tete = tete->suiv;
	}
}


/* Exercice 4 : CONNEXION */

Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc){
	//Insère un truc en tête d'une liste de trucs

	if(!truc) return liste;

	Un_elem* deb = (Un_elem*)malloc(sizeof(Un_elem));
	if(!deb) {
		printf("ERREUR\n");
		return liste; 
	}

	deb->truc = truc;

	if (!liste) deb->suiv = NULL;
	else deb->suiv = liste;
	return deb;
}



Un_elem *lire_connexions(char* nom_fichier){
	//Crée une liste de connexion à partir d'un fichier
	
	FILE* fic = NULL;
	fic = fopen(nom_fichier,"r");
	if(!fic){
		printf("Erreur\n");
		return NULL;
	}

	char new[100];

	while(fgets(new,100,fic)!=NULL){

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
	return NULL;

	fclose(fic);
}



void affiche_station(Un_elem* liste){
	//Affiche une liste de stations

	Un_elem* tmp = NULL;
	if(liste==NULL){
		printf("Liste vide");
	}else{
		tmp = liste;
		while(tmp != NULL){
			printf("%f\n", tmp->truc->coord.lat);
			printf("%f\n", tmp->truc->coord.lon);
			printf("%s\n", tmp->truc->data.sta.nom);
			tmp = tmp->suiv;
		}
	}
}



int main(){

	printf("\n---DEBUT STATION---\n\n");

	Un_elem* new = lire_stations("flux.csv");

	//Regarde si la liste est bien triée selon user val et s'il n'y a pas de problème au niveau des stations
	//affiche_station(new);
	afficher_liste(new);

	FILE* fic = fopen("liste_station.csv","w");
	ecrire_liste(fic,new);
	fclose(fic);

	Une_coord limite_no;
	Une_coord limite_se;

	limites_zone(new, &limite_no, &limite_se);

	printf("\n---LIMITES ZONES---\n\n");
	printf("Longitude min : %f\n", limite_no.lon);
	printf("Latitude max : %f\n", limite_no.lat);
	printf("Longitude max : %f\n", limite_se.lon);
	printf("Latitude min : %f\n", limite_se.lat);

	//Revoir detruire ! (Je comprend pas pk ça marche pas)
	detruire_liste_et_truc(new);

	//affiche_station(new); //Normallement affiche ("Liste vide")

	//N'affiche pas, donc tout n'a pas bien été desalloué
	if(new==NULL){
	printf("Tout a bien été désalloué !");
	}


	printf("\n---FIN STATION---\n");
	printf("\n---DEBUT CONNEXION---\n\n");

	lire_connexions("connexion.csv");

	printf("\n---FIN CONNEXION---\n\n");
	return 0;
}

/* Exercice 1 à terminer, qq fonction à verif et à mettre dans le main */