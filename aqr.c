#include <stdlib.h>
#include <stdio.h>
#include <string.h>



//Fonctions définies dans ce module



Un_noeud *creer_noeud(Un_truc *truc);
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

    if (!truc) return aqr;                                  //Cas où new est NULL
    if (!aqr) return creer_noeud(truc);                     //Cas où aqr est NULL

    if (truc->coord.lon > aqr->truc->coord.lon){            //Comparaison lat
            if (truc->coord.lat > aqr->truc->coord.lat) 
            aqr->ne = inserer_aqr(aqr->ne, limite_no, limite_se, truc);
        else 
            aqr->se = inserer_aqr(aqr->se, limite_no, limite_se, truc);
    }
    else {
        if (truc->coord.lat > aqr->truc->coord.lat) 
            aqr->no = inserer_aqr(aqr->no, limite_no, limite_se, truc);
        else 
            aqr->so = inserer_aqr(aqr->so, limite_no, limite_se, truc);
    }

    return aqr;
}



Un_noeud *construire_aqr(Un_elem *liste){
    //Construit un aqr à partir d'une liste de trucs

    if(!liste) return NULL; 

    Un_noeud * aqr = creer_noeud(liste->truc);                  //La racine de l'aqr est le 1er élément de la liste
    aqr = inserer_aqr(new, construire_aqr(liste->suiv));        //Insertion des éléments de liste dans l'aqr

    return aqr
}



void detruire_aqr(Un_noeud *aqr){
    //Détruit un aqr

    if (!aqr) return;           //Cas où aqr est vide

    if( (!aqr->no) && (!aqr->so) && (!aqr->ne) && (!aqr->se))       //Cas où aqr est l dernier élément de la branche
        free(aqr); 

    else {
        if (aqr->no)            //Destruction des différentes branches
            detruire_aqr(aqr->no);
        if (aqr->ne)
            detruire_aqr(aqr->ne);
        if (aqr->so)
            detruire_aqr(aqr->so); 
        if (aqr->se)
            detruire_aqr(aqr->so);
    }

    free(aqr);
    
}
