<<<<<<< HEAD
#include "station.h"
#include "connexion.h"
#include "coord.h"

=======
#include <station.h>
#include <connexion.h>  
#include <coord.h>
>>>>>>> f5643d8b0aef09181db17b1feded2d5d22872d08

typedef enum _ttype {STA, CON} Ttype;



typedef union _data {
	Une_station sta;
	Une_connexion con;
} Tdata;



typedef struct _un_truc {
	Une_coord coord;
	Ttype type;
	Tdata data;
	float user_val; //Distance pour plus court chemin
} Un_truc;