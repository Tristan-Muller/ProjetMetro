#include <stdlib.h>
#include "coord.h"
#include "station.h"
#include "truc.h"

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv);
void detruire_truc(Un_truc *truc);



Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv){
	Un_truc* new = (Un_truc*)malloc(sizeof(Un_truc));
	new->coord = coord;
	new->data = data;
	new->type = type;
	new->user_val = uv;
	return new;
}



void detruire_truc(Une_truc *truc){
	if(truc->type = STA){
		free(truc->data.sta.nom);
		free(truc->data.sta.tab_con);
	}
	free(truc);
}