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
    TTF_Font *police = NULL;
    police = TTF_OpenFont("fonts/arial.ttf", 65);

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

	//main var
	int run = 1;
	int timer = 0;
	int *Timer = &timer;
	Grid numberOf;
	Grid *NumberOf = &numberOf;
	NumberOf->Lines = 50;
	NumberOf->Cols = 50;
	NumberOf->Buttons = 9;
	NumberOf->Direction = 6;
	NumberOf->ButtonLeft = 8;
	NumberOf->Time = 10;
	NumberOf->Gen = 0;

    //Case list
	Case **ListCase = NULL;

	int space = 0;
	int click = 0;
	St_State state;
	St_State *State = &state;
	State->Map = 0;
	State->Draw = 1;
	int Pressed = 0;
	int Ctrl = 0;
	int Shift = 0;

	//init displacement
	location loc;
	loc.locx = 0;
	loc.locy = 0;

	Couple Compare;

	//displacement var
	Disp dispVar;
	Disp *DispVar = &dispVar;
	DispVar->Hzt = 0;
	DispVar->Vtc = 0;
	DispVar->Zm = 0;

	//Buttons var
	int cornx;
	int corny;

	//init Buttons
	Button *ListButton = NULL;
	ListButton = malloc((NumberOf->Buttons+NumberOf->ButtonLeft)*sizeof(Button));
	assert(ListButton);
	LoadButton(ListButton,WIDTH,HEIGHT,NumberOf);

	//Load directions
	Button *ListDirection = NULL;
	ListDirection = malloc(NumberOf->Direction*sizeof(Button));
	assert(ListDirection);
	LoadDirection(ListDirection,WIDTH,HEIGHT,NumberOf);

	//detect txt file loaded
    if (isatty (STDIN_FILENO)) {
    		//init Cases
			ListCase = LoadCase(NumberOf);
            //load menu
            //LoadMap(ListCase,NumberOf,"map/Menu.ins");
    }
    else {
        printf("Pipe detected, load initial map skipped\n");
        scanf("%d",&NumberOf->Lines);
        scanf("%d",&NumberOf->Cols);
        printf("%d\n",NumberOf->Lines );
        NumberOf->Lines += 2;
        NumberOf->Cols += 2;

        //init Cases
        ListCase = LoadCase(NumberOf);
        for (int i=1; i<NumberOf->Lines-1; i++) {
            for (int j=1; j<NumberOf->Cols-1; j++) {
                scanf("%d",&ListCase[i][j].nextstate);
                printf("%d\n", ListCase[i][j].nextstate );
            }
        }
    }

    //setup scale
    loc.scale = HEIGHT/NumberOf->Lines;

	while (run && ListButton[0].state == 0) {

		//SDL_WaitEvent(&event);

		//load events
		SDL_PollEvent(&event);

		//place new cells
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT && click == 0) {
                /*methode 1 (WIP)
				Compare = CompareChunk(ListCase,NumberOf, loc, event.button.x,event.button.y);
				if (Compare.x != -1) {
					if (ListCase[Compare.y][Compare.x].state == 0) ListCase[Compare.y][Compare.x].nextstate = 1;
					else ListCase[Compare.y][Compare.x].nextstate = 0;
					click = 1;
				}*/
                //methode 2

				for (int j=0; j<NumberOf->Buttons+NumberOf->ButtonLeft; j++) {
                    if (ListButton[j].cornx <= event.button.x && event.button.x <= ListButton[j].cornx + ListButton[j].sizex
                    && ListButton[j].corny <= event.button.y && event.button.y <= ListButton[j].corny+ListButton[j].sizey) {
                    	if (ListButton[j].state == 0) ListButton[j].state = 1;
                        else ListButton[j].state = 0;
                        click = 1;
                        goto ENDOFCHECK;
                    }
                }

                for (int k=0; k<NumberOf->Direction-2; k++) {
                    if (ListDirection[k].cornx <= event.button.x
                    && event.button.x <= ListDirection[k].cornx + ListDirection[k].sizex
                    && ListDirection[k].corny <= event.button.y
                    && event.button.y <= ListDirection[k].corny + ListDirection[k].sizey) {
                    	if (ListDirection[k].state == 0) ListDirection[k].state = 1;
                        else ListDirection[k].state = 0;
                        click = 1;
                        goto ENDOFCHECK;
                    }
                }
                while(event.type != SDL_MOUSEBUTTONUP) {
                    for (int i=0; i<NumberOf->Lines; i++) {
                        for (int j=0; j<NumberOf->Cols; j++) {
                            if ((ListCase[i][j].posx+loc.locx)*(loc.scale+1)+(WIDTH/2-loc.scale*NumberOf->Cols/2) <= event.button.x
                            && (ListCase[i][j].posx+loc.locx)*(loc.scale+1)+loc.scale +(WIDTH/2-loc.scale*NumberOf->Cols/2) >= event.button.x
                            && (ListCase[i][j].posy+loc.locy)*(loc.scale+1) +(HEIGHT/2-loc.scale*NumberOf->Lines/2) <= event.button.y
                            && (ListCase[i][j].posy+loc.locy)*(loc.scale+1)+loc.scale +(HEIGHT/2-loc.scale*NumberOf->Lines/2) >= event.button.y) {
                                ListCase[i][j].nextstate = 1;
                                timer =0;
                                PrintScene(renderer,ListCase,ListDirection,ListButton,loc,NumberOf,Timer,police);

                            }
                        }
                    }
                    SDL_PollEvent(&event);
                }
			}

			if (event.button.button == SDL_BUTTON_RIGHT && click == 0) {
                while(event.type != SDL_MOUSEBUTTONUP) {
                    for (int i=0; i<NumberOf->Lines; i++) {
                        for (int j=0; j<NumberOf->Cols; j++) {
                            if ((ListCase[i][j].posx+loc.locx)*(loc.scale+1)+(WIDTH/2-loc.scale*NumberOf->Cols/2) <= event.button.x
                            && (ListCase[i][j].posx+loc.locx)*(loc.scale+1)+loc.scale +(WIDTH/2-loc.scale*NumberOf->Cols/2) >= event.button.x
                            && (ListCase[i][j].posy+loc.locy)*(loc.scale+1) +(HEIGHT/2-loc.scale*NumberOf->Lines/2) <= event.button.y
                            && (ListCase[i][j].posy+loc.locy)*(loc.scale+1)+loc.scale +(HEIGHT/2-loc.scale*NumberOf->Lines/2) >= event.button.y) {
                                ListCase[i][j].nextstate = 0;
                                timer =0;
                                PrintScene(renderer,ListCase,ListDirection,ListButton,loc,NumberOf,Timer,police);
                            }
                        }
                    }
                    SDL_PollEvent(&event);
                }
			}
		}

		ENDOFCHECK:

		if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_LEFT) click = 0;
			for (int k=0; k<NumberOf->Direction-2; k++) {
				ListDirection[k].state = 0;
				DispVar->Hzt = 0;
				DispVar->Vtc = 0;
				DispVar->Zm = 0;
			}
		}
		//detect keys pressed
		if (event.type == SDL_KEYDOWN) {

			// quit
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				run = 0;
			}

			//start / Stop
			if (event.key.keysym.sym == SDLK_SPACE && space == 0) {
				if (timer == 0) {
					ListButton[8].state = 1;
					strcpy(ListButton[8].text,"Arreter");
					timer = 1 ;
				}
				else {
					timer = 0;
					ListButton[8].state = 0;
					strcpy(ListButton[8].text,"Lancer");
				}
				space = 1;
			}

			//reload
			if (event.key.keysym.sym == SDLK_r) {
				Clean(ListCase,NumberOf);
			}

			//Save map
			if (event.key.keysym.sym == SDLK_k) {
				SaveMap(ListCase, NumberOf,"map/buffer.ins");
			}

			//Load map
			if (event.key.keysym.sym == SDLK_l) {
				LoadMap(ListCase, NumberOf,"map/buffer.ins");
				PrintScene(renderer, ListCase, ListDirection, ListButton,loc,NumberOf,Timer,police);
			}

			// timer
			if (event.key.keysym.sym == SDLK_m && Ctrl == 0) {
				NumberOf->Time +=1;
				Ctrl = 1;
			}

			if (event.key.keysym.sym == SDLK_p && NumberOf->Time > 2 && Shift == 0) {
				NumberOf->Time -=1;
				Shift = 1;
			}

			//arrows
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
				DispVar->Hzt = 1;
				Pressed = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
				DispVar->Hzt = -1;
				Pressed = 1;
			}
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z) {
				DispVar->Vtc = 1;
				Pressed = 1;
			}
			else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
				DispVar->Vtc = -1;
				Pressed = 1;
			}
			//zoom
			if (event.key.keysym.sym == SDLK_LSHIFT) {
				DispVar->Zm = 0.1;
				Pressed = 1;
				//Hzt = -0.4;
				//Vtc = -0.4;
			}
			else if (event.key.keysym.sym == SDLK_LCTRL) {
				DispVar->Zm = -0.1;
				Pressed = 1;
				//Hzt = -0.1;
				//Vtc = -0.1;
			}
		}

		//detect keys released
		if (event.type == SDL_KEYUP) {

			//start stop
			if (event.key.keysym.sym == SDLK_SPACE) space = 0;

			if (event.key.keysym.sym == SDLK_c) {
                loc.scale = HEIGHT/NumberOf->Lines;
                loc.locx = 0;
                loc.locy = 0;
			}

			//timer
			if (event.key.keysym.sym == SDLK_m) {
				Ctrl = 0;
			}

			if (event.key.keysym.sym == SDLK_p) {
				Shift = 0;
			}

			//arrows
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
				DispVar->Hzt = 0;
				Pressed = 0;
			}
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
				DispVar->Hzt = 0;
				Pressed = 0;
			}
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z) {
				DispVar->Vtc = 0;
				Pressed = 0;
			}
			if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
				DispVar->Vtc = 0;
				Pressed = 0;
			}

			//zoom
			if (event.key.keysym.sym == SDLK_LSHIFT) {
				DispVar->Zm = 0;
				DispVar->Hzt = 0;
				DispVar->Vtc = 0;
				Pressed = 0;

			}
			if (event.key.keysym.sym == SDLK_LCTRL) {
				DispVar->Zm = 0;
				DispVar->Hzt = 0;
				DispVar->Vtc = 0;
				Pressed = 0;

			}
		}

		//button application
		ButtonFunc(renderer, ListDirection, ListButton,ListCase, NumberOf, State,loc,Timer,police, DispVar);

		//displacement
		loc.locx += DispVar->Hzt;
		loc.locy += DispVar->Vtc;
		loc.scale += DispVar->Zm;

		if (timer >= NumberOf->Time) {
			if (State->Map == 0) LifeThor(ListCase, NumberOf);
			else LifeClosed(ListCase, NumberOf);
			NumberOf->Gen ++;
			timer = 1;
		}

		if (timer != 0) timer ++;
		PrintScene(renderer, ListCase,ListDirection, ListButton, loc, NumberOf, Timer, police);
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
