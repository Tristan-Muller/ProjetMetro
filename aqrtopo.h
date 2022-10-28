#include <truc.h>
#include <coord.h> 

typedef struct _un_noeud {
	Un_truc *truc; 			//Une station ou une connexion
	Une_coord limite_no; 	//Limite zone
	Une_coord limite_se; 	//Limite zone
	struct _un_noeud *no; 	//Fils pour quart NO
	struct _un_noeud *so; 	//Fils pour quart SO
	struct _un_noeud *ne; 	//Fils pour quart NE
	struct _un_noeud *se; 	//Fils pour quart SE
} Un_noeud;



//Arbre Quaternaire de recherche 
