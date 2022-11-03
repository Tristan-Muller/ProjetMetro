#include <stdio.h>



int main (){
    FILE *fic =  fopen("test.txt", "w");

    if(!fic) return 0;

    /*
    fputc('M', fic);
    fputc('e', fic);
    fputc('r', fic);
    fputc('l', fic);
    fputc('i', fic);
    fputc('n', fic);
    */

   /*
   char word[] = "Hello World\ntest";
 
   fputs(word, fic);
   */

  /*
    char nom[] = "Merlin Fouché"; 
    int age = 19; 
    int CP = 92170; 

    fprintf(fic, "Nom :%s, %d ans, habite a Vanves %d", nom, age, CP);
    */





    fclose(fic);

    return 0;
}
