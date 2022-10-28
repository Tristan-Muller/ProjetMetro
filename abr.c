#include <stdlib>

#include <truc.h>
#include <abr_type.h>

Un_nabr *creer_nabr(Un_truc *truc) {
    Un_nabr * nabr = (Un_nabr * ) malloc(sizeof(Un_nabr));
    nabr->g = NULL;
    nabr->d = NULL;
    nabr-> truc = truc; 

    return nabr;
}



Un_nabr *inserer_abr(Un_nabr *abr, Un_nabr *n) {}



Un_nabr *construire_abr(Un_elem *liste_sta);{}



void detruire_abr(Un_nabr *abr);{
    if (! abr) retrun; 
    
    if (!abr->d && !abr->g) 
        free(abr); 
    
    else {
        if (abr->d) detruire_abr(abr->d);
        if (abr->g) detruire_abr(abr->g);
    }
    
}



Un_truc *chercher_station(Un_nabr *abr, char *nom); {}