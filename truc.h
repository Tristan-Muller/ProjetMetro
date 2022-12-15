#ifndef TRUC_H
#define TRUC_H

#include "station.h"
#include "connexion.h"  
#include "coord.h"


// Ce module contient les définitions des structures Tdata et Un_truc, utilisées tout au long du programme


typedef enum _ttype {STA, CON} Ttype;



typedef union _data {
	Une_station sta;
	Une_connexion con;
} Tdata;



typedef struct _un_truc {
	Une_coord coord;
	Ttype type;
	Tdata data;
	float user_val; 		//Distance pour plus court chemin
} Un_truc;

#endif