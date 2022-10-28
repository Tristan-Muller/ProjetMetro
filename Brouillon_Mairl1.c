#include <stdio.h>
#include <string.h>



//Mertro : RENNES //////////////////////////////////////////////////////////////////////////

//Ligne B :

//                                      long        lat
//Le garage atelier :               48.11198    -1.67429
//Saint-Jacques - Gaité  :          *
//La Courrouze :                    *
//Cleunay :                         *
//Puits Voltaire :                  *
//Mabilais :                        *
//Colombiers :                      *
//Gares :                           *
//Puits Duhamel :                   *
//Saint Germain :                   *
//Saint Anne :                      *
//Puis Vincennes :                  *
//Jules Ferry :                     *
//Puits Lafond :                    *
//Gros-Chêne :                      *
//Les Gayeulles :                   *
//Joliot-Curie - Chateaubriand :    *
//Beaulieu-Université :             *
//Atalante :                        *
//Cesson-Viasilva :                 *
//Les parcs relais :                *



//GIT////////////////////////////////////////////////////////////////////////////////////////

//Command : 
//   git checkout master (ou main)


//Clé GIT : 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




//TYPEDEF : ////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    printf("%d\n", strcmp("a", "ba"));
    return 0;
}