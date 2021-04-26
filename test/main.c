#include "src/mainfunc.h"

int main(int argc, char **argv) {

	time_t time1;
	time(&time1);
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
	int MaxTime = 10;
	Grid numberOf;
	Grid *NumberOf = &numberOf;
	NumberOf->Lines = 50;
	NumberOf->Cols = 50;
	NumberOf->Buttons = 12;

    //Case list
	Case **ListCase = NULL;

	int space = 0;
	int click = 0;
	int MapState = 0;
	int *MapState_p = &MapState;
	int Ctrl = 0;
	int Shift = 0;

	//init displacement
	location loc;
	loc.scale = 30;
	loc.locx = 0;
	loc.locy = 0;

	Couple Compare;

	//displacement var
	float Hzt = 0;
	float Vtc = 0;
	float Zm = 0;

	//Buttons var
	int cornx;
	int corny;

	//init Buttons
	Button *ListButton = NULL;
	ListButton = malloc(NumberOf->Buttons*sizeof(Button));
	assert(ListButton);
	LoadButton(ListButton,WIDTH,HEIGHT,NumberOf);

    //detect windows

	//detect txt file loaded
    if (isatty (STDIN_FILENO)) {
    		//init Cases
			ListCase = LoadCase(NumberOf);
            //load menu
            LoadMap(ListCase,NumberOf,"map/Menu.ins");
    }
    else {
            

        printf("Pipe detected, load initial map skipped\n");
        scanf("%d",&NumberOf->Lines);
        scanf("%d",&NumberOf->Cols);
        //init Cases
        ListCase = LoadCase(NumberOf);
        for (int i=0; i<NumberOf->Lines; i++) {
            for (int j=0; j<NumberOf->Cols; j++) {
                scanf("%d",&ListCase[i][j].nextstate);
            }
        }
        scanf("%d",&MapState);
    }

	while (run && ListButton[0].state == 0) {

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
                for (int i=0; i<NumberOf->Lines; i++) {
                    for (int j=0; j<NumberOf->Cols; j++) {
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

                //cornx = (ListCase[0][NumberOf->Cols-1].posx+loc.locx)*(loc.scale+1)+loc.scale+10;
				//corny = (ListCase[0][0].posy+loc.locy)*(loc.scale+1);
                for (int j=0; j<NumberOf->Buttons; j++) {
                    if (ListButton[j].resx-ListButton[j].sizex-10 <= event.button.x && event.button.x <= ListButton[j].resx-10
                    && 10+j*50+j <= event.button.y && event.button.y <= 10+j*50+j+ListButton[j].sizey) {
                    	if (ListButton[j].state == 0) ListButton[j].state = 1;
                        else ListButton[j].state = 0;
                        click = 1;
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
				if (timer == 0) {
					ListButton[11].state = 1;
					strcpy(ListButton[11].text,"Arreter");
					timer = 1 ;
				}
				else {
					timer = 0;
					ListButton[11].state = 0;
					strcpy(ListButton[11].text,"Lancer");
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
				PrintScene(renderer,ListCase,ListButton,loc,NumberOf,Timer,police);
			}

			// timer
			if (event.key.keysym.sym == SDLK_RSHIFT && Ctrl == 0) {
				MaxTime +=2;
				Ctrl = 1;
			}

			if (event.key.keysym.sym == SDLK_RCTRL && MaxTime > 2 && Shift == 0) {
				MaxTime -=2;
				Shift = 1;
			}

			//arrows
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
				Hzt = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
				Hzt = -1;
			}
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z) {
				Vtc = 1;
			}
			else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
				Vtc = -1;
			}
			//zoom
			if (event.key.keysym.sym == SDLK_LSHIFT) {
				Zm = 0.1;
				//Hzt = -0.4;
				//Vtc = -0.4;
			}
			else if (event.key.keysym.sym == SDLK_LCTRL) {
				Zm = -0.1;
				//Hzt = -0.1;
				//Vtc = -0.1;
			}
		}

		//detect keys released
		if (event.type == SDL_KEYUP) {

			//start stop
			if (event.key.keysym.sym == SDLK_SPACE) space = 0;

			if (event.key.keysym.sym == SDLK_c) {
                loc.scale = 30;
                loc.locx = 0;
                loc.locy = 0;
			}

			//timer
			if (event.key.keysym.sym == SDLK_RSHIFT) {
				Ctrl = 0;
			}

			if (event.key.keysym.sym == SDLK_RCTRL) {
				Shift = 0;
			}

			//arrows
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
				Hzt = 0;
			}
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
				Hzt = 0;
			}
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z) {
				Vtc = 0;
			}
			if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
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

		//button application
		ButtonFunc(renderer,ListButton,ListCase, NumberOf, MapState_p,loc,Timer,police);

		if (timer >= MaxTime) {
			if (MapState == 0) LifeThor(ListCase, NumberOf);
			else LifeClosed(ListCase, NumberOf);
			timer = 1;
		}

		if (timer != 0) timer ++;
		PrintScene(renderer, ListCase, ListButton, loc, NumberOf, Timer, police);
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
