#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"
#include "truc.h"
#include "abr_type.h"
#include "abr.h"
#include "ligne.h"
#include "aqrtopo.h"

#include "truc.c"
#include "liste.c"
#include "abr.c"
#include "ligne.c"
#include "aqr.c"


// #include <SDL.h>
// #define WINDOW_WIDTH 1280
// #define WINDOW_HEIGHT 720


// Ce module contient la fonction main, qui permet l'execution de notre programme



// Définition des fonctions


void msg (int ok) {
    // Affiche les messages

    if(ok ==-2){
        printf("Erreur à l'ouverture du fichier\n");
        printf("Arret du programme\n");
    } 

    else if(ok ==-1){
        printf("Erreur d'allocation mémoire\n");
        printf("Arret du programme\n");
    } 

    else if (ok == 0){
        printf("\n---------------------------------------------------------------\n");
        printf("\nBienvenue dans le projet metro de Trisan Muller et Merlin Fouché\n");
        printf("\nDébut des tests\n");
    }

    else {
        printf("Si vous lisez ce message, c'est que tous les tests des différentes fonctions ont été réalisés et ont fonctionné\n");
        printf("Très bonne journée à vous\n");
    }
    
}



void pause(){
    // Permet une pause entre les affichages, pour éviter une surcharge du terminal

    int pause = 0;
    printf("\n\nEnter 1 to continue\n");
    scanf("%d", &pause);

    system("clear");
}



