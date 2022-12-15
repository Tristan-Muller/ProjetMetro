#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "coord.h"
#include "station.h"
#include "liste.h"
#include "ligne.h"


// Ce module contient les fonctions permettant de traiter le dossier ligne.csv


// Terminologie : 
// lligne : liste de lignes


//Fonction contenues dans ce module : 

void afficher_lignes(Une_ligne *lligne);
Une_ligne *ajout_ligne(Une_ligne *lligne, char *code_fic, float v_moy, float interval, char *color_fic);
Une_ligne *lire_lignes(char *nom_fichier);
void detruire_lignes(Une_ligne *lligne);
Une_ligne *chercher_ligne(Une_ligne *lligne, char *code);



//Définition des fonctions : 


void afficher_lignes(Une_ligne *lligne){
    //Affiche les lignes présentes dans la liste de ligne lligne

    if(!lligne) {
        printf("La liste est nulle\n");
        return; 
    }

    printf("\n Code : %s\n  Couleur : %s\n  Vitesse : %f\t Intervalle moyen : %f\n", lligne->code, lligne->color, lligne->vitesse, lligne->intervalle);

    if (lligne->suiv){
        afficher_lignes(lligne->suiv);}
}



Une_ligne *ajout_ligne(Une_ligne *lligne, char *code_fic, float v_moy, float interval, char *color_fic){
    //Ajout d'une nouvelle ligne à une liste de ligne

    Une_ligne * new = (Une_ligne *) malloc(sizeof(Une_ligne));        //On crée un nouvel élément pour stocker des donnée transmises 
    if(!new){
        printf("ERREUR\n");
        return NULL;
    } 

    new->code = (char *) malloc(strlen(code_fic)*sizeof(char));         //Les string de ligne doivent avoir un malloc
    new->color = (char *) malloc(strlen(color_fic)*sizeof(char));


    strcpy(new->code, code_fic);                                         //On y ajoute les données
    strcpy(new->color, color_fic);
    new->vitesse = v_moy;
    new->intervalle = interval;
    new->suiv = NULL;

    if (!lligne){                                                       //Si la liste est vide, on renvoie le nouvel élément
        return new; 
    }

    new->suiv = lligne;                                                 //Sinon, on ajoute la nouvelle ligne en tête de liste et on renvoie cette nouvelle liste  
    return new;     
}



Une_ligne *lire_lignes(char *nom_fichier){
    //Parcours le fichier .csv fournis en argument et construit la liste de Une_ligne correspondante

    FILE* fic = NULL; 
    fic = fopen(nom_fichier, "r");                                      //Ouverture du fichier en mode lecture
    if (!fic) {
        printf("ERREUR\n");
        return NULL; 
    }

    char code_fic[10] = {0};                                            //On crée les variables qui vont récupérer les données du fichier
    float v_moy = 0; 
    float interval = 0;
    char color_fic[15] = {0};
    int ok =  fscanf(fic, "%s ; %f ; %f ; %s", code_fic, &v_moy, &interval, color_fic);     //Première lecture du chier

    Une_ligne * lligne = NULL;                                          //Liste de ligne du fichier

    while ( ok != EOF){                                                 //On lit le fichier jusqu'à la fin
        lligne = ajout_ligne(lligne, code_fic, v_moy, interval, color_fic);
        ok = fscanf(fic, "%s ; %f ; %f ; %s", code_fic, &v_moy, &interval, color_fic);
    }

    fclose(fic);
 
    return lligne;
}



void detruire_lignes(Une_ligne *lligne){
    //Libère la mémoire de la liste de ligne

    if(!lligne) return;                 //Cas où la liste est nulle

    if(!lligne->suiv){                  //Cas où la liste n'a qu'un seul élément
        free(lligne->color);
        free(lligne->code);
        free(lligne);
    }

    else {                              //Cas général
        Une_ligne * temp = lligne; 
        lligne = lligne->suiv; 
        free(temp->code);
        free(temp->color);
        free(temp); 
        detruire_lignes(lligne);        //On itère sur le prochain élément
    }
}



Une_ligne *chercher_ligne(Une_ligne *lligne, char *code){
    //Cherche une ligne dans lligne dont le code correspond à celui transmis en agrument
    if (!lligne) return NULL; 

    if(!strcmp(lligne->code, code)) {       //strcmp vaut 0 si les str sont identiques
        return lligne;                      //Dans ce cas, on renvoie l'élément trouvé
    }
    if(lligne->suiv)                        //Sinon, on itère sur l'élément suivant
        return chercher_ligne(lligne->suiv, code);

    return NULL;
} 




/*

//test :

int main(){
    Une_ligne * lligne = lire_lignes("ligne.csv");      //Test de lire_ligne
    afficher_lignes(lligne);                            //Test de afficher_ligne

    Une_ligne * elem = NULL;
    elem = chercher_ligne(lligne, "A");                 //Test de chercher_ligne
    afficher_lignes(elem);

    detruire_lignes(lligne);                            //Test de detruire_ligne

    printf("Memory Freed\n");                           //Ici on ne fait pas de malloc sur elem, on n'a donc pas à le free
    return 0;
}

*/