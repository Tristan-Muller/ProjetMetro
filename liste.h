#ifndef LISTE_H
#define LISTE_H
#include "truc.h"

typedef struct _un_elem {
	Un_truc *truc; //Une station ou une connexion
	struct _un_elem *suiv;
} Un_elem;

#endif