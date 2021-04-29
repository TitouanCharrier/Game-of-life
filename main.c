#include "lib/chained.h"
#include "src/mainfunc.h"
#include <unistd.h>

int main(int argc, char **argv) {

	//Starting SL2
	SDL_Init(SDL_INIT_VIDEO);

	//set antialiasing
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	//starting TTF (to display text))
    TTF_Init();

	//main tools of SDL
	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;

	//auto resolution
	SDL_DisplayMode Screen;
	SDL_GetCurrentDisplayMode(1, &Screen);
	int WIDTH = Screen.w;
	int HEIGHT = Screen.h;

	//set window and renderer
	window = SDL_CreateWindow("name",0,0,WIDTH,HEIGHT,0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//set event var to store events
	SDL_Event event;
	SDL_Event *Event = &event;

	//Main settings
	Grid numberOf;
	Grid *NumberOf = &numberOf;

	NumberOf->Lines = 60;
	NumberOf->Cols = 60;
	NumberOf->Buttons = 9;
	NumberOf->Direction = 6;
	NumberOf->ButtonLeft = 9;
	NumberOf->Time = 10;
	NumberOf->Gen = 0;

    //List init
    St_List List_v;
    St_List *List = &List_v;

    List->Cases = NULL;
    List->Buttons = NULL;
    List->Direction = NULL;

	//Main variables 
	St_Var mainVar;
	St_Var *MainVar = &mainVar;

	MainVar->run = 1;
	MainVar->timer = 0;
	MainVar->space = 0;
	MainVar->click = 0;
	MainVar->pressed = 0;
	MainVar->ctrl = 0;
	MainVar->shift = 0;
	MainVar->resx = WIDTH;
	MainVar->resy = HEIGHT;
	MainVar->loc.locy = 0;
	MainVar->loc.locx = 0;
	MainVar->police = TTF_OpenFont("fonts/arial.ttf", 65);

	//States
	St_State state;
	St_State *State = &state;

	State->Map = 0;
	State->Draw = 1;
	
	//WIP
	//Couple Compare;

	//displacement var
	Disp dispVar;
	Disp *DispVar = &dispVar;

	DispVar->Hzt = 0;
	DispVar->Vtc = 0;
	DispVar->Zm = 0;

	//init Buttons
	List->Buttons = malloc((NumberOf->Buttons+NumberOf->ButtonLeft)*sizeof(Button));
	assert(List->Buttons);
	LoadButton(List,MainVar,NumberOf);

	//Load directions
	List->Direction = malloc(NumberOf->Direction*sizeof(Button));
	assert(List->Direction);
	LoadDirection(List,MainVar,NumberOf);

	//detect txt file loaded in stdin
    if (isatty (STDIN_FILENO)) {
		//init Cases
		LoadCase(List,NumberOf);
        //load menu
        LoadMap(List,NumberOf,"map/Menu.ins");
    }
    else {
        LoadStdin(List,NumberOf);
    }

    //setup scale
    MainVar->loc.scale = HEIGHT/NumberOf->Lines;

	//main loop
	while (MainVar->run && List->Buttons[0].state == 0) {

		//load events
		SDL_PollEvent(&event);

		//Detect Mouse Click
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT && MainVar->click == 0) {
                
                FindCase(Event,List,NumberOf,MainVar);
				
				FinDirection(Event,List,NumberOf,MainVar);

                PlaceCell(renderer,Event,List,NumberOf,MainVar);
			}
			
			// for deleting cells
			else if (event.button.button == SDL_BUTTON_RIGHT && MainVar->click == 0) {
                RemoveCell(renderer,Event,List,NumberOf,MainVar);
			}
		}

		// Detect Mouse released
		if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_LEFT) MainVar->click = 0;
			for (int k=0; k<NumberOf->Direction-2; k++) {
				List->Direction[k].state = 0;
				DispVar->Hzt = 0;
				DispVar->Vtc = 0;
				DispVar->Zm = 0;
			}
		}

		//detect keys pressed
		if (event.type == SDL_KEYDOWN) {

			HandleKeyDown(renderer,List,MainVar,NumberOf,Event,DispVar);
		}

		//detect keys released
		if (event.type == SDL_KEYUP) {
			
			HandleKeyUp(renderer,List,MainVar,NumberOf,Event,DispVar);
		}

		//Functions to execute by buttons
		ButtonFunc(renderer, List, NumberOf, State, MainVar, DispVar);

		//displacement
		MainVar->loc.locx += DispVar->Hzt;
		MainVar->loc.locy += DispVar->Vtc;
		MainVar->loc.scale += DispVar->Zm;
		
		//update life position
		if (MainVar->timer >= NumberOf->Time) {
			if (State->Map == 0) LifeThor(List, NumberOf);
			else LifeClosed(List, NumberOf);
			NumberOf->Gen ++;
			MainVar->timer = 1;
		}
		//print the entire screen
		if (MainVar->timer != 0) MainVar->timer ++;
		PrintScene(renderer,List,MainVar,NumberOf);
	}

	return 0;
}
