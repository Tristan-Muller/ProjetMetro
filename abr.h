#ifndef ABR_H
#define ABR_H

#include "abr_type.h"
#include "truc.h"
#include "liste.h"

Un_nabr *creer_nabr(Un_truc *truc);
Un_nabr *inserer_abr(Un_nabr *abr, Un_nabr *n);
Un_nabr *construire_abr(Un_elem *liste_sta);
void detruire_abr(Un_nabr *abr);
Un_truc *chercher_station(Un_nabr *abr, char *nom);
void afficher_abr(Un_nabr *abr);

#endif