#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "coord.h"
#include "aqrtopo.h"
#include "ligne.h"
#include "liste.h"




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

    Un_noeud *noeud = (Un_noeud *) malloc(sizeof(Un_noeud *));
    if(!noeud){
        printf("ERREUR\n"); 
        return NULL;
    }

    noeud->truc = truc;
    noeud->no = NULL;
    noeud->ne = NULL;
    noeud->so = NULL;
    noeud->se = NULL;

    noeud->limite_no.lon = 0;
    noeud->limite_no.lat = 0;
    noeud->limite_se.lon = 0;
    noeud->limite_se.lat = 0;

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
}



Un_noeud *construire_aqr(Un_elem *liste){
    //Construit un aqr à partir d'une liste de trucs

    if(!liste) return NULL; 

    Un_noeud * aqr = creer_noeud(liste->truc);                  //La racine de l'aqr est le 1er élément de la liste
    aqr = inserer_aqr(aqr, aqr->limite_no, aqr->limite_se, liste->suiv->truc);        //Insertion des éléments de liste dans l'aqr

    return aqr;
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
            detruire_aqr(aqr->se);
    }

    free(aqr);
}


Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord){
    //Cherche un truc dont la coord se trouve dans l'aqr

    if (!aqr) return NULL;

    if ((aqr->truc->coord.lon == coord.lon) && (aqr->truc->coord.lat == coord.lat)){               //Cas où aqr est l'élément cherché
        printf("in AQR : found\n");
        return aqr->truc;
    }

    if (aqr->truc->coord.lon > coord.lon){
        if(aqr->truc->coord.lat > coord.lat)
            return chercher_aqr(aqr->ne, coord); 
        else 
            return chercher_aqr(aqr->se, coord); 
    }
    else {
        if(aqr->truc->coord.lat > coord.lat)
            return chercher_aqr(aqr->no, coord); 
        else 
            return chercher_aqr(aqr->so, coord);
    }
}



Un_elem *chercher_zone(Un_noeud *aqr, Un_elem *liste, Une_coord limite_no, Une_coord limite_se){
    //Renvoie une liste de trucs qui sont dans la zone définie par les limites _no et _se

    if (!aqr)                       //Cas où l'aqr est vide 
        return liste;               //On retourne la liste (doute là dessus)

    int i = 0;
    Un_elem *elem = liste;

    while (elem->suiv) {
        elem = elem->suiv;
    }
    
    if ((aqr->truc->coord.lon > limite_no.lon) && (aqr->truc->coord.lat < limite_no.lat)){
        if ((aqr->truc->coord.lon < limite_se.lon) && (aqr->truc->coord.lat > limite_se.lat))
            i++;

    }

    return liste;
}



void afficher_aqr(Un_noeud * aqr){
    // Affiche les noeuds d'un aqr (fonction de test)
    if (!aqr) return;

    if (aqr->truc->type == STA)
        printf("Sta : %s\n", aqr->truc->data.sta.nom);
    else 
        printf("Sta_dep : %s\n", aqr->truc->data.con.sta_dep->data.sta.nom);

    if (aqr->ne) 
        afficher_aqr(aqr->ne);
    if (aqr->no)
        afficher_aqr(aqr->no);
    if (aqr->se)
        afficher_aqr(aqr->se);
    if (aqr->so)
        afficher_aqr(aqr->so);

}