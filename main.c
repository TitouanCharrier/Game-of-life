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
	
	//main var
	int run = 1;
	int timer = 0;
	int MaxTime = 2;
	int Numberline = 100;
	int space = 0;
	int click = 0;

	//init displacement
	location loc;
	loc.scale = 30;
	loc.locx = 0;
	loc.locy = 0;
	
	//init Cases
	Case **ListCase = NULL;
	ListCase = LoadCase(Numberline);

	//displacement var
	float Hzt = 0;
	float Vtc = 0;
	float Zm = 0;
	
	while (run) {
		
		//load events
		SDL_PollEvent(&event);
		
		//place new cells
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT && click == 0) {
				for (int i=0; i<Numberline; i++) {
					for (int j=0; j<Numberline; j++) {
						if ((ListCase[i][j].posx+loc.locx)*(loc.scale+1) <= event.button.x
						&& (ListCase[i][j].posx+loc.locx)*(loc.scale+1)+loc.scale >= event.button.x
						&& (ListCase[i][j].posy+loc.locy)*(loc.scale+1) <= event.button.y
						&& (ListCase[i][j].posy+loc.locy)*(loc.scale+1)+loc.scale >= event.button.y) {
							if (ListCase[i][j].state == 0) ListCase[i][j].nextstate = 1;
							else ListCase[i][j].nextstate = 0;
							click = 1;
						}
					}
				}
			}
		}

		if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_LEFT) click = 0;
		}
		//detect keys pressed
		if (event.type == SDL_KEYDOWN) {
			
			// quit
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				run = 0;
			}
			
			//start / Stop
			if (event.key.keysym.sym == SDLK_SPACE && space == 0) {
				if (timer == 0) timer = 1 ;
				else timer = 0;
				space = 1;
			} 

			//reload
			if (event.key.keysym.sym == SDLK_r) {
				ListCase = LoadCase(Numberline);
			}

			// timer
			if (event.key.keysym.sym == SDLK_RSHIFT) {
				MaxTime ++;
			}

			if (event.key.keysym.sym == SDLK_RCTRL && MaxTime > 2) {
				MaxTime --;
			}
			
			//arrows	
			if (event.key.keysym.sym == SDLK_LEFT) {
				Hzt = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				Hzt = -1;
			}
			if (event.key.keysym.sym == SDLK_UP) {
				Vtc = 1;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				Vtc = -1;
			}
			//zoom
			if (event.key.keysym.sym == SDLK_LSHIFT) {
				Zm = 0.5;
				Hzt = -1/(loc.scale)/100;
				Vtc = -1/(loc.scale)/100;
			}
			else if (event.key.keysym.sym == SDLK_LCTRL) {
				Zm = -0.5;
				Hzt = loc.scale/100;
				Vtc = loc.scale/100;
			}
		}

		//detect keys released
		if (event.type == SDL_KEYUP) {
			
			//start stop
			if (event.key.keysym.sym == SDLK_SPACE) space = 0;
			
			//arrows
			if (event.key.keysym.sym == SDLK_LEFT) {
				Hzt = 0;
			}
			if (event.key.keysym.sym == SDLK_RIGHT) {
				Hzt = 0;
			}
			if (event.key.keysym.sym == SDLK_UP) {
				Vtc = 0;
			}
			if (event.key.keysym.sym == SDLK_DOWN) {
				Vtc = 0;	
			}

			//zoom
			if (event.key.keysym.sym == SDLK_LSHIFT) {
				Zm = 0;
				Hzt = 0;
				Vtc = 0;
				
			}
			if (event.key.keysym.sym == SDLK_LCTRL) {
				Zm = 0;
				Hzt = 0;
				Vtc = 0;
				
			}
		}			
		
		//displacement
		loc.locx += Hzt;
		loc.locy += Vtc;
		loc.scale += Zm;

		
		if (timer >= MaxTime) {
			Life(ListCase, Numberline);
			timer = 1;
		}

		if (timer != 0) timer ++;
		
		PrintScene(renderer, ListCase, loc, Numberline, timer);
		SDL_Delay(16);

		

		
	}
	
	/*Don't work for now
	element *element_1 = ch_insert(NULL,1,NULL);
	//element *element_2 = ch_insert(NULL,2,NULL);
	//element *element_3 = ch_insert(element_2,3,NULL);
	//element *element_4 = ch_insert(NULL,4,NULL);
	
	printf("%d\n",element_1->content );
	ch_print(element_1);
	*/


	



	return 0;
}