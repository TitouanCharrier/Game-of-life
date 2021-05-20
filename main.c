#include "src/game_of_life_gui.h"
#include "src/game_of_life.h"
#include <unistd.h>

int main(int argc, char **argv) {

	/*
	Init SDL2 : ----------------------------------------------------------------
	*/

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
	SDL_GetCurrentDisplayMode(0, &Screen);
	int WIDTH = Screen.w;
	int HEIGHT = Screen.h;

	//set window and renderer
	window = SDL_CreateWindow("name",0,0,WIDTH,HEIGHT,0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	/*
	Define my variables : ------------------------------------------------------
	*/

	//set event var to store events
	SDL_Event event;
	SDL_Event *Event = &event;

	//Main settings
	Grid numberOf;
	Grid *NumberOf = &numberOf;

	NumberOf->Lines = 100;
	NumberOf->Cols = 100;
	NumberOf->Buttons = 9;
	NumberOf->ButtonLeft = 16;
	NumberOf->ButtonSize = 8;
	NumberOf->Time = 10;
	NumberOf->Error = 2;
	NumberOf->Gen = 0;

	//List init
	St_List List_v;
	St_List *List = &List_v;

	List->Cases = NULL;
	List->Buttons = NULL;
	List->ButtonSize = NULL;

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
	MainVar->police = TTF_OpenFont("fonts/HEMIHEAD.TTF", 18*HEIGHT/720);
	MainVar->police40 = TTF_OpenFont("fonts/HEMIHEAD.TTF", 30*HEIGHT/720);
	MainVar->limite = -1;
	MainVar->ButtonChanged = 1;
	MainVar->Ruled = 0;

	//States
	St_State state;
	St_State *State = &state;

	State->Map = 0;
	State->Draw = 1;

	//displacement var
	Disp dispVar;
	Disp *DispVar = &dispVar;

	DispVar->Hzt = 0;
	DispVar->Vtc = 0;
	DispVar->Zm = 0;

	/*
	Initial loading : ----------------------------------------------------------
	*/

	//load settings from file
	LoadSettings(NumberOf, MainVar);

	//init Buttons and error button
	List->Buttons = malloc(sizeof(*List->Buttons) * (NumberOf->Buttons+NumberOf->ButtonLeft));
	assert(List->Buttons);
	List->ButtonSize = malloc(sizeof(*List->ButtonSize) * NumberOf->ButtonSize);
	assert(List->ButtonSize);
	List->Error = malloc((NumberOf->Error)*sizeof(Button));
	assert(List->Error);
	LoadButton(List,MainVar,NumberOf);

	//detect txt file loaded in stdin
	if (isatty (STDIN_FILENO)) {
		//init Cases
		LoadCase(List,NumberOf);
		//load menu
		LoadMap(List,NumberOf,"map/AnimeHi.ins");
	}
	else {
		if (LoadStdin(List,NumberOf,MainVar)) {
			List->Buttons[4].state = 1;
			List->Buttons[5].state = 0;
			State->Map = 1;
		}
		else {
			List->Buttons[5].state = 1;
			List->Buttons[4].state = 0;
			State->Map = 0;
		}
	}

	//Load Background
	LoadBackground(renderer,MainVar);

	//setup scale
	MainVar->loc.scale = HEIGHT/NumberOf->Lines;

	/*
	Begining of the main loop : ------------------------------------------------
	*/

	//Main loop
	while (List->Buttons[0].state == 0 && MainVar->run == 1) {
		
		//Load events
		SDL_PollEvent(&event);


		///Handle events///
		switch(event.type) {

			case SDL_QUIT :
				MainVar->run = 0;
				break;

			//Detect Mouse Click
			case SDL_MOUSEBUTTONDOWN :
				if (event.button.button == SDL_BUTTON_LEFT && MainVar->click == 0) {

					//Delete error
					List->Error[0].state = 0;
	
					if (FindButton(Event,List,NumberOf,MainVar)) break;				
	
					PlaceCell(renderer,Event,List,NumberOf,MainVar);
				} break;

			//for deleting cells
			case SDL_BUTTON_RIGHT : 
				if (MainVar->click == 0) {
					RemoveCell(renderer,Event,List,NumberOf,MainVar);
				} break;

			//Detect Mouse released
			case SDL_MOUSEBUTTONUP :
				if (event.button.button == SDL_BUTTON_LEFT) MainVar->click = 0;
				break;
			
			//Detect keys pressed
			case SDL_KEYDOWN :
				if (HandleKeyDown(renderer,List,MainVar,NumberOf,Event,DispVar)) {
					MainVar->ButtonChanged = 1;
				} break;

			//Detect keys released
			case SDL_KEYUP :
				HandleKeyUp(List,MainVar,NumberOf,Event,DispVar);
				break;

			//Detect mouse scroll
			case SDL_MOUSEWHEEL :
			
				//Up
				if (event.wheel.y > 0) {
					DispVar->Zm = MainVar->loc.scale/5+1;
					event.wheel.y = 0;
					break;
				}

				//Down
				if (event.wheel.y < 0) {
					DispVar->Zm = -(MainVar->loc.scale/5+1);
					event.wheel.y = 0;
				} break;
		}
		
		///Main part///

		//Functions to execute by buttons
		ButtonFunc(renderer, List, NumberOf, State, MainVar);

		//Update displacement
		MainVar->loc.locx += DispVar->Hzt;
		MainVar->loc.locy += DispVar->Vtc;
		MainVar->loc.scale += DispVar->Zm;

		//Reset zoom to 0
		DispVar->Zm = 0;

		//Change speed button's state
		if (NumberOf->Time == 1) {
			strcpy(List->Buttons[6].text, "Vitesse Max");
			List->Buttons[6].state = 1;
		}
		else strcpy(List->Buttons[6].text, "Plus Vite (p)");

		//Stop when reach limite
		if (NumberOf->Gen == MainVar->limite) {
			MainVar->timer = 0;
			MainVar->limite = -1;
			strcpy(List->Buttons[8].text,"Lancer");
			List->Buttons[8].state = 0;
		}

		//Update life position
		if (MainVar->timer >= NumberOf->Time) {
			if (State->Map == 0) LifeThor(List, NumberOf);
			else LifeClosed(List, NumberOf);
			NumberOf->Gen ++;
			MainVar->timer = 1;
		}
		//Print the entire screen
		if (MainVar->timer != 0) MainVar->timer ++;
		PrintScene(renderer,List,MainVar,NumberOf);
	}
	return 0;
}
