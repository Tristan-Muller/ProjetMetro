#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "liste.h"
 #include "abr.h"
// #include "truc.c"



/*Exercice 4*/
Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc);


Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc){

    if(truc->type != 0){
        printf("Le truc n'est pas une station");
        return NULL;
    }

    if(truc==NULL){
        printf("Le truc à inserer n'existe pas");
        return NULL;
    }

    Un_elem *tmp = (Un_elem*)malloc(sizeof(Un_elem));

    tmp->truc=truc;
    tmp->suiv=NULL;

    //printf("%f", tmp->truc->user_val);

    //Si problème d'allocation
    if(tmp==NULL){
        printf("Erreur d'allocation de l'element\n");
        return NULL;
    }

    //Cas si la liste est NULL
    if(liste==NULL){
        return tmp;
    }

    Un_elem *maillon = liste;

    
    //Cas où la liste ne contient qu'un seul terme
    if((maillon->truc->user_val)>(tmp->truc->user_val)){
        tmp->suiv = maillon;
        return tmp;
    }


    //Cas général
    while((maillon->suiv!=NULL) && ((maillon->suiv)->truc->user_val)<(tmp->truc->user_val)){

        maillon = maillon->suiv;
    }

    if(maillon->suiv == NULL){
        maillon->suiv = tmp;
        return liste;
    }

    tmp->suiv = maillon->suiv;
    maillon->suiv = tmp;
    return liste;
}



void ecrire_liste(FILE *liste_station, Un_elem *liste){
    Un_elem* tete = liste;
    if(liste==NULL){
        printf("Aucune liste à déchiffrer");
        return;
    }

    while(tete!=NULL){
        fprintf(liste_station,"%f;%f;%s\n", tete->truc->coord.lon, tete->truc->coord.lat, tete->truc->data.sta.nom);
        tete = tete->suiv;
    }
}



void detruire_liste(Un_elem* liste){
    free(liste);
    return;
}



void detruire_liste_et_truc(Un_elem* liste){
    Un_elem* tete = liste;
    while(liste!=NULL){
        liste = liste->suiv;
        detruire_truc(tete->truc);
        detruire_liste(tete);
        tete = liste;
    }
}



Un_elem *lire_stations(char *nom_du_fichier){

    FILE *flux = fopen(nom_du_fichier, "r");
    if (flux == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }else{
        Un_elem *liste = NULL;
        char ligne[100];
        int i = 0;
        int compt = 0;
        
        while (fgets(ligne, 100, flux) != NULL){
            float lon, lat;
            char *nom = (char *)malloc(100 * sizeof(char));
            sscanf(ligne, "%f ; %f ; ", &lon, &lat);

            for (i = 0; i < strlen(ligne); i++){
                if (ligne[i] == ';'){
                    compt++;
                }if (compt == 2){
                    strcpy(nom, ligne + i + 1);
                    nom[strlen(nom)-1] = '\0';
                    break;
                }
            }

            Un_truc *truc = (Un_truc*)malloc(sizeof(Un_truc));
            truc->type = STA;
            truc->data.sta.nom = (char*)malloc(100*sizeof(char));
            truc->coord.lon = lon;
            truc->coord.lat = lat;
            strcpy(truc->data.sta.nom, nom);
            truc->user_val = INFINITY;
            truc->data.sta.tab_con = (Un_truc**)malloc(10*sizeof(Un_truc*));
            truc->data.sta.nb_con = 0;
            truc->data.sta.con_pcc = (Un_truc*)malloc(10*sizeof(Un_truc));

            liste = inserer_liste_trie(liste, truc);
            //printf("Longitude = %f ; Latitude = %f ; Nom = %s\n", liste->truc->coord.lon,liste->truc->coord.lat, liste->truc->data.sta.nom);

            compt = 0;
        }
        fclose(flux);

        return liste;
    }
}



void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se){
    Un_elem* tete = liste;
    limite_no->lon = liste->truc->coord.lon;
    limite_no->lat = liste->truc->coord.lat;
    limite_se->lon = liste->truc->coord.lon;
    limite_se->lat = liste->truc->coord.lat;
    tete = tete->suiv;

    while(tete!=NULL){

        if((tete->truc->coord.lon)>(limite_se->lon)){
            limite_se->lon = tete->truc->coord.lon;
        }

        if((tete->truc->coord.lat)<(limite_se->lat)){
            limite_se->lat = tete->truc->coord.lat;
        }

        if((tete->truc->coord.lon)<(limite_no->lon)){
            limite_no->lon = tete->truc->coord.lon;
        }

        if((tete->truc->coord.lat)>(limite_no->lat)){
            limite_no->lat = tete->truc->coord.lat;
        }

        tete = tete->suiv;
    }
}


