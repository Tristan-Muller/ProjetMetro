#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "coord.h"
#include "truc.h"
#include "truc.c"
#include "liste.h"
#include "ligne.h"
#include "station.h"
#include "abr_type.h"
#include "abr.c"



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
		printf("Le truc à inserer n'existe pas\n");
		return NULL;
	}

	if(truc->type != 0){
		printf("Le truc n'est pas une station\n");
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
    }

	Un_elem *liste = NULL;
	char ligne[100];
	int i = 0;
	int ok = 0;
	int compt = 0;

	float lon, lat;
	char *nom = (char *)malloc(100 * sizeof(char));
	if (!nom) {											//Vérification de l'allocation mémoire
		printf("Erreur\n");
		return NULL;
	}
	
	while (fgets(ligne, 100, flux)){					//On boucle sur tout le fichier
		sscanf(ligne, "%f ; %f ; ", &lon, &lat);

		while ((i < strlen(ligne)) && (!ok)) {
			if (ligne[i] == ';')
				compt++;
			if (compt == 2){
				strcpy(nom, ligne + i + 1);
				nom[strlen(nom)-1] = '\0';
				ok =1;
			}
			i++;
		}

		Un_truc *truc = (Un_truc *)malloc(sizeof(Un_truc));
		if (!truc){
			printf("Erreur\n");
			return NULL;
		}
		else {
			truc->type = STA;
			truc->data.sta.nom = (char *)malloc(100 * sizeof(char));
			truc->coord.lon = lon;
			truc->coord.lat = lat;
			strcpy(truc->data.sta.nom, nom);
			truc->user_val = 0.0;
			truc->data.sta.tab_con = (Un_truc **)malloc(10 * sizeof(Un_truc *));
			truc->data.sta.nb_con = 0;
			truc->data.sta.con_pcc = (Un_truc *)malloc(10 * sizeof(Un_truc));

			if ((!truc->data.sta.con_pcc) || (!truc->data.sta.tab_con) || (!truc->data.sta.nom)){
				printf("Erreur\n");
				return NULL;
			}
		}

		liste = inserer_liste_trie(liste, truc);
		//printf("Longitude = %f ; Latitude = %f ; Nom = %s\n", liste->truc->coord.lon,liste->truc->coord.lat, liste->truc->data.sta.nom);

		compt = 0;
		i=0;
		ok = 0;
	}
	fclose(flux);

	return liste;
    
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

<<<<<<< HEAD


Un_elem * lire_connexions(char* nom_fichier, Un_nabr* abr){
=======
Un_elem *lire_connexions(char* nom_fichier, Un_nabr* abr){
>>>>>>> 000be00ee89989b3544f6fcacb1710ff11d3c2a2
	
	FILE* fic = NULL;
	fic = fopen(nom_fichier,"r");
	if(!fic){
		printf("Erreur\n");
		return NULL;
	}
	Un_elem *liste = NULL;
	char new[100];

	while(fgets(new,100,fic)!=NULL){

		char* stat_dep = (char*)malloc(100*sizeof(char));
		char* stat_arr = (char*)malloc(100*sizeof(char));
		char* code = (char*)malloc(1*sizeof(char));
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
		//printf("%s\n", stat_arr);
		//printf("%s\n", truc2->data.sta.nom);
        truc->type = CON;
        truc->data.con.sta_dep = truc1;
        truc->data.con.sta_arr = truc2;
        truc->data.con.ligne = (Une_ligne*)malloc(sizeof(Une_ligne));
        truc->data.con.ligne->code = (char*)malloc(1*sizeof(char));
        strcpy(truc->data.con.ligne->code, code);
<<<<<<< HEAD
        printf("%d\n", truc1->data.sta.nb_con);
=======
        //printf("%s\n", truc->data.con.ligne->code);
        //printf("%d\n", truc2->data.sta.nb_con);
>>>>>>> 000be00ee89989b3544f6fcacb1710ff11d3c2a2
        truc1->data.sta.tab_con[truc1->data.sta.nb_con]=truc;
        truc2->data.sta.tab_con[truc2->data.sta.nb_con]=truc;
        truc1->data.sta.nb_con ++;
        truc2->data.sta.nb_con ++;

		printf("Ligne=%s : Station de depart = %s \n          Station d'arrivée = %s \n          Durée=%f\n", code, stat_dep, stat_arr, strtof(temp, &endPtr));
        
        liste = inserer_deb_liste(liste, truc);
		free(stat_dep);
		free(stat_arr);
		free(temp);
	}
	return NULL;

<<<<<<< HEAD
	fclose(fic);
=======
	fclose(flux);
	return liste; //A voir si c'est bien liste qu'il faut retourner
>>>>>>> 000be00ee89989b3544f6fcacb1710ff11d3c2a2
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

<<<<<<< HEAD
=======
//Fonction supplementaire pour verification 
void affiche_prefixe(Un_nabr* abr){
	if(abr==NULL){
		return;
	}
	printf("%s\n", abr->truc->data.sta.nom);
	affiche_prefixe(abr->g);
	affiche_prefixe(abr->d);
}
>>>>>>> 000be00ee89989b3544f6fcacb1710ff11d3c2a2


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
		//detruire_liste_et_truc(new);

		//affiche_station(new); //Normallement affiche ("Liste vide")


		//N'affiche pas, donc tout n'a pas bien été desalloué
		/*if(new==NULL){
		printf("Tout a bien été désalloué !");
		}*/


	printf("\n---FIN STATION---\n");

	printf("\n---DEBUT ARBRE---\n\n");

<<<<<<< HEAD
		Un_nabr* abr = (Un_nabr*)malloc(sizeof(Un_nabr));
		abr = construire_abr(new);

		afficher_abr(abr);

		printf("\nRecherche\n");
		Un_truc *sta = chercher_station(abr, "Le Blosne");

		if (sta)
			printf("%s\n", sta->data.sta.nom);
		else 
			printf("NO STA\n");
			
		Un_elem * seek = inserer_liste_trie(NULL,sta);
		affiche_station(seek);

	printf("\n---FIN ARBRE---\n");

=======
	Un_nabr* abr = (Un_nabr*)malloc(sizeof(Un_nabr));
	abr = construire_abr(new);
	affiche_prefixe(abr);
>>>>>>> 000be00ee89989b3544f6fcacb1710ff11d3c2a2


	printf("\n---DEBUT CONNEXION---\n\n");

		lire_connexions("connexion.csv", abr); //Je me permet de mettre l'arbre en + (à voir pour la suite)

	/*
	printf("Verification tableau de connexion des stations:\n");
	
	for(int i=0; i<(0,new->truc->data.sta.nb_con); i++){
		printf("%s", new->truc->data.sta.tab_con[i]);
	}
	*/ 
	//A voir après vu que c'est un tableau de connexion on peut pas print les connexions

	printf("\n---FIN CONNEXION---\n\n");

	return 0;
}

/* Exercice 1 à terminer, qq fonction à verif et à mettre dans le main */