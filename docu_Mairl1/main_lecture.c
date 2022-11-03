#include <stdio.h>



int main (){

    FILE *fic = fopen("test.txt", "r");

    if(!fic) return 0;

    /*
    int lettre = 0;*
    while((lettre =  fgetc(fic) )!= EOF){ 

        printf("%c", lettre);
    }
    printf("\n");
    */


    /*
    char txt[200];
    while(fgets(txt, 199, fic) != NULL)
        printf("%s\n", txt); 
    */


   char txt[256]; 
   int age = 0; 
   int CP = 0;

   fscanf(fic, "%s %d %d", txt, &age, &CP);
   printf("Nom : %s \nCP : %d\n", txt, CP);



   
    fclose(fic); 

    return 0;
}