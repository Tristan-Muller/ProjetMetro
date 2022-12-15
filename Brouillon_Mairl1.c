#include <stdlib.h>
#include <stdio.h>

#include "truc.h"
#include "truc.c"
#include "liste.h"
#include "connexion.h"



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



///////////////////////////////////////////////////////////////////////////////////////////////////


int test(int a){
    if (a < 5) {
        printf("%d\n", a);
        return test(a+1);}
    return a;
}

int main(){

    int a=0; 
    a =test(a);
    printf("end :%d\n", a);

    return 0;
}