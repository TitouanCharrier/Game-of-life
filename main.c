#include "src/game_of_life_gui.h"
#include "src/game_of_life.h"
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
	SDL_GetCurrentDisplayMode(0, &Screen);
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

	NumberOf->Lines = 100;
	NumberOf->Cols = 100;
	NumberOf->Buttons = 9;
	NumberOf->ButtonLeft = 16;
	NumberOf->ButtonSize = 9;
	NumberOf->Time = 10;
	NumberOf->Error = 2;
	NumberOf->Gen = 0;

	//load settings from file
	//LoadSettings(NumberOf);

	//List init
	St_List List_v;
	St_List *List = &List_v;

	List->Cases = NULL;
	List->Buttons = NULL;

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
	MainVar->police = TTF_OpenFont("fonts/HEMIHEAD.TTF", 20*HEIGHT/720);
	MainVar->policeNbr = TTF_OpenFont("fonts/HEMIHEAD.TTF", 20*HEIGHT/720);
	MainVar->police40 = TTF_OpenFont("fonts/HEMIHEAD.TTF", 30*HEIGHT/720);
	MainVar->limite = -1;
	MainVar->ButtonChanged = 1;
	MainVar->Ruled = 0;

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

	printf("debug1\n");
	test();
	printf("test\n");
	//init Buttons and error button
	List->Buttons = malloc((NumberOf->Buttons+NumberOf->ButtonLeft+NumberOf->ButtonSize)*sizeof(*List->Buttons));
	assert(List->Buttons);
	printf("Debug1.1\n");
	List->Error = malloc((NumberOf->Error)*sizeof(*List->Buttons));
	assert(List->Error);
	printf("Debug1.2\n");
	LoadButton(List,MainVar,NumberOf);
	printf("Debug1.3\n");

	//detect txt file loaded in stdin
	if (isatty (STDIN_FILENO)) {
		//init Cases

		LoadCase(List,NumberOf);
		printf("Debug1.4\n");
		//load menu
		if (NumberOf->Lines >= 400 && NumberOf->Cols >= 400 ) LoadMap(List,NumberOf,"map/MenuH.ins");
		else LoadMap(List,NumberOf,"map/Menu.ins");
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
	printf("debug2\n");
	//main loop
	while (MainVar->run && List->Buttons[0].state == 0) {

		//load events
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT) MainVar->run = 0;

		//Detect Mouse Click
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT && MainVar->click == 0) {

				//delete error
				List->Error[0].state = 0;

				if (FindButton(Event,List,NumberOf,MainVar)) {
					goto ENDOFCHECK;
				}

				PlaceCell(renderer,Event,List,NumberOf,MainVar);
			}

			// for deleting cells
			else if (event.button.button == SDL_BUTTON_RIGHT && MainVar->click == 0) {
				RemoveCell(renderer,Event,List,NumberOf,MainVar);
			}
		}

		ENDOFCHECK:

		// Detect Mouse released
		if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_LEFT) MainVar->click = 0;
		}

		//detect keys pressed
		if (event.type == SDL_KEYDOWN) {

			if (HandleKeyDown(renderer,List,MainVar,NumberOf,Event,DispVar)) {
				MainVar->ButtonChanged = 1;
			}
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

		//Change speed button state
		if (NumberOf->Time == 1) {
			strcpy(List->Buttons[6].text, "Vitesse Max");
			List->Buttons[6].state = 1;
		}
		else strcpy(List->Buttons[6].text, "Plus Vite (p)");

		//stop when reach limite
		if (NumberOf->Gen == MainVar->limite) {
			MainVar->timer = 0;
			MainVar->limite = -1;
			strcpy(List->Buttons[8].text,"Lancer");
			List->Buttons[8].state = 0;
		}

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