/* Exercice 4 : CONNEXION */

Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc){
    Un_elem* deb = (Un_elem*)malloc(sizeof(Un_elem));
    deb->truc = truc;
    deb->suiv = liste;
    return deb;
}


Un_elem* inserer_fin_liste(Un_elem* liste, Un_truc* truc){

    Un_elem* fin = (Un_elem*)malloc(sizeof(Un_elem));
    if (!fin){
        printf("Erreur d'allocation mémoire\n");
        return liste;
    }
    fin->truc = truc;
    if(liste==NULL){
        return fin;
    }

    Un_elem *tmp = liste;
    while(tmp->suiv){
        tmp = tmp->suiv;
    } 

    tmp->suiv = fin;
    return liste;
}



Un_elem *lire_connexions(char* nom_fichier, Un_nabr* abr){
    
    FILE* flux = NULL;
    flux = fopen(nom_fichier,"r");
    if(flux==NULL){
        printf("Erreur\n");
    }
    Un_elem *liste = NULL;
    char new[100];

    while(fgets(new,100,flux)!=NULL){

        char* stat_dep = (char*)malloc(100*sizeof(char));
        char* stat_arr = (char*)malloc(100*sizeof(char));
        char* code = (char*)malloc(1*sizeof(char));
        char* temp = (char*)malloc(100*sizeof(char));
        char* endPtr;
        int i=0;
        int compt=0;
        int x=0;
        int y=0;
        int z=0;
        int w=0;

        while(new[i]!='\n'){

            if(new[i]==';'){
                compt++;
                i++;
            }

            if(compt==0){
                code[i]=new[i];
                x++;
            }

            if(compt==1){
                stat_dep[y]=new[i];
                y++;
            }

            if(compt==2){
                stat_arr[z]=new[i];
                z++;

            }

            if(compt==3){
                temp[w]=new[i];
                w++;
            }

            i++;
        }

        stat_dep[y]='\0';
        stat_arr[z]='\0';
        temp[w]='\0';

        Un_truc* truc1 = chercher_station(abr, stat_dep);
        Un_truc* truc2 = chercher_station(abr, stat_arr);
        Un_truc* truc = (Un_truc*)malloc(sizeof(Un_truc));
        //printf("%s\n", truc1->data.sta.nom);
        //printf("%s\n", truc2->data.sta.nom);
        truc->type = CON;
        truc->user_val = strtof(temp, &endPtr);
        //printf("%f\n", truc->user_val);
        truc->data.con.sta_dep = truc1;
        truc->data.con.sta_arr = truc2;
        truc->data.con.ligne = (Une_ligne*)malloc(sizeof(Une_ligne));
        truc->data.con.ligne->code = (char*)malloc(1*sizeof(char));
        strcpy(truc->data.con.ligne->code, code);
        //printf("%s\n", truc->data.con.ligne->code);
        //printf("%d\n", truc2->data.sta.nb_con);
        truc1->data.sta.tab_con[truc1->data.sta.nb_con]=truc;
        truc2->data.sta.tab_con[truc2->data.sta.nb_con]=truc;
        truc1->data.sta.nb_con ++;
        truc2->data.sta.nb_con ++;

        printf("Ligne=%s : Station de depart = %s \n          Station d'arrivée = %s \n          Durée=%f\n\n", code, stat_dep, stat_arr, strtof(temp, &endPtr));
        
        liste = inserer_deb_liste(liste, truc);
        free(stat_dep);
        free(stat_arr);
        free(temp);
    }

    fclose(flux);
    return liste; //A voir si c'est bien liste qu'il faut retourner
}


//Fonction supplementaire pour vérification pour verifier l'ordre dans la liste
void affiche_station(Un_elem* liste){
    Un_elem* tmp = NULL;
    if(liste==NULL || liste->truc==NULL){
        printf("Liste vide");
    }else{
        tmp = liste;
        while(tmp != NULL){
            //printf("%f\n", tmp->truc->coord.lat);
            //printf("%f\n", tmp->truc->coord.lon);
            printf("%s\n", tmp->truc->data.sta.nom);
            tmp = tmp->suiv;
        }
    }
}

//Fonction supplementaire pour verification que l'arbre existe bien et que tout est bien rangé
void affiche_prefixe(Un_nabr* abr){
    if(abr==NULL){
        return;
    }
    printf("%s\n", abr->truc->data.sta.nom);
    affiche_prefixe(abr->g);
    affiche_prefixe(abr->d);
}


/*Exercice 6 : Exercice Plus Court Chemin*/


Un_truc* extraire_deb_liste(Un_elem* liste){

    if (liste == NULL){
        printf("La liste n'existe pas");
        return NULL;
    }

    return liste->truc;
}


