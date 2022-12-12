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
	Un_elem* tete = liste;
	while(liste!=NULL){
		liste = liste->suiv;
		detruire_truc(tete->truc);
		detruire_liste(tete);
		tete = liste;
	}
}
 


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

            Un_truc *truc = (Un_truc*)malloc(sizeof(Un_truc));
            truc->type = STA;
            truc->data.sta.nom = (char*)malloc(100*sizeof(char));
            truc->coord.lon = lon;
            truc->coord.lat = lat;
            strcpy(truc->data.sta.nom, nom);
            truc->user_val = 0.0;
            truc->data.sta.tab_con = (Un_truc**)malloc(10*sizeof(Un_truc*));
            truc->data.sta.nb_con = 0;
            truc->data.sta.con_pcc = (Un_truc*)malloc(10*sizeof(Un_truc));

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
	Un_elem* deb = (Un_elem*)malloc(sizeof(Un_elem));
	deb->truc = truc;
	deb->suiv = liste;
	return deb;
}

Un_elem lire_connexions(char* nom_fichier, Un_nabr* abr){
	
	FILE* flux = NULL;
	flux = fopen(nom_fichier,"r");
	if(flux==NULL){
		printf("Erreur\n");
	}

	char new[100];

	while(fgets(new,100,flux)!=NULL){

		char* stat_dep = (char*)malloc(100*sizeof(char));
		char* stat_arr = (char*)malloc(100*sizeof(char));
		char* code = (char*)malloc(5*sizeof(char));
		char* temp = (char*)malloc(100*sizeof(char));
		char* endPtr;
		int i=0;
		int compt=0;
		int x=0;
		int y=0;
		int z=0;
		int w=0;

		/*
		for (i = 0; i < strlen(new); i++){
                if (new[i] == ';'){
                    compt++;
                }if (compt == 0){
                    strcpy(code, new + i + 1);
                    code[strlen(code)-1] = '\0';
                }
            }
		*/

		while(new[i]!='\n'){

			if(new[i]==';'){
				compt++;
				i++;
			}

			if(compt==0){
				code[i]=new[i];
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

		Un_truc* truc1 = chercher_station(abr, stat_dep);
		Un_truc* truc2 = chercher_station(abr, stat_arr);
		Un_truc* truc = (Un_truc*)malloc(sizeof(Un_truc));
		//truc1->data.sta.tab_con
        truc->type = CON;
        truc->data.con.sta_dep = truc1;
        truc->data.con.sta_arr = truc2;
        truc->data.con.ligne = (Une_ligne*)malloc(sizeof(Une_ligne));
        truc->data.con.ligne->code = (char*)malloc(5*sizeof(char));
        printf("%s\n", truc->data.con.ligne->code);
        strcpy(truc->data.con.ligne->code, code);
        printf("%f\n", truc1->data.sta.nb_con);
        truc1->data.sta.tab_con[truc1->data.sta.nb_con]=truc;
        truc2->data.sta.tab_con[truc2->data.sta.nb_con]=truc;
        truc1->data.sta.nb_con ++;
        truc2->data.sta.nb_con ++;

		printf("Ligne=%s : Station de depart = %s \n          Station d'arrivée = %s \n          Durée=%f\n", code, stat_dep, stat_arr, strtof(temp, &endPtr));

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

	printf("\n---DEBUT STATION---\n\n");

	Un_elem* new = lire_stations("flux.csv");

	//Regarde si la liste est bien triée selon user val et s'il n'y a pas de problème au niveau des stations
	affiche_station(new);

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
	//detruire_liste_et_truc(new);

	//affiche_station(new); //Normallement affiche ("Liste vide")


	//N'affiche pas, donc tout n'a pas bien été desalloué
	/*if(new==NULL){
	printf("Tout a bien été désalloué !");
	}*/


	printf("\n---FIN STATION---\n");

	printf("\n---DEBUT ARBRE---\n");

	Un_nabr* abr = (Un_nabr*)malloc(sizeof(Un_nabr));
	abr = construire_abr(new);


	printf("\n---DEBUT CONNEXION---\n\n");

	lire_connexions("connexion.csv", abr); //Je me permet de mettre l'arbre en + (à voir pour la suite)

	printf("\n---FIN CONNEXION---\n\n");

	return 0;
}

/* Exercice 1 à terminer, qq fonction à verif et à mettre dans le main */