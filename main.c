#include <stdio.h>
#include <stdlib.h>


// Ce module permet l'appel ordonné des fonctions, et fait ainsi fonctionner le programme


// Fonctions définies dans le module : 

void intro(); 
int main(); 



// Définitions des fonctions

void intro(){
    // Affiche le message de bienvenue 

    // system("clear");
    
    printf("\n____________________________________\n");

    printf("\nBienvenue dans le Projet Metro !\n");
}



int main() {
    // Main, organise et execute le programme

    intro();

    return 0;
}