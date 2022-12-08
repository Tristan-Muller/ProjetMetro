#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc);
Un_noeud *construire_aqr(Un_elem *liste); 
void detruire_aqr(Un_noeud *aqr);
Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord); 
Un_elem *chercher_zone(Un_noeud *aqr, Un_elem *liste, Une_coord limite_no, Une_coord limite_se);


Un_noeud *creer_noeud(Un_truc *truc) {
    /*Fonction de création d'un noeud d'AQR*/

    Un_noeud noeud = (Un_noeud *) malloc(sizeof(Un_noeud *));
    if(!noeud){
        printf("ERREUR\n"); 
        return NULL
    }

    noeud->truc = truc;
    noeud->no = NULL;
    noeud->ne = NULL;
    noeud->so = NULL;
    noeud->se = NULL;

    noeud->limite_no = 0;
    noeud->limite_se = 0;

    return noeud;
}


Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc){
    /*Fonction d'insertion d'un truc dans l'AQR*/

    Un_noeud * new = creer_noeud(truc);
    if (!new) return aqr;
    if (!aqr) return new;  

    

    return aqr;
}