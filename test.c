#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

void myfunc(int* Coucou) {
	printf("Salut je suis la %d\n",*Coucou);
	*Coucou += 1;
}

int main(int arg, char **argv) {
	
	int coucou = 0;
	int *Coucou = &coucou;

	SDL_CreateThread(NULL,NULL,NULL);
}