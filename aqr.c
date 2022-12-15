#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "aqrtopo.h"


//Ce module contient les fonctions permmettant la création et manipulation d'AQR



//Fonctions définies dans ce module


Un_noeud *creer_noeud(Un_truc *truc, Une_coord limite_no, Une_coord limite_se);
Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc);
Un_noeud *construire_aqr(Un_elem *liste); 
void detruire_aqr(Un_noeud *aqr);
Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord); 
Un_elem *chercher_zone(Un_noeud *aqr, Un_elem *liste, Une_coord limite_no, Une_coord limite_se);
void afficher_aqr(Un_noeud *aqr);


//Définition des fonctions



Un_noeud *creer_noeud(Un_truc *truc, Une_coord limite_no, Une_coord limite_se) {
    //Crée d'un noeud d'AQR

    if (!truc) {
        printf("Truc = NULL\n");
        return NULL;
    }

    Un_noeud *noeud = (Un_noeud *) malloc(sizeof(Un_noeud));
    if(!noeud){
        printf("ERREUR\n"); 
        return NULL;
    }

    noeud->truc = truc;
    noeud->no = NULL;
    noeud->ne = NULL;
    noeud->so = NULL;
    noeud->se = NULL;

    noeud->limite_no = limite_no;
    noeud->limite_se = limite_se;

    return noeud;
}



Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc){
    //Insert un truc dans l'AQR

    if (!truc) return aqr;                                  //Cas où new est NULL
    if (!aqr) return creer_noeud(truc, limite_no, limite_se);                     //Cas où aqr est NULL

    if (truc->coord.lon > aqr->truc->coord.lon){                                //Comparaison lon 
            if (truc->coord.lat > aqr->truc->coord.lat)                         //Comparaison lat
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

    return creer_noeud(truc, limite_no, limite_se); 
}



Un_noeud *construire_aqr(Un_elem *liste){
    //Construit un aqr à partir d'une liste de trucs

    if(!liste) return NULL; 

    Une_coord limite_no, limite_se;
    limites_zone(liste, &limite_no, &limite_se);

    Un_noeud * aqr = creer_noeud(liste->truc, limite_no, limite_se);            //La racine de l'aqr est le 1er élément de la liste
    
    while(liste->suiv){
        liste = liste->suiv;
        aqr = inserer_aqr(aqr, limite_no, limite_se, liste->truc);        //Insertion des éléments de liste dans l'aqr
    }
    
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

    // free(aqr);
}


Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord){
    //Cherche un truc dont la coord se trouve dans l'aqr

    if (!aqr) return NULL;
    printf("\n\t coord : %f, %f", coord.lon, coord.lat);
    printf("\n\t aqr : %f, %f\n", aqr->truc->coord.lon,aqr->truc->coord.lat);

    if ((aqr->truc->coord.lon == coord.lon) && (aqr->truc->coord.lat == coord.lat)){               //Cas où aqr est l'élément cherché
        printf("in AQR : found\n");
        return aqr->truc;
    }

    else if (aqr->truc->coord.lon > coord.lon){
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
    
    if ((aqr->limite_no.lon > limite_no.lon) && (aqr->limite_no.lat < limite_no.lat)){          
        if ((aqr->limite_se.lon < limite_se.lon) && (aqr->limite_se.lat > limite_se.lat))
            liste = inserer_liste_trie(liste, aqr->truc);                       // Si le noeud appartient à la zone, il est ajouté à la zone
    }
    
    if (aqr->no)
        liste = chercher_zone(aqr->no, liste, limite_no, limite_se);
    if (aqr->ne)
        liste = chercher_zone(aqr->ne, liste, limite_no, limite_se);
    if (aqr->so)
        liste = chercher_zone(aqr->so, liste, limite_no, limite_se);
    if (aqr->se)
        liste = chercher_zone(aqr->se, liste, limite_no, limite_se);

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