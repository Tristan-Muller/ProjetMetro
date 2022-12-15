#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"liste.h"
#include"truc.h"
#include"abr_type.h"
#include"ligne.h"
#include"aqrtopo.h"
#include"truc.c"
#include"liste.c"
//#include<SDL.h>
//#define WINDOW_WIDTH 1280
//#define WINDOW_HEIGHT 720

//gcc *.c $(sd12-config --cflags --libs) -o prog

int main (){

	printf("\n---TEST STATION---\n\n");

	Un_truc* truc;
	Une_coord limite_no;
	Une_coord limite_se;
	FILE* fic = fopen ("liste_station.csv" , "w");

	if (fic == NULL){
		printf("Erreur quand on veut ouvrir le fichier .\n");
		return 0;
	}

	Un_elem* liste_sta = NULL;

	Un_elem* new = lire_stations("flux.csv");

	printf("Liste des stations : \n");
	affiche_station(new);

	printf("On écrit maintenant dans le fichier liste_station.\n");
	ecrire_liste(fic , new);

	printf("On a réussi ces 2 étapes ! \n");
	fclose(fic);

	limites_zone(new , &limite_no , &limite_se);
	//detruire_liste_et_truc(liste);
	//printf("on a free liste on va essayer d'afficher liste on devrait avoir un seg fault\n");
	//afficher_station_dans_liste(liste);
	printf("on va tester construire arbre \n");
	Un_nabr* arbre = construire_abr(liste);
	//printf("on est sorti de consrtuire abr et on veut afficher l'arbre.\n");
	//affiche_prefix_arbre(arbre);
	//printf("on va essayer de free l'arbre.\n");
	//free(arbre);
	//printf("on va essayer mtn d'afficher l'arbre on devrait avoir un seg fault.\n");
	//affiche_prefix_arbre(arbre);
	//truc = chercher_station(arbre ,"Les Sablons");
	//printf("%s ; %f ; %f\n",truc->data.sta.nom,truc->coord.lat,truc->coord.lon);
	Une_ligne* ligne;
	Une_ligne* temp;
	ligne = lire_lignes("ligne.csv");
	//printf("on passe à afficher ligne\n");
	//afficher_lignes(ligne);
	//printf("on arrive à free\n");
	//detruire_lignes(ligne);
	//afficher_lignes(ligne);
	//printf("on va essayer dafficher ligne on devrait avoir un seg fault.\n");
	//printf("on cherche la ligne 1 par exemple :\n");
	temp = chercher_ligne(ligne , "3");
	printf("%s ; %f ; %f ; %s\n",temp->code , temp->vitesse , temp->intervalle , temp->color);
	//Un_truc* station456 = chercher_station(arbre , "La Defense");
	//printf("%s\n",station456->data.sta.nom);
	liste_sta = lire_connexions("connexion.csv" , ligne , arbre);
	afficher_connexion_dans_arbre(arbre);
	printf("ON VA MAINTENANT TESTER CONSTRUIRE_AQR :\n");
		Un_noeud* nouvel_aqr;
		nouvel_aqr = construire_aqr(liste);
		if (nouvel_aqr == NULL) printf("erreur lors de l'allocation mémoire de l'aqr\n");
		//faudrait faire une fonction affiche_aqr
		
		printf("\n\nL'AQR A ÉTÉ CONSTRUIT, ON VA L'AFFICHER\n");
		affiche_pre_aqr(nouvel_aqr);
		
		//printf("on va essayer de free l'aqr.\n");
		//detruire_aqr(nouvel_aqr);
		//printf("on va essayer mtn d'afficher l'arbre on devrait avoir un seg fault.\n");
		
		//affiche_pre_aqr(nouvel_aqr);
		
		printf("\n\nFIN\nsimple test pour montrer la tête de l'aqr actuellement : %s\n",nouvel_aqr->truc->data.sta.nom);
		
		
		
		Un_elem* liste_dans_zone;
		
		Une_coord Lim_SE;
		Lim_SE.lat = 48.8963;
		Lim_SE.lon = 2.35; 
		
		
		Une_coord Lim_NO;
		Lim_NO.lat = 48.8310;
		Lim_NO.lon = 2.36;
		
		
		printf("\n\nDES LIMITES ONT ÉTÉ DÉFINIES, ON VA MAINTENANT TESTER CHERCHER_AQR\n");
		
		Un_truc* machin = chercher_aqr(nouvel_aqr, Lim_NO);
		
		if (machin == NULL) printf("y'a eu un pb\n");
		
		printf("résultat de chercher_aqr = %s\n", machin->data.sta.nom);
		
		printf("\n\nFIN\n\n");
		
		printf("\nON VA MAINTENANT TESTER LA FONCTION CHERCHER_ZONE AVEC DES LIMITES DÉFINIES VOLONTAIREMENT DANS LE MAIN\n");
		
		liste_dans_zone = NULL;
		
		liste_dans_zone = chercher_zone(nouvel_aqr, liste_dans_zone, Lim_NO, Lim_SE);
		
		printf("\nON AFFICHE LA LISTE DES STATION COMPRISES DANS LA ZONE RENSEIGNÉE :\n");
		
		afficher_station_dans_liste(liste_dans_zone);
		
		printf("FIN DE TOUS LES TESTS, TOUTES LES FONCTIONS DANS LE PROJET ONT NORMALEMENT BIEN FONCTIONNÉES\nMerci d'avoir utilisé le programe. ^_^\n");
	return 0;
}
