#ifndef LIGNE_H
#define LIGNE_H

typedef struct _une_ligne {
	char* code; //Le nom de la ligne A, B .., M1, M2, T1...
	char color[8]; //La couleur de la ligne #RRGGBB
	float vitesse; //Vitesse moyenne des rames en km/h
	float intervalle; //Intervalle moyen entre 2 rames
	struct _une_ligne *suiv;
} Une_ligne;

#endif



/*Ici, suite à des soucis dans les fonctions de ligne.c, j'ai remplacé les char * par des tableaux de char 
Si possible, j'aimerais avoir le temps de revenir dessus et resoudre le problème en gardant la notion de pouinteurs 
D'ici la, je grade les tableaux qui permettent à la fonction de marcher 
(Merlin)*/