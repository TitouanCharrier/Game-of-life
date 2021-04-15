#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "lib/chained.h"
#include "src/mainfunc.h"
#include "src/struct.h"

int main(int argc, char **argv) {
	
	
	//Starting SL2
	SDL_Init(SDL_INIT_VIDEO);

	//set antialiasing
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	//starting TTF (to display text))
    //TTF_Init();
	
	//init random
	time_t t;
	srand((unsigned) time(&t));
	
	//main tools of SDL
	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	
	//auto resolution
	SDL_DisplayMode Screen;
	SDL_GetCurrentDisplayMode(0, &Screen);
	int WIDTH = Screen.w;
	int HEIGHT = Screen.h;
	
	//set window and renderer
	window = SDL_CreateWindow("name",0,0,WIDTH,HEIGHT,0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//set event var to store events
	SDL_Event event;

	Case **ListCase = NULL;
	ListCase = LoadCase(100,100);

	PrintScene(renderer, ListCase);
	
	SDL_Delay(5000);
	
	/*Don't work for now
	element *element_1 = ch_insert(NULL,1,NULL);
	//element *element_2 = ch_insert(NULL,2,NULL);
	//element *element_3 = ch_insert(element_2,3,NULL);
	//element *element_4 = ch_insert(NULL,4,NULL);
	
	printf("%d\n",element_1->content );
	ch_print(element_1);
	*/


	



	printf("End reached\n");
	return 0;
}