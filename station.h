#ifndef STATION_H
#define STATION_H


// Ce module contient la définition de la structure Une_station, utilisée tout au long du programme


typedef struct _une_station{
	char* nom; 					//Le nom
	struct _un_truc **tab_con; 	//Tableau des connexions
	unsigned int nb_con; 		//Nombre de connexions
	struct _un_truc *con_pcc; 	//Connexion du plus court chemin
} Une_station;

#endif