#include <stdlib.h>
#include <stdio.h>
#include "coord.h"
#include "station.h"
#include "truc.h"
#include "liste.h"
#include "truc.c"

Une_ligne *lire_lignes(char *nom_fichier){

    FILE* fic = NULL;
 
    char code;
    int v_moy = 0; 
    float interval = 0;
    char color[15];
 
    fic = fopen(nom_fichier, "r");

    if (!fic) return NULL; 

    fscanf(fic, "%c;%d;%f;%s", &code, &v_moy, &interval, color);

    printf("\nCode : %c\nVitesse : %d\nIntervalle : %f\nCouleur : %s", code, v_moy, interval, color);

    
    fscanf(fic, "%c;%d;%f;%s", &code, &v_moy, &interval, color);

    printf("\nCode : %c\nVitesse : %d\nIntervalle : %f\nCouleur : %s", code, v_moy, interval, color);
     //Ne marche pas pour l'instant mais je teste 


    fclose(fic);
    
 
    return NULL;
}



void afficher_lignes(Une_ligne *lligne){}



void detruire_lignes(Une_ligne *lligne){}



Une_ligne *chercher_ligne(Une_ligne *lligne, char *code){
    return NULL;
} 