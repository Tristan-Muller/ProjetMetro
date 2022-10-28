#include <coord.h>
#include <station.h>
#include <truc.h>

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv){
	Un_truc new=(Un_truc*)malloc(sizeof(Un_truc));
	new->coord = coord;
	new->data = data;
	new->user_val = uv;
	return new;
}


void detruire_truc(Une_truc *truc){
	
}