#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "coord.h"
#include "station.h"
#include "truc.h"
#include "liste.h"
#include "truc.c"
#include "ligne.h"


//lligne : liste de lignes



void afficher_lignes(Une_ligne *lligne){
    /*Fonction qui permet d'afficher les lignes présentes dans la liste de ligne lligne*/
    if(!lligne) {
        printf("lligne == NULL\n");
        return; 
    }

    printf("\n Code de la ligne : %s\n  Couleur : %s\n  Vitesse : %f\n  Intervalle moyen : %f\n", lligne->code, lligne->color, lligne->vitesse, lligne->intervalle);

    if (lligne->suiv){
        afficher_lignes(lligne->suiv);}
}



Une_ligne * ajout_ligne(Une_ligne *lligne, char *code_fic, float v_moy, float interval, char *color_fic){
    /*fonction d'ajout d'une nouvelle ligne à une liste de ligne*/

    Une_ligne * new = (Une_ligne *) malloc(sizeof(Une_ligne));        //On crée un nouvel élément pour stocker des donnée transmises 
    if(!new){
        printf("ERREUR\n");
        return NULL;
    } 

    
    new->code = (char *) malloc(strlen(code_fic)*sizeof(char));
    new->color = (char *) malloc(strlen(color_fic)*sizeof(char));


    strcpy(new->code, code_fic);                                         //On y ajoute les données
    strcpy(new->color, color_fic);
    new->vitesse = v_moy;
    new->intervalle = interval;
    new->suiv = NULL;

    if (!lligne){                                                       //Si la liste est vide, la 1ere ligne
        return new; 
    }

    new->suiv = lligne;

    return new;     
}



Une_ligne *lire_lignes(char *nom_fichier){
    /*parcours le fichier .csv fournis en argument et construit la liste de Une_ligne correspondante*/

    FILE* fic = NULL; 
    fic = fopen(nom_fichier, "r");
    if (!fic) return NULL; 

    char code_fic[10] = {0};
    float v_moy = 0; 
    float interval = 0;
    char color_fic[15] = {0};
    int ok =  fscanf(fic, "%s ; %f ; %f ; %s", code_fic, &v_moy, &interval, color_fic);

    printf("Test_before : color : %s\n", color_fic);

    Une_ligne * lligne = NULL; 

    while ( ok != EOF){
        lligne = ajout_ligne(lligne, code_fic, v_moy, interval, color_fic);
        ok = fscanf(fic, "%s ; %f ; %f ; %s", code_fic, &v_moy, &interval, color_fic);
    }

    printf("Test_after : color : %s\n", lligne->suiv->color);

    afficher_lignes(lligne); 

    fclose(fic);
 
    return lligne;
}



void detruire_lignes(Une_ligne *lligne){
    /*fonction permettant de libérer la mémoire de la liste de ligne*/

    if(!lligne) return; 

    if(!lligne->suiv){ 
        free(lligne->color);
        free(lligne->code);
        free(lligne);
    }

    else {
        Une_ligne * temp = lligne; 
        lligne = lligne->suiv; 
        free(temp->code);
        free(temp->color);
        free(temp); 
        detruire_lignes(lligne);
    }
}



Une_ligne *chercher_ligne(Une_ligne *lligne, char *code){
    /*Fonction qui permet de chercher une ligne dans lligne dont le code correspond à celui transmis en agrument*/
    if (!lligne) return NULL; 

    if(!strcmp(lligne->code, code)) {
        printf("Found\n");
        return lligne;
    }
    if(lligne->suiv)
        return chercher_ligne(lligne->suiv, code);

    return NULL;
} 