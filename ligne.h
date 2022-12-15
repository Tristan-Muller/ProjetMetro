#ifndef LIGNE_H
#define LIGNE_H


// Ce module contient la définition de la structure Une_ligne, utilisée dans le module ligne.c


typedef struct _une_ligne {
	char *code; 		//Le nom de la ligne A, B .., M1, M2, T1...
	char *color;		//La couleur de la ligne #RRGGBB
	float vitesse; 		//Vitesse moyenne des rames en km/h
	float intervalle; 	//Intervalle moyen entre 2 rames
	struct _une_ligne *suiv;
} Une_ligne;

#endif