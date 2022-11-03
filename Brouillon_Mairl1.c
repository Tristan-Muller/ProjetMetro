#include <stdio.h>
#include <string.h>

#include "ligne.c"



//Notes sur les docs : ////////////////////////////////////////////////////////////////////////////

    //lignes.csv : "Elle contient dans l’ordre le code de la ligne, 
    //              la vitesse moyenne (en km/h),l’intervalle moyen 
    //              entre rames(en minutes) et la couleur."


//Mertro : RENNES /////////////////////////////////////////////////////////////////////////////////


//Ligne A : 
//                                      lat        long
//J.F Kennedy                       48.121348;-1.711154
//Villejean Université              48.121256;-1.703934
//Pontchaillou-CHU                  48.121571;-1.693441
//Anatole France                    48.118230;-1.687475
//Sainte Anne                       48.114562;-1.680173
//République                        48.109670;-1.679215
//Charles de Gaulle                 48.105386;-1.676835
//Gares                             48.104181;-1.672193
//Jacques Cartier                   48.097541;-1.675264
//Clémenceau                        48.093493;-1.674424
//Henri Fréville                    48.087623;-1.674768
//Italie                            48.086526;-1.667849
//Triangle                          48.086486;-1.660429
//Le Blosne                         48.087743;-1.654303
//La Poterie                        48.087534;-1.644666


//Ligne B :

//                                      lat        long
//Saint-Jacques - Gaité  :          48.092053;-1.703633
//La Courrouze :                    48.096517;-1.698342
//Cleunay :                         48.100993;-1.706423
//Puits Voltaire :                  48.105081;-1.703334
//Mabilais :                        48.105032;-1.692710
//Colombiers :                      48.105768;-1.682879
//Gares :                           48.104181;-1.672193
//Puits Duhamel :                   48.106696;-1.669375
//Saint Germain :                   48.110661;-1.676419
//Saint Anne :                      48.114562;-1.680173
//Puis Vincennes :                  48.117302;-1.678802
//Jules Ferry :                     48.118699;-1.670777
//Puits Lafond :                    48.122109;-1.666518
//Gros-Chêne :                      48.125055;-1.664382
//Les Gayeulles :                   48.129446;-1.657385
//Joliot-Curie - Chateaubriand :    48.124114;-1.651436
//Beaulieu-Université :             48.122067;-1.639063
//Atalante :                        48.127127;-1.627985
//Cesson-Viasilva :                 48.131394;-1.620170



//GIT//////////////////////////////////////////////////////////////////////////////////////////////

//Command : 
//   git checkout master (ou main)


//Clé GIT : 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




//TYPEDEF : ///////////////////////////////////////////////////////////////////////////////////////

typedef struct _une_coord {
    float lon; //Longitude decimale
    float lat; //Latitude decimale
} Une_coord; 



typedef struct _une_station {
    char *nom; //Le nom
    struct _un_truc **tab_con; //Tableau des connexions
    unsigned int nb_con; //Nombre de connexions
    struct _un_truc *con_pcc; //Connexion du plus court chemin
} Une_station; 



typedef struct _une_connexion {
    struct _un_truc *sta_dep; //Station de depart
    struct _un_truc *sta_arr; //Station d arrivee
    struct _une_ligne *ligne; //Ligne
} Une_connexion; 



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



typedef struct _un_elem {
    Un_truc *truc; //Une station ou une connexion
    struct _un_elem *suiv;
} Un_elem; 



typedef struct _un_nabr {
    Un_truc *truc; //La station
    struct _un_nabr *g; //Fils gauche strictement inferieur
    struct _un_nabr *d; //Fils droit
} Un_nabr; 



typedef struct _une_ligne {
    char *code; //Le nom de la ligne A, B .., M1, M2, T1...
    char *color; //La couleur de la ligne #RRGGBB
    float vitesse; //Vitesse moyenne des rames en km/h
    float intervalle; //Intervalle moyen entre 2 rames
    struct _une_ligne *suiv; 
} Une_ligne; 



typedef struct _un_noeud {
    Un_truc *truc; //Une station ou une connexion
    Une_coord limite_no; //Limite zone
    Une_coord limite_se; //Limite zone
    struct _un_noeud *no; //Fils pour quart NO
    struct _un_noeud *so; //Fils pour quart SO
    struct _un_noeud *ne; //Fils pour quart NE
    struct _un_noeud *se; //Fils pour quart SE
} Un_noeud; 


///////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    lire_lignes("ligne.csv");
    return 0;
}