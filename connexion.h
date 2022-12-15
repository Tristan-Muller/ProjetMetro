#ifndef CONNEXION_H
#define CONNEXION_H


// Ce module contient la définition de la structure Une_connexion

typedef struct _une_connexion {
	struct _un_truc *sta_dep; //Station de depart
	struct _un_truc *sta_arr; //Station d arrivee
	struct _une_ligne *ligne; //Ligne
} Une_connexion;

#endif