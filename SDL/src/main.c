#include <SDL.h>
#include <stdio.h>

int main(int argc, char **argv){

    SDL_version nb;
    SDL_VERSION(&nb);

    printf("Hello on the SDL %d %d %d ! \n", nb.major, nb.minor, nb.patch);

    return 0;
}


//Compilation : 
//  gcc src/main.c -o bin/prog -I include -L lib -lSDL2main -lSDL2