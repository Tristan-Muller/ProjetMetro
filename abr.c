#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abr_type.h"
#include "abr.h"



//Definition des fonctions

Un_nabr *creer_nabr(Un_truc *truc) {
    //Crée un noeud d'abr

    Un_nabr* nabr = (Un_nabr * ) malloc(sizeof(Un_nabr));
    if (!nabr){
        printf("Erreur\n");
        return NULL;
    }

    nabr->g = NULL;
    nabr->d = NULL;
    nabr->truc = truc; 

    return nabr;
}



Un_nabr *inserer_abr(Un_nabr *abr, Un_nabr *n) {
    //Insert d'un noeud dans un ABR

    if(n==NULL) return abr;
    if(abr==NULL) return n; 

    if(strcmp(n->truc->data.sta.nom, abr->truc->data.sta.nom)<0)
        abr->g = inserer_abr(abr->g,n);
    else 
        abr->d = inserer_abr(abr->d,n);

    return abr;
}



Un_nabr *construire_abr(Un_elem *liste_sta) {
    //Crée un ABR à partir d'une liste de stations

    if(liste_sta==NULL) return NULL;

    Un_nabr* abr= creer_nabr(liste_sta->truc);

    liste_sta = liste_sta->suiv;

    while (liste_sta!=NULL){
        Un_nabr* new = creer_nabr(liste_sta->truc); 
        abr = inserer_abr(abr, new); //Tu avais mis *liste_sta +1 mais ce n'est pas un nombre donc je pense que t'avais voulu dire suivant
        liste_sta = liste_sta->suiv;
    }

    return abr;
}



void detruire_abr(Un_nabr *abr) {
    //Detruit un ABR

    if (! abr) return;      //Cas où abr est vide 

    if (!abr->d && !abr->g)         //Cas où abr est le dernier élément de la branche
        free(abr); 
    
    else {                          //Cas général
        if (abr->d) detruire_abr(abr->d);
        if (abr->g) detruire_abr(abr->g);
    }
    
    free(abr);
}



Un_truc *chercher_station(Un_nabr *abr, char *nom){
    /*Fonction permettant de rechercher une station dans un ABR*/
    
    if (nom==NULL){
        printf("Pas de nom de station en argument\n");
        return NULL;
    }

    if (abr==NULL){
        printf("Pas trouvé\n");
        return NULL; 
    }

    //printf("%s\n", abr->truc->data.sta.nom);

    int comp = strcmp(abr->truc->data.sta.nom, nom);
    //printf("\t nom abr : %s\n\n", abr->truc->data.sta.nom);

    if(!comp)                                           //La fonction vaut 0 si les deux chaines sont égales
        return abr->truc;
    
    if (comp<0){
        //printf("\t going d\n");
        return chercher_station(abr->d, nom);           //Elle est négative si s1<s2
    }
    
    else {
        //printf("\t going g\n");
        return chercher_station(abr->g, nom);           //Positive si s1>s2
    }
}



void afficher_abr(Un_nabr *abr){
    // Affiche les noeuds d'un abr (fonction de test)
    if (!abr) {
        printf("##End of abr##\n"); 
        return;
    }

    if (abr->truc->type == STA)
        printf("Sta : %s\n", abr->truc->data.sta.nom);
    else 
        printf("Sta_dep : %s\n", abr->truc->data.con.sta_dep->data.sta.nom);

    if (abr->d) 
        afficher_abr(abr->d);
    if (abr->g)
        afficher_abr(abr->g);
    
    if (!(abr->g) && !(abr->d))
        printf(".\n");

}