#include <stdlib.h>
#include <stdio.h>
#include "coord.h"
#include "station.h"
#include "truc.h"
#include "liste.h"
#include "truc.c"

//lligne : liste de lignes

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
    }

    fclose(fic);
 
    return lligne;
}



Une_ligne * ajout_ligne(Une_ligne *lligne, char *code, float v_moy, float interval, char *color){
    /*fonction d'ajout d'une nouvelle ligne à une liste de ligne*/

    Une_ligne * new = (Une_ligne *) malloc(sizeof(Une_ligne *));
    if(!new){
        printf("ERREUR\n");
        return NULL;
    } 

    strcpy(new->code, code);
    new->vitesse = v_moy;
    new->intervalle = intervalle; 
    strcpy(new->color, color);

    if (!lligne){
        return new; 
    }

    Une_ligne * temp = lligne;

    while(temp->suiv){
        
    }


    return lligne;     
}



void afficher_lignes(Une_ligne *lligne){}



void detruire_lignes(Une_ligne *lligne){}



Une_ligne *chercher_ligne(Une_ligne *lligne, char *code){
    return NULL;
} 