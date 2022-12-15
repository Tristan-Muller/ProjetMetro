#ifndef LISTE_H
#define LISTE_H

#include "truc.h"


// Ce module contient la définition de la structure Un_elem, utilisée dans les listes de truc


typedef struct _un_elem {
	Un_truc *truc; //Une station ou une connexion
	struct _un_elem *suiv;
} Un_elem;

#endif
