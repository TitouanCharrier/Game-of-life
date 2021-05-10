#include "test2.h"



int main(int arg, char **argv) {
	
	int coucou = 0;
	int *Coucou = &coucou;
	myfunc(Coucou);
	//SDL_CreateThread(NULL,NULL,NULL);
}