#include <stdio.h>
#include <stdlib.h>


// Module main, permettant l'appel ordonné des fonctions.



// Fonctions définies dans le module : 

void intro(); 
int main(); 



// Définitions des fonctions

void intro(){
    // Affiche le message de bienvenue 

    system("clear");
    
    printf("Bienvenue dans le Projet Metro !\n");
}



int main() {
    // Main, organise et execute le programme

    intro();

    return 0;
}