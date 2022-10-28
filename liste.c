#include <stdlib.h>
#include <stdio.h>
#include "coord.h"
#include "station.h"
#include "truc.h"
#include "liste.h"

Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc);
void ecrire_liste(FILE *flux, Un_elem *liste);
void detruire_liste(Un_elem *liste);
void detruire_liste_et_truc(Un_elem *liste);

Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc){
	Un_elem *tmp = (Un_elem*)malloc(sizeof(Un_elem));
	tmp->truc=truc;
	tmp->suivant=NULL;

	//Si problème d'allocation 
	if(temp==NULL){
		printf("erreur d'allocation de tmp");
	}

	//Cas si la liste est NULL
	if(liste==NULL){
		return tmp;
	}

	Un_elem *precedent = liste;
	Un_elem *element = liste->suivant;

	//Cas où user_val du truc à ajouter est inférieur à la 1ère valeur user_val de la liste
	if((liste->truc->user_val)>(tmp->truc->user_val)){
		tmp->suivant = liste;
		return tmp;
	}

	//Cas général
	while(((element->truc->user_val)<(tmp->truc->user_val))&&(element!=NULL)){
		precedent->suivant;
		element->suivant;
	}

	//Cas où la liste ne contient qu'un seul terme
	if(element==NULL){
		precedent->suivant = tmp;
		return precedent; 
	}

	precedent->suivant = tmp
	tmp->suivant = element;
	return liste;
}


void ecrire_liste(FILE *flux, Un_elem *liste){
	Un_elem* tete = liste;
	while(liste!=NULL){
	}
}



