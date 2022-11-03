#include <stdio.h>

Une_ligne *lire_lignes(char *nom_fichier){

    FILE* fichier = NULL;
    int i =0;
 
    char tab[200]={0};
 
    fichier = fopen("nombres.csv", "r");
 
    if (fichier != NULL)
    {
       for(i = 0; i < 200; i++)
       {
       fscanf(fichier, "%f ", &tableau[i]);
       }
        fclose(fichier);
    }
 
    return 0;
 
}



void afficher_lignes(Une_ligne *lligne){}



void detruire_lignes(Une_ligne *lligne){}



Une_ligne *chercher_ligne(Une_ligne *lligne, char *code){} 