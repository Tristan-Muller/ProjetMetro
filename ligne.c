#include <stdlib.h>
#include <stdio.h>
#include "coord.h"
#include "station.h"
#include "truc.h"
#include "liste.h"
#include "truc.c"


//lligne : liste de lignes



void afficher_lignes(Une_ligne *lligne){
    if(!lligne) return; 
    printf("Test1\n");
    printf("\n Code de la ligne : %s\n  Couleur : %s\n  Vitesse : %f\n  Intervalle moyen : %f\n", lligne->code, lligne->color, lligne->vitesse, lligne->intervalle);

    if (lligne->suiv){
        printf("Oh2\n");
        afficher_lignes(lligne->suiv);}
}



Une_ligne * ajout_ligne(Une_ligne *lligne, char *code, float v_moy, float interval, char *color){
    /*fonction d'ajout d'une nouvelle ligne à une liste de ligne*/

    Une_ligne * new = (Une_ligne *) malloc(sizeof(Une_ligne *));        //On crée un nouvel élément pour stocker des donnée transmises 
    if(!new){
        printf("ERREUR\n");
        return NULL;
    } 

    if(new->suiv) new->suiv = NULL;

    new->code = code;                                          //On y ajoute les données
    new->color = color;
    new->vitesse = v_moy;
    new->intervalle = interval;

    if (!lligne){                                                       //Si la liste est vide, la 1ere lignez
        return new; 
    }

    Une_ligne * temp = lligne;

    while(temp->suiv){
        temp = temp->suiv;
    }

    temp->suiv = new; 

    return lligne;     
}



Une_ligne *lire_lignes(char *nom_fichier){
    /*parcours le fichier .csv fournis en argument et construit la liste de Une_ligne correspondante*/

    FILE* fic = NULL; 
    fic = fopen(nom_fichier, "r");
    if (!fic) return NULL; 

    char code[10];
    float v_moy = 0; 
    float interval = 0;
    char color[15];

    Une_ligne * lligne = NULL;  

    while (fscanf(fic, "%s ; %f ; %f ; %s", code, &v_moy, &interval, color) != EOF){
        lligne = ajout_ligne(lligne, code, v_moy, interval, color);   
        afficher_lignes(lligne);      
    }

    fclose(fic);
 
    return lligne;
}



void detruire_lignes(Une_ligne *lligne){
    if(!lligne) return; 
    if(!lligne->suiv) free(lligne);
    else {
        Une_ligne * temp = lligne; 
        lligne = lligne->suiv; 
        free(temp); 
        detruire_lignes(lligne);
    }
}



Une_ligne *chercher_ligne(Une_ligne *lligne, char *code){
    return NULL;
} 