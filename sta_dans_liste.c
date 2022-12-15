

int sta_dans_liste (Un_elem *liste, char *sta){
    // Renvoie 0 si la station de nom sta n'est pas dans la liste de trucs
    // Renvoie 1 si elle l'est

    if (!liste || !liste->truc) return 0;               // Si la liste est vide, on renvoie 0 

    if(!strcomp(liste->truc->data.sta.nom, sta))        // strcomp vaut 0 si les char* sont égaux
        return 1;

    if(liste->suiv)                                     // Si la liste possède un élément suivant 
        return sta_dans_liste(liste->suiv, sta);        // On cherche sur cet élément suivant 

    return 0;                                           // Cas où la liste n'est composée de qu'un seul élément différent de sta
}