int main (){
    int ok = 0;                                             // Variable permettant d'afficher les messages adéquats

    char *write_in = "liste_station.csv";                   //Définitions des différents noms de fichiers 
    char *read_in  = "flux.csv";
    char *ligne_fic = "ligne.csv";
    char *connex_fic = "connexion.csv";

    char *nom_sta_cherch = "Sainte Anne";                         //Définitions des noms recherchés
    char *nom_ligne_cherch = "A";

    msg(ok);                                                // Message de bienvenue
    ok++;



    pause();



    printf("\n---TEST STATION---\n\n");

    printf("\nExtraction d'une liste de stations à partir du fichier \"%s\"\n", read_in);
    Un_elem* liste_sta = lire_stations(read_in);

	printf("\nListe des stations : \n\n");
	affiche_station(liste_sta);

    FILE* fic = fopen (write_in, "w");                      // On ecrit les stations récupérées dans le fichier liste_stations.csv
	if (!fic){                                              // if !fic <=> if fic == NULL
        msg(-2);
		return 0;
    }

    printf("\nOuverture de \"%s\" en mode ecriture\n", write_in);
	printf("Ecriture des stations dans %s\n", write_in);
	ecrire_liste(fic , liste_sta);

	printf("Fin de l'écriture, fermeture de \"%s\"\n", write_in);
	fclose(fic);

	Une_coord limite_no;
	Une_coord limite_se;

    printf("\nCalcul de la limite de zone des stations\n");
	limites_zone(liste_sta , &limite_no , &limite_se);
    printf("La zone est définie par les limites : : \n");
    printf("NO : \tlon = %f \tlat = %f\net\n ", limite_no.lon, limite_no.lat);
    printf("SE : \tlon = %f \tlat = %f\n", limite_se.lon, limite_se.lat);
    
    printf("\n---TEST STATION - FIN ---\n\n");



    pause();



	printf("\n---TEST ABR---\n\n");

    printf("Construction d'un abr à partir de la liste de stations\n");
	Un_nabr* abr = construire_abr(liste_sta);

    printf("Affichage de l'abr : \t(les . représentent les fins de branches)\n");
    afficher_abr(abr); 

    Un_truc *cherch_sta; 
    printf("Recherche de la station \"%s\" dans l'abr\n", nom_sta_cherch);
	cherch_sta = chercher_station(abr , nom_sta_cherch);
    printf("Resultat de la recherche : \n");
    if (!cherch_sta)
        printf("NULL\n");
    else 
        printf("%s ; %f ; %f\n", cherch_sta->data.sta.nom, cherch_sta->coord.lat, cherch_sta->coord.lon);

    printf("\n---TEST ABR - FIN ---\n\n");



    pause();



    printf("\n---TEST LIGNES---\n\n");

	Une_ligne *ligne;
	Une_ligne *cherch_ligne;

    printf("Recupération d'une liste de lignes à partir du fichier \" %s \"\n", ligne_fic);
	ligne = lire_lignes(ligne_fic);

    printf("Affichage de la liste de ligne : \n");
	afficher_lignes(ligne);

    printf("\nRecherche de la ligne %s dans la liste\n", nom_ligne_cherch);
	cherch_ligne = chercher_ligne(ligne , nom_ligne_cherch);
    printf("Resultat de la recherche : \n");
    afficher_lignes(cherch_ligne);

    printf("\n---TEST LIGNES - FIN ---\n\n");



    pause();



    printf("\n---TEST CONNEXIONS---\n\n");

    Un_elem* liste_con;
    printf("Création d'une liste de connexions à partir du fichier \"%s\"\n", connex_fic);
	liste_con = lire_connexions(connex_fic, abr); 

    printf("\n---TEST CONNEXIONS - FIN---\n\n");



    pause();



    printf("\n---TEST AQR---\n\n");

    Un_noeud* aqr;
    printf("Construction d'un AQR à partir de la liste de stations\n");
    aqr = construire_aqr(liste_sta);
    if (!aqr) {
        msg(-1);
        return 0;
    }

    Une_coord zone_no;
    Une_coord zone_se;
    zone_no.lon = limite_no.lon+0.01;
    zone_no.lat = limite_no.lat-0.01;
    zone_se.lon = limite_se.lon-0.01;
    zone_se.lat = limite_se.lat+0.01;
    
    Un_truc *cherch_aqr = NULL;
    printf("\nRecherche d'un élément dans l'aqr\n");
    printf("Ici on cherche le 2e élément de la liste : %s", liste_sta->truc->data.sta.nom);
    cherch_aqr = chercher_aqr(aqr, liste_sta->truc->coord);
    if (!cherch_aqr)
        printf("\nElement non trouvé\n");
    else 
        printf("%s\n", cherch_aqr->data.sta.nom);

    Un_elem* liste_dans_zone = NULL;
    printf("\nRecherche d'une zone dans l'aqr\n"); 
    printf("Ici on choisi la zone définie par : \n");
    printf("NO : \tlon = %f \tlat = %f\net\n ", zone_no.lon, zone_no.lat);
    printf("SE : \tlon = %f \tlat = %f\n", zone_se.lon, zone_se.lat);
    liste_dans_zone = chercher_zone(aqr, liste_dans_zone, zone_no, zone_se);
    printf("Résultat de la recherche : \n");
    affiche_station(liste_dans_zone);
    
    printf("\n---TEST AQR - FIN---\n\n");



    pause();

    printf("\n---TEST PLUS COURT CHEMIN\n\n");

    char stat_dep[50];
    char* stat_arr;
    printf("Voici la liste des stations : \n\n");
    affiche_station(liste_sta);

    printf("\nChoisissez votre station de départ : ");
    scanf("%s", stat_dep);
    printf("\n");

    printf("\nChoisissez votre station d'arrivée : ");
    scanf("%s", stat_arr);

    Un_truc* dep = chercher_station(abr , stat_dep);

    dijkstra(liste_sta, dep);
    printf("\n");

    Un_elem* co = cherche_chemin();
    printf("Pour arriver jusque : %s, il faut passer par :\n", stat_arr);
    while(co->suiv!=NULL){
        printf("%s \npuis ", co->truc->data.con.sta_dep->data.sta.nom);
        co = co->suiv;
    }


    printf("\n---TEST PLUS COURT CHEMIN - FIN---\n\n");

    //pause();


    printf("\n--- Libération Mémoire ---\n\n");

    printf("Libération de la mémoire des liste de stations, de connexions et de lignes\n");
	// detruire_liste_et_truc(liste_sta);
    detruire_liste_et_truc(liste_con);
    // detruire_lignes(ligne);
    printf("Libération de la mémoire de l'aqr\n");
    detruire_aqr(aqr);

    printf("\n--- Libération Mémoire - Fin  ---\n\n");

    msg(ok);
    
	return 0;
}