Un_truc* extraire_liste(Un_elem* liste, Un_truc* truc){
    
    while((liste->truc->data.sta.nom != truc->data.sta.nom) && liste!=NULL){
        liste = liste->suiv;
    }

    if (liste==NULL){
        printf("Nous ne pouvons pas extraire d'une liste un truc qui n'existe pas\n");
        return NULL;
    } 

    return liste->truc;
}


void dijkstra(Un_elem* liste_sta, Un_truc* sta_dep){

    Un_elem* tete = liste_sta;
    //Un_elem* liste_co = (Un_elem*)malloc(sizeof(Un_elem));
    //printf("%s \t %s\n", liste_sta->truc->data.sta.nom, sta_dep->data.sta.nom);
    
    while(strcmp((tete->truc->data.sta.nom),(sta_dep->data.sta.nom))!=0 && (tete!=NULL)){
        tete = tete->suiv;
    }

    if(tete==NULL){
        printf("La station de départ n'a pas été trouvé dans la liste de station\n");
        return;
    }

    //printf("%s", tete->truc->data.sta.nom);
    tete->truc->user_val = 0.0;

    Un_elem* Q = NULL;
    Un_elem* Q2 = liste_sta;


    while(Q2!=NULL){

        //On créé la liste Q triée avec les user_val
        while(Q2!=NULL){
            Q = inserer_liste_trie(Q, Q2->truc);
            Q2 = Q2->suiv;
        }

        //Affichage de la liste pour vérifier si c'est bien trié
        Un_elem* tmp = Q;
        while(tmp!=NULL){
            //printf("%s\t", tmp->truc->data.sta.nom);
            //printf("%f\n", tmp->truc->user_val);
            tmp = tmp->suiv;
        }
        tmp=Q;
        
        //printf("\n");
        
        for(int i=0; i<(Q->truc->data.sta.nb_con); i++){

            Un_truc* connect = Q->truc->data.sta.tab_con[i];

            //printf("%s - %s\n\n", connect->data.con.sta_dep->data.sta.nom, connect->data.con.sta_arr->data.sta.nom);

            if(strcmp(connect->data.con.sta_dep->data.sta.nom, Q->truc->data.sta.nom)!=0){
                if(sta_dans_liste(Q, connect->data.con.sta_dep->data.sta.nom)==1){
                    while((strcmp(tmp->truc->data.sta.nom, connect->data.con.sta_dep->data.sta.nom)!=0) && tmp!=NULL){
                        tmp = tmp->suiv;
                    }
                    if(tmp->truc->user_val==INFINITY){
                        tmp->truc->user_val = connect->data.con.sta_arr->user_val + connect->user_val;
                    }
                    else{
                        if(tmp->truc->user_val > connect->data.con.sta_arr->user_val + connect->user_val){
                            tmp->truc->user_val = connect->data.con.sta_arr->user_val + connect->user_val;
                        }
                    }
                }
            }

            if(strcmp(connect->data.con.sta_arr->data.sta.nom, Q->truc->data.sta.nom)!=0){
                if(sta_dans_liste(Q, connect->data.con.sta_arr->data.sta.nom)==1){
                    while(strcmp(tmp->truc->data.sta.nom, connect->data.con.sta_arr->data.sta.nom)!=0){
                        tmp = tmp->suiv;
                    }
                    if(tmp->truc->user_val==INFINITY){
                        tmp->truc->user_val = connect->data.con.sta_dep->user_val + connect->user_val;
                    }
                    else{
                        if(tmp->truc->user_val > (connect->data.con.sta_dep->user_val + connect->user_val)){
                            tmp->truc->user_val = connect->data.con.sta_dep->user_val + connect->user_val;
                        }
                    }
                }
            }
            tmp = Q;
        }
        tmp = Q;
        
        while(tmp!=NULL){
            //printf("%s\t", tmp->truc->data.sta.nom);
            //printf("%f\n", tmp->truc->user_val);
            tmp = tmp->suiv;
        }
        //printf("\n");
        
        //On met Q2 à Q->suiv pour avancer la liste
        Q2 = Q->suiv;
        //On met Q à NULL pour pouvoir recreer une liste 
        Q = NULL;
    }

    tete = liste_sta;
    while(tete!=NULL){
        printf("Il faut  %f  min\t", tete->truc->user_val);
        printf("pour aller à %s\n", tete->truc->data.sta.nom);
        tete = tete->suiv;
    }
}


