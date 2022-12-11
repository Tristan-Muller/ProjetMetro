#include <stdlib.h>
#include <stdio.h>
#include <string.h>



//Fonctions définies dans ce module



Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc);
Un_noeud *construire_aqr(Un_elem *liste); 
void detruire_aqr(Un_noeud *aqr);
Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord); 
Un_elem *chercher_zone(Un_noeud *aqr, Un_elem *liste, Une_coord limite_no, Une_coord limite_se);



//Définition des fonctions



Un_noeud *creer_noeud(Un_truc *truc) {
    //Crée d'un noeud d'AQR

    if (!truc) {
        printf("Truc = NULL\n");
        return NULL;
    }

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
    //Insert un truc dans l'AQR

    Un_noeud * new = creer_noeud(truc);     //On crée un nouvreau noeud à partir du truc
    if (!new) return aqr;                   //Cas où new est NULL

    if (!aqr) return new;                   //Cas où aqr est NULL

    

    return aqr;
}