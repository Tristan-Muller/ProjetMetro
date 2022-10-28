typedef struct _un_nabr {
	Un_truc *truc; 		//La station
	struct _un_nabr *g; //Fils gauche strictement inferieur
	struct _un_nabr *d; //Fils droit
} Un_nabr;