Un_elem* cherche_chemin(Un_elem* liste_sta, Un_truc* sta_dep, Un_truc* sta_arr){

    Un_truc* dep = sta_dep;
    Un_elem* tete = liste_sta;
    int nb_station = 0;
    Un_elem* liste_co = (Un_elem*)malloc(sizeof(Un_elem));

    if(liste_co == NULL){
        printf("Erreur lors de l'allocation de la liste de connexions pour le plus court chemin");
        return NULL;
    }

    liste_co->truc = dep;

    //Cas général
    printf("Pour aller jusqu'à %s le plus rapidement possible, il faut passer par: ", sta_arr->data.sta.nom);
    while((strcmp(dep->data.sta.nom, sta_arr->data.sta.nom)!=0) && tete!=NULL){


        tete = tete->suiv;
    }

    if(nb_station == 0){
        printf("Votre station de départ est votre station d'arrivée, vous êtes donc déjà arrivé à destination !");
        liste_co->truc = dep;
        return liste_co;
    }

}



int sta_dans_liste (Un_elem *liste, char *sta){
    // Renvoie 0 si la station de nom sta n'est pas dans la liste de trucs
    // Renvoie 1 si elle l'est

    if (!liste || !liste->truc) return 0;               // Si la liste est vide, on renvoie 0 

    if(!strcmp(liste->truc->data.sta.nom, sta))        // strcomp vaut 0 si les char* sont égaux
        return 1;

    if(liste->suiv)                                     // Si la liste possède un élément suivant 
        return sta_dans_liste(liste->suiv, sta);        // On cherche sur cet élément suivant 

    return 0;                                           // Cas où la liste n'est composée de qu'un seul élément différent de sta
}


// int main(){

//     printf("\n---DEBUT STATION---\n\n");

//     Un_elem* new = lire_stations("flux.csv");

//     //Regarde si la liste est bien triée selon user val et s'il n'y a pas de problème au niveau des stations
//     affiche_station(new);

//     FILE* fic = fopen("liste_station.csv","w");
//     ecrire_liste(fic,new);
//     fclose(fic);

//     Une_coord limite_no;
//     Une_coord limite_se;

//     limites_zone(new, &limite_no, &limite_se);

//     printf("\n---LIMITES ZONES---\n\n");

//     printf("Longitude min : %f\n", limite_no.lon);
//     printf("Latitude max : %f\n", limite_no.lat);
//     printf("Longitude max : %f\n", limite_se.lon);
//     printf("Latitude min : %f\n", limite_se.lat);

    //Revoir detruire ! (Je comprend pas pk ça marche pas)
    /*detruire_liste_et_truc(new);

    affiche_station(new); //Normallement affiche ("Liste vide")


    //N'affiche pas, donc tout n'a pas bien été desalloué
    if(new==NULL){
    printf("Tout a bien été désalloué !");
    }*/

    //printf("\n---FIN STATION---\n");

//     //Revoir detruire ! (Je comprend pas pk ça marche pas)
//     //detruire_liste_et_truc(new);

//     //affiche_station(new); //Normallement affiche ("Liste vide")


//     //N'affiche pas, donc tout n'a pas bien été desalloué
//     /*if(new==NULL){
//     printf("Tout a bien été désalloué !");
//     }*/


//     printf("\n---FIN STATION---\n");

//     printf("\n---DEBUT ARBRE---\n\n");

//     Un_nabr* abr = (Un_nabr*)malloc(sizeof(Un_nabr));
//     abr = construire_abr(new);
//     affiche_prefixe(abr);


//     printf("\n---DEBUT CONNEXION---\n\n");

    /*lire_connexions("connexion.csv", abr); //Je me permet de mettre l'arbre en + (à voir pour la suite)
    
    printf("Verification tableau de connexion des stations:\n");
    
    //Vérification Tableau de Connexion pour Gares
    Un_truc* g = chercher_station(abr, "Gares");
    
    for(int i=0; i<(g->data.sta.nb_con); i++){
        Un_truc* p = g->data.sta.tab_con[i];
        printf("%s - %s\n", p->data.con.sta_dep->data.sta.nom, p->data.con.sta_arr->data.sta.nom);
    }
    //A voir après vu que c'est un tableau de connexion on peut pas print les connexions
=======
//     lire_connexions("connexion.csv", abr); //Je me permet de mettre l'arbre en + (à voir pour la suite)
//     
//     printf("Verification tableau de connexion des stations:\n");
    
//     for(int i=0; i<(0,new->truc->data.sta.nb_con); i++){
//         Un_truc* p = new->truc->data.sta.tab_con[i];
//         printf("%s - %s", p->data.con.sta_dep, p->data.con.sta_arr);
//     }
//     */
//     //A voir après vu que c'est un tableau de connexion on peut pas print les connexions

//     printf("\n---FIN CONNEXION---\n\n");

//     printf("\n---DEBUT PCC---\n\n");

//     dijkstra(new, new->truc);

//     return 0;
// }

// /* Exercice 1 à terminer, qq fonction à verif et à mettre dans le main */
