#include <stdlib.h>
#include <string.h>

#include "truc.h"
#include "abr_type.h"



Un_nabr *creer_nabr(Un_truc *truc) {
    /*Fonction de création d'un noeud d'arbre binaire de recherche*/

    Un_nabr * nabr = (Un_nabr * ) malloc(sizeof(Un_nabr));

    nabr->g = NULL;
    nabr->d = NULL;
    nabr->truc = truc; 

    return nabr;
}



Un_nabr *inserer_abr(Un_nabr *abr, Un_nabr *n) {
    /*Fonction d'insertion d'un noeud dans un ABR*/

    if(!n) return abr;
    if(!abr) return n; 

    if(strcmp(n->truc->data.sta.nom, abr->truc->data.sta.nom))
        abr->g = inserer_abr(abr->g, n);
    
    else 
        abr->d = inserer_abr(abr->d, n);
}



Un_nabr *construire_abr(Un_elem *liste_sta) {
    /*Fonction de création d'un ABR à partir d'une liste de stations*/

    if(! liste_sta) return NULL;

    Un_nabr n = creer_nabr(*liste_sta);
    n = inserer_abr(n, construire_abr(*(liste_sta+1)));

    return n;
}



void detruire_abr(Un_nabr *abr) {
    /*Fonction de destruction d'un ABR*/

    if (! abr) retrun; 

    if (!abr->d && !abr->g) 
        free(abr); 
    
    else {
        if (abr->d) detruire_abr(abr->d);
        if (abr->g) detruire_abr(abr->g);
    }
    
    free(abr);
}



Un_truc *chercher_station(Un_nabr *abr, char *nom); {
    /*Fonction permettant de rechercher une station dans un ABR*/

    if (!abr) 
        return NULL; 

    int comp = strcmp(abr->truc->data.sta.nom,nom);

    if(!comp)         //La fonction vaut 0 si les deux chaines sont égales
        return abr;
    
    if (comp<0)
        return chercher_station(abr->d, nom);           //Elle est négative si s1<s2
    
    else 
        return chercher_station(abr->g, nom);           //Positive si s1>s2

}